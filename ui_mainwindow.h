/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionConfigure;
    QAction *actionAbout;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tablesTabs;
    QWidget *accountsTab;
    QGridLayout *gridLayout;
    QTableView *accountsTableView;
    QWidget *boxesTab;
    QGridLayout *gridLayout_2;
    QTableView *boxesTableView;
    QWidget *accountBoxesSettingsTab;
    QGridLayout *gridLayout_3;
    QTableView *settingsTableView;
    QWidget *settingsViewTab;
    QGridLayout *gridLayout_4;
    QTableView *settingsViewTableView;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuOptions;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(695, 558);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/ic_app.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QFont font;
        font.setPointSize(10);
        actionExit->setFont(font);
        actionConfigure = new QAction(MainWindow);
        actionConfigure->setObjectName(QString::fromUtf8("actionConfigure"));
        actionConfigure->setFont(font);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tablesTabs = new QTabWidget(centralwidget);
        tablesTabs->setObjectName(QString::fromUtf8("tablesTabs"));
        accountsTab = new QWidget();
        accountsTab->setObjectName(QString::fromUtf8("accountsTab"));
        gridLayout = new QGridLayout(accountsTab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        accountsTableView = new QTableView(accountsTab);
        accountsTableView->setObjectName(QString::fromUtf8("accountsTableView"));

        gridLayout->addWidget(accountsTableView, 0, 0, 1, 1);

        tablesTabs->addTab(accountsTab, QString());
        boxesTab = new QWidget();
        boxesTab->setObjectName(QString::fromUtf8("boxesTab"));
        gridLayout_2 = new QGridLayout(boxesTab);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        boxesTableView = new QTableView(boxesTab);
        boxesTableView->setObjectName(QString::fromUtf8("boxesTableView"));

        gridLayout_2->addWidget(boxesTableView, 0, 0, 1, 1);

        tablesTabs->addTab(boxesTab, QString());
        accountBoxesSettingsTab = new QWidget();
        accountBoxesSettingsTab->setObjectName(QString::fromUtf8("accountBoxesSettingsTab"));
        gridLayout_3 = new QGridLayout(accountBoxesSettingsTab);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        settingsTableView = new QTableView(accountBoxesSettingsTab);
        settingsTableView->setObjectName(QString::fromUtf8("settingsTableView"));

        gridLayout_3->addWidget(settingsTableView, 0, 0, 1, 1);

        tablesTabs->addTab(accountBoxesSettingsTab, QString());
        settingsViewTab = new QWidget();
        settingsViewTab->setObjectName(QString::fromUtf8("settingsViewTab"));
        gridLayout_4 = new QGridLayout(settingsViewTab);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        settingsViewTableView = new QTableView(settingsViewTab);
        settingsViewTableView->setObjectName(QString::fromUtf8("settingsViewTableView"));

        gridLayout_4->addWidget(settingsViewTableView, 0, 0, 1, 1);

        tablesTabs->addTab(settingsViewTab, QString());

        horizontalLayout->addWidget(tablesTabs);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 695, 23));
        menubar->setFont(font);
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFile->setFont(font);
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        menuOptions->setFont(font);
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuOptions->menuAction());
        menuFile->addAction(actionExit);
        menuOptions->addAction(actionConfigure);
        menuOptions->addSeparator();
        menuOptions->addAction(actionAbout);

        retranslateUi(MainWindow);

        tablesTabs->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Simple HTTP Server", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        actionConfigure->setText(QApplication::translate("MainWindow", "Configure...", nullptr));
        actionAbout->setText(QApplication::translate("MainWindow", "About", nullptr));
#ifndef QT_NO_TOOLTIP
        tablesTabs->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_ACCESSIBILITY
        tablesTabs->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        tablesTabs->setTabText(tablesTabs->indexOf(accountsTab), QApplication::translate("MainWindow", "Accounts Table", nullptr));
        tablesTabs->setTabText(tablesTabs->indexOf(boxesTab), QApplication::translate("MainWindow", "Boxes Table", nullptr));
        tablesTabs->setTabText(tablesTabs->indexOf(accountBoxesSettingsTab), QApplication::translate("MainWindow", "Settings Table", nullptr));
        tablesTabs->setTabText(tablesTabs->indexOf(settingsViewTab), QApplication::translate("MainWindow", "Settings View", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuOptions->setTitle(QApplication::translate("MainWindow", "Options", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
