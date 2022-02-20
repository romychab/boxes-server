#include <QJsonDocument>
#include <QDateTime>
#include "embeddedrequesthandler.h"
#include "custom_error.h"
#include "QJsonWebToken"

EmbeddedRequestHandler::EmbeddedRequestHandler(LocalDatabase* database) {
    this->database = database;
}

QString createToken(Account& account) {
    QJsonWebToken token;
    token.setSecret(JWT_SECRET);
    token.appendClaim("iss", "rom");
    token.appendClaim("aud", QString::number(account.id));
    token.appendClaim("exp", QString::number(QDateTime::currentDateTime().addDays(7).toSecsSinceEpoch()));
    token.appendClaim("iat", QString::number(QDateTime::currentDateTime().toSecsSinceEpoch()));
    token.appendClaim("sub", "all");
    token.setAlgorithmStr("HS256");
    return token.getToken();
}

void EmbeddedRequestHandler::onSignIn(QJsonObject& payload, HttpResponse& response) {
    QString email = payload.value("email").toString();
    QString password = payload.value("password").toString();
    Account account = database->getAccountByEmail(email);
    if (account.password == password) {
        QJsonObject json;
        QString token = createToken(account);
        json.insert("token", token);
        writeSuccessObj(json, response);
    } else {
        throw HttpError(401, "Unathorized", "Invalid email or password");
    }
}

void EmbeddedRequestHandler::onSignUp(QJsonObject& payload, HttpResponse& response) {
    Account account;
    account.email = payload.value("email").toString();
    account.username = payload.value("username").toString();
    account.password = payload.value("password").toString();
    account.createdAt = QDateTime::currentMSecsSinceEpoch();
    database->signUp(account);
    writeSuccessStatusObj(response);
}

void EmbeddedRequestHandler::getBoxes(long userId, HttpResponse& response, bool* isActive) {
    QList<Box> boxes = database->getBoxes(userId, isActive);
    QJsonArray array;
    QList<Box>::iterator i;
    for (i = boxes.begin(); i != boxes.end(); i++) {
        QJsonObject json = (*i).toJson();
        array.append(json);
    }
    QJsonDocument document(array);
    writeSuccess(document, response);
}

void EmbeddedRequestHandler::getBox(long userId, long boxId, HttpResponse& response) {
    Box box = database->getBox(userId, boxId);
    writeSuccessObj(box.toJson(), response);
}

void EmbeddedRequestHandler::putBox(long userId, long boxId, QJsonObject& payload, HttpResponse& response) {
    bool isActive = payload.value("isActive").toBool();
    database->setActiveFlag(userId, boxId, isActive);
    writeSuccessStatusObj(response);
}

void EmbeddedRequestHandler::getAccountInfo(long userId, HttpResponse& response) {
    Account account = database->getAccount(userId);
    writeSuccessObj(account.toJson(), response);
}

void EmbeddedRequestHandler::putAccountInfo(long userId, QJsonObject& payload, HttpResponse& response) {
    QString newUsername = payload.value("username").toString();
    if (newUsername.isEmpty()) throw HttpError(400, "Bad Request", "Empty username");
    database->updateUsername(userId, newUsername);
    writeSuccessStatusObj(response);
}

void EmbeddedRequestHandler::service(HttpRequest& request, HttpResponse& response) {
    QByteArray path = request.getPath();
    QByteArray method = request.getMethod();

    try {
        if (path == "/sign-in" && method == "POST") {
            QJsonObject payload = getPayload(request);
            this->onSignIn(payload, response);
            return;
        } else if (path == "/sign-up" && method == "POST") {
            QByteArray body = request.getBody();
            QJsonObject payload = getPayload(request);
            this->onSignUp(payload, response);
            return;
        }

        long userId = this->isAuthorized(request);
        if (userId < 0) {
            writeError(401, "Unauthorized", "Authorization token is invalid or doesn't exist", response);
            return;
        }

        if (path == "/boxes" && method == "GET") {
            QByteArray isActive = request.getParameter("active");
            if (isActive.isEmpty()) {
                this->getBoxes(userId, response);
            } else {
                bool isActiveValue = isActive == "true";
                this->getBoxes(userId, response, &isActiveValue);
            }
            return;

        } else if (path.startsWith("/boxes/")) {
            QList<QByteArray> parts = path.split('/');
            if (parts.size() != 3) {
                writeError(404, "Not found", "Invalid box path", response);
                return;
            }
            bool ok;
            long boxId = parts.takeAt(2).toLong(&ok);
            if (!ok) {
                writeError(404, "Not found", "Box not found", response);
                return;
            }
            if (method == "GET") {
                this->getBox(userId, boxId, response);
                return;
            } else if (method == "PUT") {
                QJsonObject payload = getPayload(request);
                this->putBox(userId, boxId, payload, response);
                return;
            }
            return;

        } else if (path == "/me") {
            if (method == "GET") {
                this->getAccountInfo(userId, response);
                return;
            } else if (method == "PUT") {
                QJsonObject payload = getPayload(request);
                this->putAccountInfo(userId, payload, response);
                return;
            }
        }

        writeError(404, "Not Found", "Resource not found", response);
    } catch (HttpError& error) {
        writeError(error.code, error.message.toUtf8(), error.bodyMessage, response);
    } catch (...) {
        writeError(400, "Error", "Invalid request", response);
    }
}

long EmbeddedRequestHandler::isAuthorized(HttpRequest& request) {
    QString auth = request.getHeader("Authorization");
    if (auth.isEmpty()) return -1;
    QJsonWebToken token = QJsonWebToken::fromTokenAndSecret(auth, JWT_SECRET);
    if (token.isValid()) {
        long expiredAt = token.claim("exp").toLong();
        long currentTime = QDateTime::currentSecsSinceEpoch();
        if (currentTime > expiredAt) {
            return -1;
        } else {
            return token.claim("aud").toInt();
        }
    } else {
        return -1;
    }
}

void EmbeddedRequestHandler::writeError(int httpCode, QByteArray httpMessage, QString message, HttpResponse& response) {
    QJsonObject payload;
    payload.insert("error", QJsonValue::fromVariant(message));
    response.setStatus(httpCode, httpMessage);
    response.write(QJsonDocument(payload).toJson(), true);
}

void EmbeddedRequestHandler::writeSuccessObj(const QJsonObject& json, HttpResponse& response) {
    QJsonDocument document(json);
    writeSuccess(document, response);
}

void EmbeddedRequestHandler::writeSuccessStatusObj(HttpResponse& response) {
    QJsonObject json;
    json.insert("status", "ok");
    writeSuccessObj(json, response);
}

void EmbeddedRequestHandler::writeSuccess(QJsonDocument& document, HttpResponse& response) {
    response.setStatus(200, "OK");
    response.write(document.toJson(), true);
}

QJsonObject EmbeddedRequestHandler::getPayload(HttpRequest& request) {
    return QJsonDocument::fromJson(request.getBody()).object();
}
