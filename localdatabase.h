#ifndef LOCALDATABASE_H
#define LOCALDATABASE_H

#include <QTemporaryFile>
#include <QtSql>
#include <QJsonValue>
#include <QJsonObject>

struct Account {
    long id;
    QString email;
    QString username;
    QString password;
    long createdAt;

    QJsonObject toJson() {
        QJsonObject json;
        json.insert("id", (int) id);
        json.insert("email", email);
        json.insert("username", username);
        json.insert("createdAt", (qint64) createdAt);
        return json;
    }
};

struct Box {
    long id;
    QString colorName;
    QString colorValue;
    bool isActive;

    QJsonObject toJson() {
        QJsonObject json;
        json.insert("id", (int) id);
        json.insert("colorName", colorName);
        json.insert("colorValue", colorValue);
        json.insert("isActive", isActive);
        return json;
    }

    static Box fromRecord(QSqlQuery& query) {
        Box box;
        box.id = query.value("box_id").toInt();
        box.colorName = query.value("color_name").toString();
        box.colorValue = query.value("color_value").toString();
        box.isActive = query.value("is_active").toBool();
        return box;
    }
};

class LocalDatabase
{
private:
    QTemporaryFile *databaseFile;
    QSqlDatabase sqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
    bool _isReady;

    bool isAccountExists(QString email);

    void prepareAccountsModel();
    void prepareBoxesModel();
    void prepareSettingsModel();
    void prepareSettingsViewModel();

    void throwInternalError();
public:
    LocalDatabase();
    ~LocalDatabase();
    bool isReady();

    QSqlQueryModel accountsModel;
    QSqlQueryModel boxesModel;
    QSqlQueryModel settingsModel;
    QSqlQueryModel settingsViewModel;

    Account getAccount(long id);

    Account getAccountByEmail(QString email);

    void signUp(Account& account);

    void updateUsername(long id, QString newUsername);

    QList<Box> getBoxes(long accountId, bool* isActive = nullptr);

    Box getBox(long accountId, long boxId);

    void setActiveFlag(long userId, long boxId, bool isActive);

};

#endif // LOCALDATABASE_H
