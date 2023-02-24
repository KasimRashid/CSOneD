/********************************************************************************
** Form generated from reading UI file 'seconddialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECONDDIALOG_H
#define UI_SECONDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SecondDialog
{
public:
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *SecondDialog)
    {
        if (SecondDialog->objectName().isEmpty())
            SecondDialog->setObjectName("SecondDialog");
        SecondDialog->resize(400, 300);
        label = new QLabel(SecondDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 100, 261, 16));
        pushButton = new QPushButton(SecondDialog);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(120, 60, 161, 18));

        retranslateUi(SecondDialog);

        QMetaObject::connectSlotsByName(SecondDialog);
    } // setupUi

    void retranslateUi(QDialog *SecondDialog)
    {
        SecondDialog->setWindowTitle(QCoreApplication::translate("SecondDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SecondDialog", "This is the menu for the Student View", nullptr));
        pushButton->setText(QCoreApplication::translate("SecondDialog", "open database", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SecondDialog: public Ui_SecondDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECONDDIALOG_H
