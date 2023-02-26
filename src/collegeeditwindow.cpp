#include "collegeeditwindow.h"
#include "ui_collegeeditwindow.h"
#include "mainwindow.h"
#include "adminwindow.h"
#include <QString>
#include <QSqlQuery>
#include <QList>
#include <QSqlDatabase>

CollegeEditWindow::CollegeEditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CollegeEditWindow)
{
    ui->setupUi(this);
}

CollegeEditWindow::~CollegeEditWindow()
{
    delete ui;
}

void CollegeEditWindow::on_addCollegeButton_clicked()
{
    QString collegeName = ui->collegeBox->currentText();
    int collegeID = -1;

    if (collegeName == "University of Texas")
        collegeID = 3658;
    else if (collegeName == "California State University, Fullerton")
        collegeID = 1137;

    // default connection
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.open()) {
        qDebug() << "Failed to open database";
        fail();
        return;
    }

    QSqlQuery college_query;
    college_query.prepare("INSERT INTO College_Touring (ID,Universities) VALUES (:collegeID,:collegeName)");
    college_query.bindValue(":collegeID", collegeID);
    college_query.bindValue(":collegeName", collegeName);

    if (!college_query.exec()) {
        qDebug() << "Add college failed: " << college_query.lastError();
        fail();
        return;
    }

    // souvenir struct
    struct DBSouvenir {
        int collegeID;
        QString souvenirName;
        double price;
        int quantity;
        QString collegeName;
    };

    // add respective souvenirs to souvenir struct vector
    QList<DBSouvenir> souvenirs;
    if (collegeName == "University of Texas") {
        souvenirs.push_back({3658, "Car Magnet", 7.86, 3, "University of Texas"});
        souvenirs.push_back({3658, "Cufflinks", 56.87, 1, "University of Texas"});
        souvenirs.push_back({3658, "Ring", 88.98, 3, "University of Texas"});
        souvenirs.push_back({3658, "Watch", 104.69, 4, "University of Texas"});
    } else if (collegeName == "California State University, Fullerton") {
        souvenirs.push_back({1137, "Coaster Set",	12.73, 0, "California State University, Fullerton"});
        souvenirs.push_back({1137, "Lawn Chair", 88.79, 1, "California State University, Fullerton"});
        souvenirs.push_back({1137, "Reclininig Chair", 165.99, 1, "California State University, Fullerton"});
        souvenirs.push_back({1137, "Temporary tattoos", 7.99, 3, "California State University, Fullerton"});
        souvenirs.push_back({1137, "Water Bottle", 9.85, 6, "California State University, Fullerton"});
    }

    // write souvenirs to database
    QSqlQuery souvenir_query;
    souvenir_query.prepare("INSERT INTO colleges_souvenirs (ID,souvenir,price,Quantity,Universities) VALUES (:collegeID,:souvenirName,:price,:quantity,:collegeName)");
    for (int i = 0; i < souvenirs.size(); ++i) {
        souvenir_query.bindValue(":collegeID", souvenirs.at(i).collegeID);
        souvenir_query.bindValue(":souvenirName", souvenirs.at(i).souvenirName);
        souvenir_query.bindValue(":price", souvenirs.at(i).price);
        souvenir_query.bindValue(":quantity", souvenirs.at(i).quantity);
        souvenir_query.bindValue(":collegeName", souvenirs.at(i).collegeName);

        if (!souvenir_query.exec()) {
            qDebug() << "Add college failed: " << college_query.lastError();
            fail();
            return;
        }
    }

    // success
    ui->error_label->setStyleSheet("color:green");
    ui->error_label->setText("Success");
}

void CollegeEditWindow::fail()
{
    ui->error_label->setStyleSheet("color:red");
    ui->error_label->setText("Failed to add College");
}

void CollegeEditWindow::on_pushButton_2_clicked()
{
    AdminWindow *admin = new AdminWindow;
    admin->show();
    this->close();
}
