/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *addressLabel;
    QComboBox *addressesComboBox;
    QLabel *portLabel;
    QLineEdit *portEditText;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QString::fromUtf8("SettingsDialog"));
        SettingsDialog->resize(300, 150);
        SettingsDialog->setMinimumSize(QSize(300, 150));
        SettingsDialog->setMaximumSize(QSize(500, 300));
        verticalLayout = new QVBoxLayout(SettingsDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        addressLabel = new QLabel(SettingsDialog);
        addressLabel->setObjectName(QString::fromUtf8("addressLabel"));

        verticalLayout->addWidget(addressLabel);

        addressesComboBox = new QComboBox(SettingsDialog);
        addressesComboBox->setObjectName(QString::fromUtf8("addressesComboBox"));

        verticalLayout->addWidget(addressesComboBox);

        portLabel = new QLabel(SettingsDialog);
        portLabel->setObjectName(QString::fromUtf8("portLabel"));

        verticalLayout->addWidget(portLabel);

        portEditText = new QLineEdit(SettingsDialog);
        portEditText->setObjectName(QString::fromUtf8("portEditText"));

        verticalLayout->addWidget(portEditText);

        buttonBox = new QDialogButtonBox(SettingsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "Settings", nullptr));
        addressLabel->setText(QApplication::translate("SettingsDialog", "Address:", nullptr));
        portLabel->setText(QApplication::translate("SettingsDialog", "Port:", nullptr));
        portEditText->setText(QApplication::translate("SettingsDialog", "12345", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
