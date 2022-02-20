#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "settingsdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dbStatuslabel->setText(localDatabase.isReady() ? QString("Database ready") : QString("Database not ready"));
    serverStatusLabel->setText("HTTP Server Offline");
    ui->statusbar->addPermanentWidget(dbStatuslabel);
    ui->statusbar->addPermanentWidget(serverStatusLabel);

    ui->accountsTableView->setModel(&localDatabase.accountsModel);
    ui->boxesTableView->setModel(&localDatabase.boxesModel);
    ui->settingsTableView->setModel(&localDatabase.settingsModel);
    ui->settingsViewTableView->setModel(&localDatabase.settingsViewModel);

    ui->accountsTableView->resizeColumnsToContents();
    ui->boxesTableView->resizeColumnsToContents();
    ui->settingsTableView->resizeColumnsToContents();
    ui->settingsViewTableView->resizeColumnsToContents();

    ui->boxesTableView->setItemDelegateForColumn(2, &colorDelegate);
    ui->settingsViewTableView->setItemDelegateForColumn(4, &colorDelegate);
    ui->settingsViewTableView->setItemDelegateForColumn(5, &checkboxDelegate);

    this->httpServer = new EmbeddedHttpServer(&this->localDatabase);

    QObject::connect(this->httpServer, &EmbeddedHttpServer::statusChanged, this, &MainWindow::onServerStatusChanged);
}

MainWindow::~MainWindow()
{
    delete this->httpServer;
    delete ui;
}

void MainWindow::on_actionExit_triggered() {
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered() {
    AboutDialog* dialog = new AboutDialog();
    dialog->setModal(true);
    dialog->exec();
    delete dialog;
}


void MainWindow::on_actionConfigure_triggered() {
    SettingsDialog* dialog = new SettingsDialog(this->httpServer);
    dialog->setModal(true);
    dialog->exec();
    delete dialog;
}

void MainWindow::onServerStatusChanged(QHostAddress address, int port, bool isStarted) {
    if (isStarted) {
        QString status = QString("HTTP Server ONLINE, port: %1, address: %2")
                .arg(port)
                .arg(address.toString());

        serverStatusLabel->setText(status);
    } else {
        serverStatusLabel->setText("HTTP Server Offline");
    }
}
