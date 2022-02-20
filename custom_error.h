#ifndef CUSTOM_ERROR_H
#define CUSTOM_ERROR_H

#include <QString>

struct HttpError {
    int code;
    QString message;
    QString bodyMessage;

    HttpError(int code, QString message, QString bodyMessage) :
        code(code),
        message(message),
        bodyMessage(bodyMessage){}
};

#endif // CUSTOM_ERROR_H
