#include "mainwindow.h"

#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QRect screenRect = w.screen()->geometry();
    QRect windowGeometry = w.frameGeometry();
    windowGeometry.moveCenter(screenRect.center());
    w.move(windowGeometry.x(), windowGeometry.y());

    w.show();

    return a.exec();
}
