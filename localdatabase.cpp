#include <QTemporaryFile>

#include "localdatabase.h"
#include <QtSql>
#include <QtDebug>
#include "custom_error.h"

LocalDatabase::LocalDatabase() {
    databaseFile = QTemporaryFile::createNativeFile(":/database/initial_database.db");
    sqlDatabase.setDatabaseName(databaseFile->fileName());

    bool isOpened = sqlDatabase.open();
    if (!isOpened) return;

    prepareAccountsModel();
    prepareBoxesModel();
    prepareSettingsModel();
    prepareSettingsViewModel();
    _isReady = true;
}

void LocalDatabase::prepareAccountsModel() {
    accountsModel.setQuery(QSqlQuery("SELECT * FROM accounts", sqlDatabase));
}

void LocalDatabase::prepareBoxesModel() {
    boxesModel.setQuery(QSqlQuery("SELECT * FROM boxes", sqlDatabase));
}

void LocalDatabase::prepareSettingsModel() {
    settingsModel.setQuery(QSqlQuery("SELECT * FROM accounts_boxes_settings", sqlDatabase));
}

void LocalDatabase::prepareSettingsViewModel() {
    settingsViewModel.setQuery(QSqlQuery("SELECT email, username, box_id, color_name, color_value, is_active FROM boxes_and_settings_view", sqlDatabase));
}

LocalDatabase::~LocalDatabase() {
    sqlDatabase.close();
    delete databaseFile;
}

Account createAccount(QSqlQuery& query) {
    Account account;
    account.id = query.value("id").toInt();
    account.email = query.value("email").toString();
    account.username = query.value("username").toString();
    account.password = query.value("password").toString();
    account.createdAt = query.value("created_at").toLongLong();
    return account;
}

bool LocalDatabase::isAccountExists(QString email) {
    try {
        getAccountByEmail(email);
        return true;
    }  catch (...) {
        return false;
    }
}

bool LocalDatabase::isReady() {
    return _isReady;
}

Account LocalDatabase::getAccount(long id) {
    QSqlQuery query(sqlDatabase);
    query.prepare("SELECT * FROM accounts WHERE id = :id");
    query.bindValue(":id", QVariant::fromValue(id));
    if (!query.exec()) throwInternalError();
    if (query.next()) {
        return createAccount(query);
    }
    throw HttpError(404, "Not Found", "Account doesn't exist");
}

void LocalDatabase::signUp(Account& account) {
    if (account.email.isEmpty()) throw HttpError(400, "Bad Request", "Email is empty");
    if (account.username.isEmpty()) throw HttpError(400, "Bad Request", "Username is empty");
    if (account.password.isEmpty()) throw HttpError(400, "Bad Request", "Password is empty");
    if (isAccountExists(account.email)) throw HttpError(409, "Conflict", "User with such email already exists");

    QSqlQuery query(sqlDatabase);
    query.prepare("INSERT INTO accounts (email, username, password, created_at) VALUES (:email, :username, :password, :created_at)");
    query.bindValue(":email", account.email);
    query.bindValue(":username", account.username);
    query.bindValue(":password", account.password);
    query.bindValue(":created_at", QVariant::fromValue(account.createdAt));
    if (!query.exec()) throwInternalError();
    prepareAccountsModel();
    prepareSettingsViewModel();
}

Account LocalDatabase::getAccountByEmail(QString email) {
    QSqlQuery query(sqlDatabase);
    query.prepare("SELECT * FROM accounts WHERE email = :email");
    query.bindValue(":email", email);
    if (!query.exec()) throwInternalError();
    if (query.next()) {
        return createAccount(query);
    }
    throw HttpError(401, "Unathorized", "Invalid email or password");
}

void LocalDatabase::updateUsername(long id, QString newUsername) {
    QSqlQuery query(sqlDatabase);
    query.prepare("UPDATE accounts SET username = :username WHERE id = :id");
    query.bindValue(":username", newUsername);
    query.bindValue(":id", QVariant::fromValue(id));
    if (!query.exec()) throwInternalError();
    prepareAccountsModel();
    prepareSettingsViewModel();
}

QList<Box> LocalDatabase::getBoxes(long accountId, bool* isActive) {
    QSqlQuery query(sqlDatabase);
    if (isActive == nullptr) {
        query.prepare("SELECT * FROM boxes_and_settings_view WHERE account_id = :accountId");
    } else {
        query.prepare("SELECT * FROM boxes_and_settings_view WHERE account_id = :accountId AND is_active = :isActive");
        query.bindValue(":isActive", QVariant::fromValue(*isActive ? 1 : 0));
    }
    query.bindValue(":accountId", QVariant::fromValue(accountId));
    if (!query.exec()) throwInternalError();
    QList<Box> boxes;
    while (query.next()) {
        boxes.append(Box::fromRecord(query));
    }
    return boxes;
}

Box LocalDatabase::getBox(long accountId, long boxId) {
    QSqlQuery query(sqlDatabase);
    query.prepare("SELECT * FROM boxes_and_settings_view WHERE account_id = :accountId AND box_id = :boxId");
    query.bindValue(":accountId", QVariant::fromValue(accountId));
    query.bindValue(":boxId", QVariant::fromValue(boxId));
    if (!query.exec()) throwInternalError();
    if (query.next()) {
        return Box::fromRecord(query);
    }
    throw HttpError(404, "Not Found", "There is no box with such ID");
}

void LocalDatabase::setActiveFlag(long userId, long boxId, bool isActive) {
    QSqlQuery query(sqlDatabase);
    query.prepare("INSERT OR REPLACE INTO accounts_boxes_settings VALUES(:userId, :boxId, :isActive)");
    query.bindValue(":userId", QVariant::fromValue(userId));
    query.bindValue(":boxId", QVariant::fromValue(boxId));
    query.bindValue(":isActive", QVariant::fromValue(isActive));
    if (!query.exec()) throwInternalError();
    prepareSettingsModel();
    prepareSettingsViewModel();
}

void LocalDatabase::throwInternalError() {
    throw HttpError(500, "Internal Server Error", "Failed to executed the operation");
}
