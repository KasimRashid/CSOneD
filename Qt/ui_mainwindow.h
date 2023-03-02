/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QLineEdit *UserLineEdit;
    QPushButton *clearButton;
    QLineEdit *PWLineEdit;
    QPushButton *loginButton;
    QLabel *adminLabel;
    QLabel *UserLabel;
    QLabel *PWLabel;
    QLabel *studentLabel;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(858, 565);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(180, 244, 255)"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(510, 220, 251, 91));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 38, 0)"));
        UserLineEdit = new QLineEdit(centralwidget);
        UserLineEdit->setObjectName(QString::fromUtf8("UserLineEdit"));
        UserLineEdit->setGeometry(QRect(242, 230, 141, 22));
        UserLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0,  0)"));
        UserLineEdit->setEchoMode(QLineEdit::Normal);
        UserLineEdit->setCursorPosition(0);
        clearButton = new QPushButton(centralwidget);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        clearButton->setGeometry(QRect(280, 330, 93, 28));
        clearButton->setStyleSheet(QString::fromUtf8("background-color: rgb(4, 51, 255)"));
        PWLineEdit = new QLineEdit(centralwidget);
        PWLineEdit->setObjectName(QString::fromUtf8("PWLineEdit"));
        PWLineEdit->setGeometry(QRect(242, 280, 141, 22));
        PWLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0)"));
        PWLineEdit->setEchoMode(QLineEdit::Password);
        PWLineEdit->setDragEnabled(false);
        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        loginButton->setGeometry(QRect(150, 330, 93, 28));
        loginButton->setStyleSheet(QString::fromUtf8("background-color: rgb(4, 51, 255)"));
        adminLabel = new QLabel(centralwidget);
        adminLabel->setObjectName(QString::fromUtf8("adminLabel"));
        adminLabel->setGeometry(QRect(120, 140, 301, 51));
        adminLabel->setAlignment(Qt::AlignCenter);
        UserLabel = new QLabel(centralwidget);
        UserLabel->setObjectName(QString::fromUtf8("UserLabel"));
        UserLabel->setGeometry(QRect(150, 230, 71, 16));
        PWLabel = new QLabel(centralwidget);
        PWLabel->setObjectName(QString::fromUtf8("PWLabel"));
        PWLabel->setGeometry(QRect(150, 280, 71, 16));
        studentLabel = new QLabel(centralwidget);
        studentLabel->setObjectName(QString::fromUtf8("studentLabel"));
        studentLabel->setGeometry(QRect(540, 140, 191, 51));
        studentLabel->setAlignment(Qt::AlignCenter);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(210, 50, 461, 51));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 858, 37));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Login as Student", nullptr));
        clearButton->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        loginButton->setText(QApplication::translate("MainWindow", "Login", nullptr));
        adminLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:24pt; font-weight:600; text-decoration: underline; color:#0433ff;\">ADMINISTRATOR LOGIN</span></p></body></html>", nullptr));
        UserLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" text-decoration: underline; color:#0433ff;\">Username:</span></p></body></html>", nullptr));
        PWLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" text-decoration: underline; color:#0433ff;\">Password:</span></p></body></html>", nullptr));
        studentLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:24pt; font-weight:600; text-decoration: underline; color:#ff2600;\">STUDENT LOGIN</span></p></body></html>", nullptr));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:36pt; font-weight:600; text-decoration: underline;\">College Touring Project</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
