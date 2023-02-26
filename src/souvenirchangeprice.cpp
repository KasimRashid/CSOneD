#include "souvenirchangeprice.h"
#include "ui_souvenirchangeprice.h"
#include "adminwindow.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QList>

SouvenirChangePrice::SouvenirChangePrice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SouvenirChangePrice)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::database();
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

SouvenirChangePrice::~SouvenirChangePrice()
{
    delete ui;
}

void SouvenirChangePrice::on_pushChange_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery souvenir_qry("SELECT * FROM colleges_souvenirs");
    int souvenirIndex = ui->souvenirBox->currentIndex() - 1;

    souvenir_qry.prepare("UPDATE colleges_souvenirs SET price = (:price) WHERE souvenir = (:name)");
    souvenir_qry.bindValue(":name", this->souvenirs1.at(souvenirIndex));
    souvenir_qry.bindValue(":price", ui->priceEdit->text());

    if(souvenir_qry.exec())
    {
        qDebug() << "Success";
    } else {
        qDebug() << "Failed";
    }
}

void SouvenirChangePrice::on_pushButton_clicked()
{
    AdminWindow *admin = new AdminWindow;
    admin->show();
    this->close();
}
