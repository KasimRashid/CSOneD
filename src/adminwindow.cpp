#include "adminwindow.h"
#include "mainwindow.h"
#include "ui_adminwindow.h"
#include "collegeeditwindow.h"
#include "souvenireditwindow.h"
#include "souvenirchangeprice.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_addCollege_clicked()
{
    CollegeEditWindow *collegeWindow = new CollegeEditWindow();
    collegeWindow->show();
    this->close();
}

void AdminWindow::on_pushButton_2_clicked()
{
   MainWindow *main = new MainWindow;
   main->show();
   this->close();
}

void AdminWindow::on_pushButton_3_clicked()
{
    SouvenirEditWindow *souvenirNew = new SouvenirEditWindow();
    souvenirNew->show();
    this->close();
}

void AdminWindow::on_pushButton_clicked()
{
    SouvenirChangePrice *priceNew = new SouvenirChangePrice();
    priceNew->show();
    this->close();
}
