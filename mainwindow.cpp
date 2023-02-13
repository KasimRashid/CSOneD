#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_loginAdmin_clicked()
{
    QString username = ui->lineEdit_userName->text();
    QString password = ui->lineEdit_password->text();

    if (username == "admin" && password == "12345")
    {
        QMessageBox::information(this, "Login", "Username and password is correct.");
        //hide();
        dialog = new Dialog(this);
        dialog->show();
    }
    else
    {
        QMessageBox::warning(this, "Login", "Username and password is incorrect.");
    }
}


void MainWindow::on_pushButton_loginStudent_clicked()
{
    QMessageBox::information(this, "Login", "Logging in as Student.");
    //hide();
    secondDialog = new SecondDialog(this);
    secondDialog->show();
}

