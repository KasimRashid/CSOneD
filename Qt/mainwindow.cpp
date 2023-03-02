#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QMessageBox>
#include <QFont>
#include "QDebug"

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

void MainWindow::on_loginButton_clicked()
{
    if(ui->UserLineEdit->text() == "A" && ui->PWLineEdit->text() == "A")
    {
       //ADMIN PAGE
       QMessageBox::information(this, "Welcome, Admin!", "Now moving to the Admin Screen...", QMessageBox::Ok, QMessageBox::NoButton);
       adminObj.show();
    }
    else
       QMessageBox::critical(this, "Access Denied", "INCORRECT LOGIN", QMessageBox::Ok, QMessageBox::NoButton);

}

void MainWindow::on_clearButton_clicked()
{
    ui->UserLineEdit->setText("");
    ui->PWLineEdit->setText("");
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox::information(this, "Welcome, Student!", "Now moving to the Student Screen...", QMessageBox::Ok, QMessageBox::NoButton);
    studentObj.show();
}
