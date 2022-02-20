#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include "addressesmodel.h"
#include "embeddedhttpserver.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(EmbeddedHttpServer* server, QWidget *parent = nullptr);
    ~SettingsDialog();
    AddressesModel* addressesModel;
    void accept() override;
private:
    Ui::SettingsDialog *ui;
    EmbeddedHttpServer *server;
};

#endif // SETTINGSDIALOG_H
