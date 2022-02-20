#ifndef EMBEDDEDHTTPSERVER_H
#define EMBEDDEDHTTPSERVER_H

#include <QtNetwork/QNetworkInterface>
#include <QObject>
#include "httplistener.h"
#include "localdatabase.h"

using namespace stefanfrings;

class EmbeddedHttpServer : public QObject
{
    Q_OBJECT
private:
    QHostAddress address = QHostAddress(QHostAddress::LocalHost);
    int port = 12345;
    QSettings* settings = nullptr;
    HttpListener* httpListener = nullptr;
    HttpRequestHandler* httpRequestHandler = nullptr;

    LocalDatabase* database;

    void doStart();
public:
    EmbeddedHttpServer(LocalDatabase* database);

    void restart(QHostAddress address, int port);

    void stop();

    bool isStarted();

    ~EmbeddedHttpServer();

    int getPort();

    QHostAddress getAddress();

signals:
    void statusChanged(QHostAddress address, int port, bool isStarted);

};

#endif // EMBEDDEDHTTPSERVER_H
