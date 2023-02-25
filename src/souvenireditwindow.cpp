#include "souvenireditwindow.h"
#include "ui_souvenireditwindow.h"
#include "adminwindow.h"
#include "college.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QList>

SouvenirEditWindow::SouvenirEditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SouvenirEditWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    populate();

}

void SouvenirEditWindow::populate()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery colleges_qry("SELECT * FROM College_Touring");

    while (colleges_qry.next()) {
        // push back College
        colleges1.push_back(College(colleges_qry.record().value("ID").toInt(),
                                colleges_qry.record().value("Universities").toString()));
    }

    ui->collegeBox->insertItem(0," (Choose a college) ");
    for(int i=0; i<colleges1.length(); i++)
    {
        ui->collegeBox->addItem(colleges1.at(i).getCollegeName());
    }

    QSqlQuery souvenir_qry("SELECT * FROM colleges_souvenirs");

    while (souvenir_qry.next()) {
        // push back College
        souvenirs1.push_back(souvenir_qry.record().value("souvenir").toString());
    }

    ui->souvenirBox->insertItem(0," (Choose a souvenir) ");
    for(int i=0; i<souvenirs1.length(); i++)
    {
        ui->souvenirBox->addItem(souvenirs1.at(i));
    }
}

SouvenirEditWindow::~SouvenirEditWindow()
{
    delete ui;
}

void SouvenirEditWindow::on_pushButton_3_clicked()
{
    AdminWindow *admin = new AdminWindow;
    admin->show();
    this->close();
}

void SouvenirEditWindow::on_addSouvenirButton_clicked()
{    
    QSqlDatabase db = QSqlDatabase::database();
    int collegeIndex = ui->collegeBox->currentIndex() - 1;

    QSqlQuery query;

    query.prepare("INSERT INTO colleges_souvenirs(ID,souvenir,price,Quantity,Universities) VALUES (:id, :name, :price, :quantity, :college)");
    query.bindValue(":id", this->colleges1.at(collegeIndex).getCollegeID());
    query.bindValue(":name", ui->souvenirName->text());
    query.bindValue(":price", ui->souvenirPrice->text());
    query.bindValue(":quantity", ui->souvenirQuantity->text());
    query.bindValue(":college", this->colleges1.at(collegeIndex).getCollegeID());

    if(query.exec())
    {
        qDebug() << "Success";
    } else {
        qDebug() << "Failed";
    }
}

void SouvenirEditWindow::on_deleteSouvenirButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();
    int souvenirIndex = ui->souvenirBox->currentIndex() - 1;

    QSqlQuery query;

    query.prepare("DELETE FROM colleges_souvenirs WHERE souvenir = (:souvName)");
    query.bindValue(":souvName", this->souvenirs1.at(souvenirIndex));

    if(query.exec())
    {
        qDebug() << "Success";
    } else {
        qDebug() << "Failed";
    }
}

void SouvenirEditWindow::on_add_item_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void SouvenirEditWindow::on_delete_item_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
