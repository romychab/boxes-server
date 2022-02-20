#ifndef EMBEDDEDREQUESTHANDLER_H
#define EMBEDDEDREQUESTHANDLER_H

#include "httprequesthandler.h"
#include "localdatabase.h"
#include <QJsonDocument>

#define JWT_SECRET "PUT_YOUR_SECRET_HERE"

using namespace stefanfrings;

class EmbeddedRequestHandler : public HttpRequestHandler {
    Q_OBJECT
private:
    LocalDatabase* database;
    void onSignIn(QJsonObject& payload, HttpResponse& response);
    void onSignUp(QJsonObject& payload, HttpResponse& response);
    void getBoxes(long userId, HttpResponse& response, bool* isActive = nullptr);
    void getBox(long userId, long boxId, HttpResponse& response);
    void putBox(long userId, long boxId, QJsonObject& payload, HttpResponse& response);

    void getAccountInfo(long userId, HttpResponse& response);
    void putAccountInfo(long userId, QJsonObject& payload, HttpResponse& response);

    long isAuthorized(HttpRequest& request);

    void writeError(int httpCode, QByteArray httpMessage, QString message, HttpResponse& response);
    void writeSuccess(QJsonDocument& document, HttpResponse& response);
    void writeSuccessObj(const QJsonObject& json, HttpResponse& response);
    void writeSuccessStatusObj(HttpResponse& response);

    QJsonObject getPayload(HttpRequest& request);
public:
    EmbeddedRequestHandler(LocalDatabase* database);
    void service(HttpRequest& request, HttpResponse& response) override;
};

#endif // EMBEDDEDREQUESTHANDLER_H
