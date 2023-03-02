#include "adminpage.h"
#include "QDebug"
#include <iostream>
#include <string>
#include <QFileDialog>
#include <fstream>

adminpage::adminpage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminpage)
{
    ui->setupUi(this);
    // Sets default page to be the home page
    ui->stackedWidget->setCurrentWidget(ui->adminHomePage);
    setupConnections();

    showSouvenirComboBoxDeletePage(database_.loadCampusNamesOnly());
    showCampusComboBoxAddPage(database_.loadCampusNamesOnly());
    showchangeSouvenirPageCampusNameComboBox(database_.loadCampusNamesOnly());

}

adminpage::~adminpage()
{
    delete ui;
}

void adminpage::setupConnections()
{
    connect(ui->addSouvenirBtn, &QPushButton::clicked, this, &adminpage::changeToSouvenirPage);
    connect(ui->addSouvenirPageBackBtn, &QPushButton::clicked, this, &adminpage::changeToAdminHomePage);
    connect(ui->changeSouvenirPriceBtn, &QPushButton::click, this, &adminpage::changeToSouvenirPricePage);
    connect(ui->changeSouvPriceBackBtn, &QPushButton::click, this, &adminpage::changeToAdminHomePage);
    connect(ui->deleteSouvenirBtn, &QPushButton::click, this, &adminpage::changeToSouvenirDeletePage);
    connect(ui->deletePageBackBtn, &QPushButton::click, this, &adminpage::changeToAdminHomePage);
}

void adminpage::changeToAdminHomePage()
{
    ui->stackedWidget->setCurrentWidget(ui->adminHomePage);
}

void adminpage::changeToSouvenirPage()
{
    ui->stackedWidget->setCurrentWidget(ui->addSouvenirPage);
}

void adminpage::changeToSouvenirPricePage()
{
    ui->stackedWidget->setCurrentWidget(ui->changeSouvenirPricePage);
}

void adminpage::changeToSouvenirDeletePage()
{
    ui->stackedWidget->setCurrentWidget(ui->deleteSouvenirPage);


}

void adminpage::on_viewSouvenirBtn_clicked()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QSqlQuery* view = new QSqlQuery();

    view->prepare("SELECT * FROM Souvenirs ORDER by souvCollege ASC");

    view->exec();
    model->setQuery(*view);

    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0, 120);
}

void adminpage::on_viewDistancesBtn_clicked()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QSqlQuery* view = new QSqlQuery();

    view->prepare("SELECT * FROM Distances ORDER by distStart ASC");

    view->exec();
    model->setQuery(*view);

    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0, 120);
}

void adminpage::showSouvenirComboBoxDeletePage(QSqlQueryModel *model)
{
    ui->deletePageComboBox->setModel(model);
}

void adminpage::showCampusComboBoxAddPage(QSqlQueryModel * model)
{
    ui->addSouvenirPageCampusNameComboBox->setModel(model);
}

void adminpage::on_addCampusThroughInputFile_clicked()
{
    std::string startDist;
    std::string endDist;
    double numDist;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/Desktop", tr("Txt Files (*.txt)"));     /// user picks the txt file to choose from
    QFile file(fileName);

    std::ifstream inFile;
    inFile.open(fileName.toStdString());

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this,QObject::tr("System Message"),tr("File is invalid! Cannot be found."),QMessageBox::Ok);
        return;
    }
    else
    {
         while(inFile) {
            getline(inFile, startDist);
            getline(inFile, endDist);
            inFile >> numDist;
            inFile.ignore(10000,'\n');

            QString start_dist = QString::fromStdString(startDist);
            QString end_dist = QString::fromStdString(endDist);

            QSqlQuery query;
            query.prepare("INSERT INTO Distances(distStart, distEnd, distBtwn)"
                          " VALUES (:start_dist, :end_dist, :addDist)");
            query.bindValue(":start_dist", start_dist);
            query.bindValue(":end_dist", end_dist);
            query.bindValue(":addDist", numDist);

            if(query.exec())
            {
                qDebug() << "Query executed !";
            }
            else
            {
                qDebug() << "Query UNABLE to execute!";
                QMessageBox::information(this,QObject::tr("System Message"),tr("Failure to input the desired campus as it already exists!"),QMessageBox::Ok);
                break;
            }
        }
         QMessageBox::information(this,QObject::tr("System Message"),tr("Campus distances have been added!"),QMessageBox::Ok);
    }
}

void adminpage::on_addSouvenirThroughInputFile_clicked()
{
    std::string campusName;
    std::string souvenirName;
    double souvenirPrice;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/Desktop", tr("Txt Files (*.txt)"));     /// user picks the txt file to choose from
    QFile file(fileName);

    std::ifstream inFile;
    inFile.open(fileName.toStdString());

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this,QObject::tr("System Message"),tr("File is invalid! Cannot be found."),QMessageBox::Ok);
        return;
    }
    else
    {
         while(inFile) {
            getline(inFile, campusName);
            getline(inFile, souvenirName);
            inFile >> souvenirPrice;
            inFile.ignore(10000, '\n');

            QString souv_College = QString::fromStdString(campusName);
            QString souvTrad = QString::fromStdString(souvenirName);

            QSqlQuery query;
            query.prepare("INSERT INTO Souvenirs(souvCollege, souvTrad, souvCost)"
                          " VALUES (:souv_College, :souvTrad, :souvCost)");
            query.bindValue(":souv_College", souv_College);
            query.bindValue(":souvTrad", souvTrad);
            query.bindValue(":souvCost", souvenirPrice);

            if(query.exec())
            {
                qDebug() << "Query executed !";
            }
            else
            {
                qDebug() << "Query UNABLE to execute!";
                QMessageBox::information(this,QObject::tr("System Message"),tr("Failure to input the desired souvenir as it already exists!"),QMessageBox::Ok);
                break;
            }
        }
         QMessageBox::information(this,QObject::tr("System Message"),tr("Campus souvenirs have been added!"),QMessageBox::Ok);
    }
}

void adminpage::on_changeSouvPriceBackBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->adminHomePage);
}

void adminpage::showchangeSouvenirPageCampusNameComboBox(QSqlQueryModel * model)
{
    ui->changeSouvenirPageCampusNameComboBox->setModel(model);
}

void adminpage::on_changeSouvenirPriceBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->changeSouvenirPricePage);
}

void adminpage::on_updateSouvenirPriceBtn_clicked()
{
    QString souvCampus;
    QString souvTrad;
    QString souvPrice;

    souvCampus = ui->changeSouvenirPageCampusNameComboBox->currentText();
    souvTrad = ui->souvPriceChangeName_line->text();
    souvPrice = ui->souvChangePrice_line->text();

    bool check = false;

    for(int i = 0; i < souvPrice.length(); i++)
    {
        if(souvPrice[i] != '0' && souvPrice[i] != '1' && souvPrice[i] != '2' && souvPrice[i] != '3'
                && souvPrice[i] != '4' && souvPrice[i] != '5'
                && souvPrice[i] != '6' && souvPrice[i] != '7'
                && souvPrice[i] != '8' && souvPrice[i] != '9' && souvPrice[i] != '.')
        {
            check = true;
            break;
        }
    }

    if(check == true)
    {
        QMessageBox::about(this, "Invalid Input", "There was an invalid input. Please use only Numerals(0-9) and the . ");
        ui->stackedWidget->setCurrentWidget(ui->adminHomePage);
        return;
    }

    QSqlQuery qry;
    qry.prepare("UPDATE Souvenirs SET souvCollege = '"+souvCampus+"', souvTrad = '"+souvTrad+"' ,souvCost = '"+souvPrice+"' WHERE souvTrad = '"+souvTrad+"' AND souvCollege = '"+souvCampus+"' ");
    qry.exec();

    if(qry.numRowsAffected() == 0)
    {
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }
    else
    {
        QMessageBox::about(this, tr("Edit"), tr("Updated"));
    }

    ui->stackedWidget->setCurrentWidget(ui->adminHomePage);
}

void adminpage::on_addSouvenirBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->addSouvenirPage);
}

void adminpage::on_createSouvenirBtn_clicked()
{

    QSqlQuery data;
    QSqlQuery dataOne;
    QSqlQuery dataTwo;

    QString campusName = ui->addSouvenirPageCampusNameComboBox->currentText();
    QString souvName = ui->souvName_line->text();
    QString souvPrice = ui->souvPrice_line->text();

    bool check = false;

    for(int i = 0; i < souvPrice.length(); i++)
    {
        if(souvPrice[i] != '0' && souvPrice[i] != '1' && souvPrice[i] != '2' && souvPrice[i] != '3'
                && souvPrice[i] != '4' && souvPrice[i] != '5'
                && souvPrice[i] != '6' && souvPrice[i] != '7'
                && souvPrice[i] != '8' && souvPrice[i] != '9' && souvPrice[i] != '.')
        {
            check = true;
            break;
        }
    }

    if(check == true)
    {
        QMessageBox::about(this, "Invalid Input", "There was an invalid input. Please use only Numerals(0-9) and the . ");
        ui->stackedWidget->setCurrentWidget(ui->adminHomePage);
        return;
    }

    data.prepare("INSERT INTO Souvenirs (souvCollege, souvTrad, souvCost) VALUES ('"+campusName+"', '"+souvName+"', '"+souvPrice+"')");

    if(!data.exec())
    {
        QMessageBox::about(this, "Error", "Database not found double check path to database!");

    }
    else
    {
        QMessageBox::about(this, "", "The item was added. Double check if an error occured.");
    }

    ui->stackedWidget->setCurrentWidget(ui->adminHomePage);
}

void adminpage::on_deleteSouvenirBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->deleteSouvenirPage);
}

void adminpage::on_deletePageBackBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->adminHomePage);
}

void adminpage::on_deleteSouvenirConfirmBtn_clicked()
{
    int souvCount = 0;
    int afterSouvCount = 0;

    QString nameCampus = ui->deletePageComboBox->currentText();
    QString nameSouv = ui->deletePageSouvenirName_line->text();

    QSqlQuery data;
    QSqlQuery dataOne;
    QSqlQuery dataTwo;
    QSqlQuery qry;

    souvCount = data.prepare("SELECT COUNT(souvCollege) FROM Souvenirs");
    data.exec();

    if(data.next())
    {
        souvCount = data.value(0).toInt();
    }

    qry.prepare("DELETE FROM Souvenirs WHERE souvCollege = '"+nameCampus+"' AND souvTrad = '"+nameSouv+"'");
    qry.exec();
    dataOne.exec();

    afterSouvCount = dataTwo.prepare("SELECT COUNT(souvCollege) FROM Souvenirs");
    dataTwo.exec();

    if(dataTwo.next())
    {
        afterSouvCount = dataTwo.value(0).toInt();
    }

    if(souvCount == afterSouvCount)
    {
        QMessageBox::about(this, "Error", "Value not found double check path to database!");
    }
    else
    {
        QMessageBox::about(this, "", "The item was deleted. Double check if an error occured");

        ui->stackedWidget->setCurrentWidget(ui->adminHomePage);
    }
}
