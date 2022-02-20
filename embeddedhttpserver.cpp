#include <QSettings>
#include "httplistener.h"
#include "httprequesthandler.h"
#include "embeddedhttpserver.h"
#include "embeddedrequesthandler.h"

using namespace stefanfrings;

EmbeddedHttpServer::EmbeddedHttpServer(LocalDatabase* database)
{
    this->database = database;
}

void EmbeddedHttpServer::restart(QHostAddress address, int port) {
    this->address = address;
    this->port = port;
    if (isStarted()) {
        stop();
    }
    doStart();
}

void EmbeddedHttpServer::stop() {
    if (this->httpListener != nullptr) {
        this->httpListener->close();
        delete this->httpListener;
        delete this->httpRequestHandler;
        delete this->settings;
        this->httpListener = nullptr;
    }
    emit this->statusChanged(this->address, this->port, false);
}

bool EmbeddedHttpServer::isStarted() {
    return this->httpListener != nullptr
            && this->httpListener->isListening();
}

EmbeddedHttpServer::~EmbeddedHttpServer() {
    this->stop();
}

void EmbeddedHttpServer::doStart() {
    QSettings* settings = new QSettings("rom");
    settings->setValue("host", this->address.toString());
    settings->setValue("port", this->port);
    settings->setValue("minThreads", 4);
    settings->setValue("maxThreads", 10);
    settings->setValue("cleanupInterval", 60000);
    settings->setValue("readTimeout", 60000);
    settings->setValue("maxRequestSize", 100000);
    settings->setValue("maxMultiPartSize", 10000000);
    this->settings = settings;
    this->httpRequestHandler = new EmbeddedRequestHandler(this->database);
    this->httpListener = new HttpListener(settings, this->httpRequestHandler);
    if (this->httpListener->isListening()) {
        emit this->statusChanged(this->address, this->port, true);
    }
}

int EmbeddedHttpServer::getPort() {
    return this->port;
}

QHostAddress EmbeddedHttpServer::getAddress() {
    return this->address;
}
