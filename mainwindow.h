#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "localdatabase.h"
#include "embeddedhttpserver.h"
#include "item_delegates.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    LocalDatabase localDatabase;
    ColorDelegate colorDelegate;
    CheckBoxDelegate checkboxDelegate;

    EmbeddedHttpServer* httpServer;

private slots:
    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_actionConfigure_triggered();

    void onServerStatusChanged(QHostAddress address, int port, bool isStarted);
private:
    Ui::MainWindow *ui;
    QLabel *dbStatuslabel = new QLabel(this);
    QLabel *serverStatusLabel = new QLabel(this);
};
#endif // MAINWINDOW_H
