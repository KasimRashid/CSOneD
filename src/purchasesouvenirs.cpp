#include "purchasesouvenirs.h"
#include "ui_purchasesouvenirs.h"

/**
 * @brief purchaseSouvenirs::purchaseSouvenirs
 * @param parent
 */
purchaseSouvenirs::purchaseSouvenirs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::purchaseSouvenirs)
{
    ui->setupUi(this);


    // stretch vertical headers to fit table
    ui->tableWidget_receipt->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // center header text
    ui->tableWidget_receipt->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    // no editing elements
    ui->tableWidget_receipt->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // select entire rows instead of single cells
    ui->tableWidget_receipt->setSelectionBehavior(QAbstractItemView::SelectRows);

    // stretch vertical headers to fit table
    ui->tableWidget_total->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // center header text
    ui->tableWidget_total->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    // no editing elements
    ui->tableWidget_total->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // select entire rows instead of single cells
    ui->tableWidget_total->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_receipt->verticalHeader()->hide();
    ui->tableWidget_total->verticalHeader()->hide();

    //hide everything except choose the college label and comboBox
    ui->label_3->hide();
    ui->comboBox_souvenir->hide();
    ui->label_4->hide();
    ui->lineEdit_quanity->hide();
    ui->pushButton_add->hide();
    ui->pushButton_receipt->hide();
    ui->label_add->hide();
    ui->tableWidget_receipt->hide();
    ui->tableWidget_total->hide();

    // populate vectors
    populate();

    //making comboBox to show the colleges names
    ui->comboBox_college->insertItem(0," (Choose a college) ");
    for(int i=0; i<collegesList.length(); i++)
    {
        ui->comboBox_college->addItem(collegesList.at(i).getCollegeName());
    }


}

/**
 * @brief purchaseSouvenirs::~purchaseSouvenirs
 */
purchaseSouvenirs::~purchaseSouvenirs()
{
    delete ui;
}

/**
 * @brief purchaseSouvenirs::populate
 */
void purchaseSouvenirs::populate()
{

    // reading from the SQL database into the College vector
    QSqlQuery colleges_qry("SELECT * FROM College_Touring");

    while (colleges_qry.next()) {
        // push back College
        collegesList.push_back(College(colleges_qry.record().value("ID").toInt(),
                                colleges_qry.record().value("Universities").toString()));
    }

    // read from the SQL Database into the Souvenir vector
    QSqlQuery souvenirs_qry("SELECT * FROM colleges_souvenirs");

    while (souvenirs_qry.next()) {
        // push back Souvenir
        souvenirsList.push_back(Souvenir(College(souvenirs_qry.record().value("ID").toInt(),
                                                 souvenirs_qry.record().value("Universities").toString()),
                                         souvenirs_qry.record().value("souvenir").toString(),
                                         souvenirs_qry.record().value("price").toDouble()));
    }
}

/**
 * @brief purchaseSouvenirs::on_comboBox_college_currentIndexChanged
 * @param index
 */
void purchaseSouvenirs::on_comboBox_college_currentIndexChanged(int index)
{
    ui->comboBox_souvenir->clear();

    if(index > 0) {
        ui->label_3->show();
        ui->comboBox_souvenir->show();
        ui->label_4->show();
        ui->lineEdit_quanity->show();

        //store the chosen college into the collegeName
        collegeName = collegesList.at(index-1).getCollegeName();

        //make comboBix_souvenir to show the souvenirs if the chosen college
        ui->comboBox_souvenir->insertItem(0," (Choose a souvenir) ");
        for(int i=0; i<souvenirsList.length(); i++)
        {
            if(collegeName == souvenirsList.at(i).getSouvenirCollege().getCollegeName())
            {
                ui->comboBox_souvenir->addItem(souvenirsList.at(i).getSouvenirName());
                tempSouvenirName.push_back(souvenirsList.at(i).getSouvenirName());
                tempSouvenirPrice.push_back(souvenirsList.at(i).getSouvenirPrice());

            }
        }

    }
}

/**
 * @brief purchaseSouvenirs::on_comboBox_souvenir_currentIndexChanged
 * @param index
 */
void purchaseSouvenirs::on_comboBox_souvenir_currentIndexChanged(int index)
{
    if(index > 0) {
        ui->pushButton_add->show();
        souvenirName.push_back(tempSouvenirName.at(index-1));
        souvenirPrice.push_back(tempSouvenirPrice.at(index-1));
    }
}

/**
 * @brief purchaseSouvenirs::on_pushButton_add_clicked
 */
void purchaseSouvenirs::on_pushButton_add_clicked()
{
    //if lineEdit is empty, push 1 to vector
    if(ui->lineEdit_quanity->text().isEmpty())
    {
        souvenirQuantity.push_back(1);
        ui->label_add->show();
        ui->pushButton_receipt->show();
        QTimer::singleShot(2000, ui->label_add, &QLabel::hide);
    }
    else
    {
        //if lineEdit is not empty, push ehat user entered into the vector
        souvenirQuantity.push_back((ui->lineEdit_quanity->text()).toInt());
        ui->label_add->show();
        ui->pushButton_receipt->show();
        QTimer::singleShot(2000, ui->label_add, &QLabel::hide);

    }
}

/**
 * @brief purchaseSouvenirs::on_pushButton_receipt_clicked
 */
void purchaseSouvenirs::on_pushButton_receipt_clicked()
{
   ui->tableWidget_receipt->show();
   ui->tableWidget_total->show();

   //set receipt coloumn titels
   ui->tableWidget_receipt->setRowCount(0);

   ui->tableWidget_receipt->setColumnCount(3);
   ui->tableWidget_receipt->setHorizontalHeaderItem(0, new QTableWidgetItem("Souvenir"));
   ui->tableWidget_receipt->setHorizontalHeaderItem(1, new QTableWidgetItem("Quantity"));
   ui->tableWidget_receipt->setHorizontalHeaderItem(2, new QTableWidgetItem("Price"));

   double itemTotal;        //stores thre quantity * price for each item
   double total = 0;        //stores the total cost
   for (int i = 0; i < souvenirName.size(); i++) {
       ui->tableWidget_receipt->insertRow(ui->tableWidget_receipt->rowCount());
       ui->tableWidget_receipt->setItem(ui->tableWidget_receipt->rowCount() - 1, 0,
                                          new QTableWidgetItem(souvenirName.at(i)));
       ui->tableWidget_receipt->setItem(ui->tableWidget_receipt->rowCount() - 1, 1,
                                          new QTableWidgetItem(QString::number(souvenirQuantity.at(i))));
       ui->tableWidget_receipt->setItem(ui->tableWidget_receipt->rowCount() - 1, 2,
                                          new QTableWidgetItem("$" + QString::number((souvenirQuantity.at(i))*(souvenirPrice.at(i)))));
       itemTotal = (souvenirQuantity.at(i))*(souvenirPrice.at(i));
       total = total + itemTotal;
   }

   double tax = total * .075;
   double totalTax = total + tax;
   ui->tableWidget_total->setRowCount(0);
   ui->tableWidget_total->setColumnCount(2);

   ui->tableWidget_total->setHorizontalHeaderItem(0, new QTableWidgetItem("TOTAL"));
   ui->tableWidget_total->setHorizontalHeaderItem(1, new QTableWidgetItem("TOTAL+TAX(7.5%"));
   ui->tableWidget_total->insertRow(ui->tableWidget_total->rowCount());
   ui->tableWidget_total->setItem(ui->tableWidget_total->rowCount() - 1, 0,
                                      new QTableWidgetItem("$" + QString::number(total)));
   ui->tableWidget_total->setItem(ui->tableWidget_total->rowCount() - 1, 1,
                                      new QTableWidgetItem("$" + QString::number(totalTax)));

}
