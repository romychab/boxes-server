QT       += core gui
QT       += sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += static

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutdialog.cpp \
    addressesmodel.cpp \
    embeddedhttpserver.cpp \
    embeddedrequesthandler.cpp \
    localdatabase.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp

HEADERS += \
    aboutdialog.h \
    addressesmodel.h \
    custom_error.h \
    embeddedhttpserver.h \
    embeddedrequesthandler.h \
    item_delegates.h \
    localdatabase.h \
    mainwindow.h \
    settingsdialog.h

FORMS += \
    aboutdialog.ui \
    mainwindow.ui \
    settingsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

include(QtWebApp/logging/logging.pri)
include(QtWebApp/httpserver/httpserver.pri)
include(jwt/qjsonwebtoken.pri)
