#include <QMessageBox>
#include <QAbstractButton>
#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "addressesmodel.h"

SettingsDialog::SettingsDialog(EmbeddedHttpServer* server, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    this->server = server;

    this->addressesModel = new AddressesModel(this);
    ui->setupUi(this);
    ui->addressesComboBox->setModel(this->addressesModel);

    ui->portEditText->setText(QString::number(server->getPort()));

    int index = ui->addressesComboBox->findText(server->getAddress().toString());
    if (index >= 0) ui->addressesComboBox->setCurrentIndex(index);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::accept() {
    QString portTextValue = ui->portEditText->text();
    bool ok;
    int port = portTextValue.toInt(&ok, 10);
    if (!ok || port < 10000 || port > 65535) {
        QMessageBox::critical(this, "Error", "Port number is incorrect!");
        return;
    }

    int index = ui->addressesComboBox->currentIndex();
    if (index < 0 || index >= ui->addressesComboBox->count()) {
        QMessageBox::critical(this, "Error", "Address is not selected!");
        return;
    }

    QString addressValue = ui->addressesComboBox->currentText();
    //QString addressValue = ui->addressesComboBox->currentData();
    QHostAddress address(addressValue);
    server->restart(address, port);
    if (!server->isStarted()) {
        QMessageBox::critical(this, "Error", "Can't start server. Please check the address/port is free and the firewall settings of your OS allow listening TCP connections.");
        return;
    }

    QDialog::close();
}
