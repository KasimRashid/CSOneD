#include "tourpurchase.h"
#include "ui_tourpurchase.h"
#include <QDebug>

QVector<int> tourpurchase::keys;
QVector<int> tourpurchase::selectedTourColleges;
QVector<Souvenir> tourpurchase::souvenirList;
//double tourpurchase::total = 0.0;
//int tourpurchase::souvenirCount = 0;
//int tourpurchase::pageIndicator = 0;

/**
 * @brief tourpurchase::tourpurchase
 * @param parent
 */
tourpurchase::tourpurchase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tourpurchase)
{
    ui->setupUi(this);

    //total = 0.0;
    souvenirCount = 0;
    tempCount = 0;
    pageIndicator = 0;

    ui->purchase_stackedWidget->setCurrentIndex(0);
    ui->pushButton_quantityAsu->hide();
    ui->lineEdit_quantity_asu->hide();
    ui->label_QAsu->hide();
    ui->label_totalAsu->hide();
    ui->tableWidget_totalAsu->hide();
    ui->pushButton_quantityUci->hide();
    ui->lineEdit_quantity_uci->hide();
    ui->label_QUci->hide();
    ui->label_totalUci->hide();
    ui->tableWidget_totalUci->hide();
    ui->pushButton_quantityMit->hide();
    ui->lineEdit_quantity_Mit->hide();
    ui->label_QMit->hide();
    ui->label_totalMit->hide();
    ui->tableWidget_totalMit->hide();
    ui->pushButton_quantityNorthwestern->hide();
    ui->lineEdit_quantity_northwestern->hide();
    ui->label_QNorthwestern->hide();
    ui->label_totalNorthwestern->hide();
    ui->tableWidget_totalNorthwestern->hide();
    ui->pushButton_quantityOhio->hide();
    ui->lineEdit_quantity_Ohio->hide();
    ui->label_QOhio->hide();
    ui->label_totalOhio->hide();
    ui->tableWidget_totalOhio->hide();
    ui->pushButton_quantitySaddleback->hide();
    ui->lineEdit_quantity_saddleback->hide();
    ui->label_QSaddleback->hide();
    ui->label_totalsaddleback->hide();
    ui->tableWidget_totalsaddleback->hide();
    ui->pushButton_quantityFullerton->hide();
    ui->lineEdit_quantity_fullerton->hide();
    ui->label_QFullerton->hide();
    ui->label_totalcsuf->hide();
    ui->tableWidget_totalcsuf->hide();
    ui->pushButton_quantityMichigan->hide();
    ui->lineEdit_quantity_michigan->hide();
    ui->label_QMichigan->hide();
    ui->label_totalmichigan->hide();
    ui->tableWidget_totalmichigan->hide();
    ui->pushButton_quantityUcla->hide();
    ui->lineEdit_quantity_ucla->hide();
    ui->label_QUcla->hide();
    ui->label_totalUcla_2->hide();
    ui->tableWidget_totalucla_2->hide();
    ui->pushButton_quantityOregon->hide();
    ui->lineEdit_quantity_Oregon->hide();
    ui->label_QOregon->hide();
    ui->label_totaloregon_2->hide();
    ui->tableWidget_totaloregon_2->hide();
    ui->pushButton_quantityTexas->hide();
    ui->lineEdit_quantity_texas->hide();
    ui->label_QTexas->hide();
    ui->label_totaltexas->hide();
    ui->tableWidget_totaltexas->hide();
    ui->pushButton_quantityPacific->hide();
    ui->lineEdit_quantity_pacific->hide();
    ui->label_QPacific->hide();
    ui->label_totalPacific->hide();
    ui->tableWidget_totalPacific->hide();
    ui->pushButton_quantityWisconsin->hide();
    ui->lineEdit_quantity_Wisconsin->hide();
    ui->label_QWisconsin->hide();
    ui->label_totalWisconsin->hide();
    ui->tableWidget_totalWisconsin->hide();
}

/**
 * @brief tourpurchase::~tourpurchase
 */
tourpurchase::~tourpurchase()
{
    delete ui;
}

/**
 * @brief tourpurchase::tourpurchase
 * @param tour_keys
 * @param chosenTour
 * @param souvenirs
 */
tourpurchase::tourpurchase(QVector<int> tour_keys, QVector<int> chosenTour, QVector<Souvenir> souvenirs)
{
    selectedTourColleges.clear();
    souvenirList.clear();
    keys.clear();

    selectedTourColleges = chosenTour;
    souvenirList = souvenirs;
    keys = tour_keys;


}

/**
 * @brief tourpurchase::on_shopping_button_clicked
 */
void tourpurchase::on_shopping_button_clicked()
{
    qDebug() << "Key Size" << keys.size();
    qDebug() << "Souvenir List " << souvenirList.size();

    findPage(keys.at(0));
    displaySouvenirs(0);
}

/**
 * @brief tourpurchase::displaySouvenirs
 * @param count
 */
void tourpurchase::displaySouvenirs(int count)
{
    tempSouvenirs.clear();

      for(int index = 0; index < souvenirList.size(); index++) {
          if(selectedTourColleges.at(count) == souvenirList.at(index).getSouvenirCollege().getCollegeID()) {
            tempSouvenirs.push_back(souvenirList.at(index));
          }
      }

      tourPurchasesTable(keys.at(count));

      if(count < keys.size()-1) {
         pageIndicator = keys.at(count + 1);
         count++;
      } else {
          count = 0;
          pageIndicator = keys.at(count);
      }
      tempCount = count;
}

/**
 * @brief tourpurchase::findPage
 * @param index
 */
void tourpurchase::findPage(int index)
{
    switch (index) {
    case 1:  ui->purchase_stackedWidget->setCurrentIndex(index);
        break;
    case 2:  ui->purchase_stackedWidget->setCurrentIndex(index);
        break;
    case 3:  ui->purchase_stackedWidget->setCurrentIndex(index);
        break;
    case 4:  ui->purchase_stackedWidget->setCurrentIndex(index);
        break;
    case 5:  ui->purchase_stackedWidget->setCurrentIndex(index);
        break;
    case 6:  ui->purchase_stackedWidget->setCurrentIndex(index);
        break;
    case 7:  ui->purchase_stackedWidget->setCurrentIndex(index);
        break;
    case 8:  ui->purchase_stackedWidget->setCurrentIndex(index);
        break;
    case 9:  ui->purchase_stackedWidget->setCurrentIndex(index);
        break;
    case 10: ui->purchase_stackedWidget->setCurrentIndex(index);
        break;
    case 11: ui->purchase_stackedWidget->setCurrentIndex(index);
        break;
    case 12: ui->purchase_stackedWidget->setCurrentIndex(index);
        break;
    case 13: ui->purchase_stackedWidget->setCurrentIndex(index);
        break;
    }
}

/**
 * @brief tourpurchase::tourPurchasesTable
 * @param count
 */
void tourpurchase::tourPurchasesTable(int count)
{
    switch(count) {
    case 1:
        ui->tableWidget_arizona->setRowCount(0);
        ui->tableWidget_arizona->setColumnCount(2);
        ui->tableWidget_arizona->setHorizontalHeaderItem(0, new QTableWidgetItem("Souvenir"));
        ui->tableWidget_arizona->setHorizontalHeaderItem(1, new QTableWidgetItem("Price $"));
        ui->tableWidget_arizona->verticalHeader()->hide();
        ui->tableWidget_arizona->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

        for(int index = 0; index < tempSouvenirs.size(); index++) {
            ui->tableWidget_arizona->insertRow(ui->tableWidget_arizona->rowCount());
            ui->tableWidget_arizona->setItem(ui->tableWidget_arizona->rowCount() - 1, 0,
                                               new QTableWidgetItem(tempSouvenirs.at(index).getSouvenirName()));
            ui->tableWidget_arizona->setItem(ui->tableWidget_arizona->rowCount() - 1, 1,
                                               new QTableWidgetItem(QString::number(tempSouvenirs.at(index).getSouvenirPrice())));
            ui->tableWidget_arizona->item(ui->tableWidget_arizona->rowCount() - 1, 0)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_arizona->item(ui->tableWidget_arizona->rowCount() - 1, 1)->setTextAlignment(Qt::AlignCenter);
        }
        break;
    case 2:
        ui->tableWidget_irvine->setRowCount(0);
        ui->tableWidget_irvine->setColumnCount(2);
        ui->tableWidget_irvine->setHorizontalHeaderItem(0, new QTableWidgetItem("Souvenir"));
        ui->tableWidget_irvine->setHorizontalHeaderItem(1, new QTableWidgetItem("Price $"));
        ui->tableWidget_irvine->verticalHeader()->hide();
        ui->tableWidget_irvine->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

        for(int index = 0; index < tempSouvenirs.size(); index++) {
            ui->tableWidget_irvine->insertRow(ui->tableWidget_irvine->rowCount());
            ui->tableWidget_irvine->setItem(ui->tableWidget_irvine->rowCount() - 1, 0,
                                               new QTableWidgetItem(tempSouvenirs.at(index).getSouvenirName()));
            ui->tableWidget_irvine->setItem(ui->tableWidget_irvine->rowCount() - 1, 1,
                                               new QTableWidgetItem(QString::number(tempSouvenirs.at(index).getSouvenirPrice())));
            ui->tableWidget_irvine->item(ui->tableWidget_irvine->rowCount() - 1, 0)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_irvine->item(ui->tableWidget_irvine->rowCount() - 1, 1)->setTextAlignment(Qt::AlignCenter);
        }
        break;
    case 3:
        ui->tableWidget_Mit->setRowCount(0);
        ui->tableWidget_Mit->setColumnCount(2);
        ui->tableWidget_Mit->setHorizontalHeaderItem(0, new QTableWidgetItem("Souvenir"));
        ui->tableWidget_Mit->setHorizontalHeaderItem(1, new QTableWidgetItem("Price $"));
        ui->tableWidget_Mit->verticalHeader()->hide();
        ui->tableWidget_Mit->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

        for(int index = 0; index < tempSouvenirs.size(); index++) {
            ui->tableWidget_Mit->insertRow(ui->tableWidget_Mit->rowCount());
            ui->tableWidget_Mit->setItem(ui->tableWidget_Mit->rowCount() - 1, 0,
                                               new QTableWidgetItem(tempSouvenirs.at(index).getSouvenirName()));
            ui->tableWidget_Mit->setItem(ui->tableWidget_Mit->rowCount() - 1, 1,
                                               new QTableWidgetItem(QString::number(tempSouvenirs.at(index).getSouvenirPrice())));
            ui->tableWidget_Mit->item(ui->tableWidget_Mit->rowCount() - 1, 0)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_Mit->item(ui->tableWidget_Mit->rowCount() - 1, 1)->setTextAlignment(Qt::AlignCenter);
        }
        break;
    case 4:
        ui->tableWidget_northwestern->setRowCount(0);
        ui->tableWidget_northwestern->setColumnCount(2);
        ui->tableWidget_northwestern->setHorizontalHeaderItem(0, new QTableWidgetItem("Souvenir"));
        ui->tableWidget_northwestern->setHorizontalHeaderItem(1, new QTableWidgetItem("Price $"));
        ui->tableWidget_northwestern->verticalHeader()->hide();
        ui->tableWidget_northwestern->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

        for(int index = 0; index < tempSouvenirs.size(); index++) {
            ui->tableWidget_northwestern->insertRow(ui->tableWidget_northwestern->rowCount());
            ui->tableWidget_northwestern->setItem(ui->tableWidget_northwestern->rowCount() - 1, 0,
                                               new QTableWidgetItem(tempSouvenirs.at(index).getSouvenirName()));
            ui->tableWidget_northwestern->setItem(ui->tableWidget_northwestern->rowCount() - 1, 1,
                                               new QTableWidgetItem(QString::number(tempSouvenirs.at(index).getSouvenirPrice())));
            ui->tableWidget_northwestern->item(ui->tableWidget_northwestern->rowCount() - 1, 0)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_northwestern->item(ui->tableWidget_northwestern->rowCount() - 1, 1)->setTextAlignment(Qt::AlignCenter);
        }
        break;
    case 5:
        ui->tableWidget_ohio->setRowCount(0);
        ui->tableWidget_ohio->setColumnCount(2);
        ui->tableWidget_ohio->setHorizontalHeaderItem(0, new QTableWidgetItem("Souvenir"));
        ui->tableWidget_ohio->setHorizontalHeaderItem(1, new QTableWidgetItem("Price $"));
        ui->tableWidget_ohio->verticalHeader()->hide();
        ui->tableWidget_ohio->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

        for(int index = 0; index < tempSouvenirs.size(); index++) {
            ui->tableWidget_ohio->insertRow(ui->tableWidget_ohio->rowCount());
            ui->tableWidget_ohio->setItem(ui->tableWidget_ohio->rowCount() - 1, 0,
                                               new QTableWidgetItem(tempSouvenirs.at(index).getSouvenirName()));
            ui->tableWidget_ohio->setItem(ui->tableWidget_ohio->rowCount() - 1, 1,
                                               new QTableWidgetItem(QString::number(tempSouvenirs.at(index).getSouvenirPrice())));
            ui->tableWidget_ohio->item(ui->tableWidget_ohio->rowCount() - 1, 0)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_ohio->item(ui->tableWidget_ohio->rowCount() - 1, 1)->setTextAlignment(Qt::AlignCenter);
        }
        break;
    case 6:
        ui->tableWidget_saddleback->setRowCount(0);
        ui->tableWidget_saddleback->setColumnCount(2);
        ui->tableWidget_saddleback->setHorizontalHeaderItem(0, new QTableWidgetItem("Souvenir"));
        ui->tableWidget_saddleback->setHorizontalHeaderItem(1, new QTableWidgetItem("Price $"));
        ui->tableWidget_saddleback->verticalHeader()->hide();
        ui->tableWidget_saddleback->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

        for(int index = 0; index < tempSouvenirs.size(); index++) {
            ui->tableWidget_saddleback->insertRow(ui->tableWidget_saddleback->rowCount());
            ui->tableWidget_saddleback->setItem(ui->tableWidget_saddleback->rowCount() - 1, 0,
                                               new QTableWidgetItem(tempSouvenirs.at(index).getSouvenirName()));
            ui->tableWidget_saddleback->setItem(ui->tableWidget_saddleback->rowCount() - 1, 1,
                                               new QTableWidgetItem(QString::number(tempSouvenirs.at(index).getSouvenirPrice())));
            ui->tableWidget_saddleback->item(ui->tableWidget_saddleback->rowCount() - 1, 0)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_saddleback->item(ui->tableWidget_saddleback->rowCount() - 1, 1)->setTextAlignment(Qt::AlignCenter);
        }
        break;
    case 7:
        ui->tableWidget_csuf->setRowCount(0);
        ui->tableWidget_csuf->setColumnCount(2);
        ui->tableWidget_csuf->setHorizontalHeaderItem(0, new QTableWidgetItem("Souvenir"));
        ui->tableWidget_csuf->setHorizontalHeaderItem(1, new QTableWidgetItem("Price $"));
        ui->tableWidget_csuf->verticalHeader()->hide();
        ui->tableWidget_csuf->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

        for(int index = 0; index < tempSouvenirs.size(); index++) {
            ui->tableWidget_csuf->insertRow(ui->tableWidget_csuf->rowCount());
            ui->tableWidget_csuf->setItem(ui->tableWidget_csuf->rowCount() - 1, 0,
                                               new QTableWidgetItem(tempSouvenirs.at(index).getSouvenirName()));
            ui->tableWidget_csuf->setItem(ui->tableWidget_csuf->rowCount() - 1, 1,
                                               new QTableWidgetItem(QString::number(tempSouvenirs.at(index).getSouvenirPrice())));
            ui->tableWidget_csuf->item(ui->tableWidget_csuf->rowCount() - 1, 0)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_csuf->item(ui->tableWidget_csuf->rowCount() - 1, 1)->setTextAlignment(Qt::AlignCenter);
        }
        break;
    case 8:
        ui->tableWidget_michigan->setRowCount(0);
        ui->tableWidget_michigan->setColumnCount(2);
        ui->tableWidget_michigan->setHorizontalHeaderItem(0, new QTableWidgetItem("Souvenir"));
        ui->tableWidget_michigan->setHorizontalHeaderItem(1, new QTableWidgetItem("Price $"));
        ui->tableWidget_michigan->verticalHeader()->hide();
        ui->tableWidget_michigan->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

        for(int index = 0; index < tempSouvenirs.size(); index++) {
            ui->tableWidget_michigan->insertRow(ui->tableWidget_michigan->rowCount());
            ui->tableWidget_michigan->setItem(ui->tableWidget_michigan->rowCount() - 1, 0,
                                               new QTableWidgetItem(tempSouvenirs.at(index).getSouvenirName()));
            ui->tableWidget_michigan->setItem(ui->tableWidget_michigan->rowCount() - 1, 1,
                                               new QTableWidgetItem(QString::number(tempSouvenirs.at(index).getSouvenirPrice())));
            ui->tableWidget_michigan->item(ui->tableWidget_michigan->rowCount() - 1, 0)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_michigan->item(ui->tableWidget_michigan->rowCount() - 1, 1)->setTextAlignment(Qt::AlignCenter);
        }
        break;
    case 9:
        ui->tableWidget_ucla->setRowCount(0);
        ui->tableWidget_ucla->setColumnCount(2);
        ui->tableWidget_ucla->setHorizontalHeaderItem(0, new QTableWidgetItem("Souvenir"));
        ui->tableWidget_ucla->setHorizontalHeaderItem(1, new QTableWidgetItem("Price $"));
        ui->tableWidget_ucla->verticalHeader()->hide();
        ui->tableWidget_ucla->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

        for(int index = 0; index < tempSouvenirs.size(); index++) {
            ui->tableWidget_ucla->insertRow(ui->tableWidget_ucla->rowCount());
            ui->tableWidget_ucla->setItem(ui->tableWidget_ucla->rowCount() - 1, 0,
                                               new QTableWidgetItem(tempSouvenirs.at(index).getSouvenirName()));
            ui->tableWidget_ucla->setItem(ui->tableWidget_ucla->rowCount() - 1, 1,
                                               new QTableWidgetItem(QString::number(tempSouvenirs.at(index).getSouvenirPrice())));
            ui->tableWidget_ucla->item(ui->tableWidget_ucla->rowCount() - 1, 0)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_ucla->item(ui->tableWidget_ucla->rowCount() - 1, 1)->setTextAlignment(Qt::AlignCenter);
        }
        break;
    case 10:
        ui->tableWidget_oregon->setRowCount(0);
        ui->tableWidget_oregon->setColumnCount(2);
        ui->tableWidget_oregon->setHorizontalHeaderItem(0, new QTableWidgetItem("Souvenir"));
        ui->tableWidget_oregon->setHorizontalHeaderItem(1, new QTableWidgetItem("Price $"));
        ui->tableWidget_oregon->verticalHeader()->hide();
        ui->tableWidget_oregon->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

        for(int index = 0; index < tempSouvenirs.size(); index++) {
            ui->tableWidget_oregon->insertRow(ui->tableWidget_oregon->rowCount());
            ui->tableWidget_oregon->setItem(ui->tableWidget_oregon->rowCount() - 1, 0,
                                               new QTableWidgetItem(tempSouvenirs.at(index).getSouvenirName()));
            ui->tableWidget_oregon->setItem(ui->tableWidget_oregon->rowCount() - 1, 1,
                                               new QTableWidgetItem(QString::number(tempSouvenirs.at(index).getSouvenirPrice())));
            ui->tableWidget_oregon->item(ui->tableWidget_oregon->rowCount() - 1, 0)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_oregon->item(ui->tableWidget_oregon->rowCount() - 1, 1)->setTextAlignment(Qt::AlignCenter);
        }
        break;
    case 11:
        ui->tableWidget_texas->setRowCount(0);
        ui->tableWidget_texas->setColumnCount(2);
        ui->tableWidget_texas->setHorizontalHeaderItem(0, new QTableWidgetItem("Souvenir"));
        ui->tableWidget_texas->setHorizontalHeaderItem(1, new QTableWidgetItem("Price $"));
        ui->tableWidget_texas->verticalHeader()->hide();
        ui->tableWidget_texas->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

        for(int index = 0; index < tempSouvenirs.size(); index++) {
            ui->tableWidget_texas->insertRow(ui->tableWidget_texas->rowCount());
            ui->tableWidget_texas->setItem(ui->tableWidget_texas->rowCount() - 1, 0,
                                               new QTableWidgetItem(tempSouvenirs.at(index).getSouvenirName()));
            ui->tableWidget_texas->setItem(ui->tableWidget_texas->rowCount() - 1, 1,
                                               new QTableWidgetItem(QString::number(tempSouvenirs.at(index).getSouvenirPrice())));
            ui->tableWidget_texas->item(ui->tableWidget_texas->rowCount() - 1, 0)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_texas->item(ui->tableWidget_texas->rowCount() - 1, 1)->setTextAlignment(Qt::AlignCenter);
        }
        break;
    case 12:
        ui->tableWidget_Pacific->setRowCount(0);
        ui->tableWidget_Pacific->setColumnCount(2);
        ui->tableWidget_Pacific->setHorizontalHeaderItem(0, new QTableWidgetItem("Souvenir"));
        ui->tableWidget_Pacific->setHorizontalHeaderItem(1, new QTableWidgetItem("Price $"));
        ui->tableWidget_Pacific->verticalHeader()->hide();
        ui->tableWidget_Pacific->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

        for(int index = 0; index < tempSouvenirs.size(); index++) {
            ui->tableWidget_Pacific->insertRow(ui->tableWidget_Pacific->rowCount());
            ui->tableWidget_Pacific->setItem(ui->tableWidget_Pacific->rowCount() - 1, 0,
                                               new QTableWidgetItem(tempSouvenirs.at(index).getSouvenirName()));
            ui->tableWidget_Pacific->setItem(ui->tableWidget_Pacific->rowCount() - 1, 1,
                                               new QTableWidgetItem(QString::number(tempSouvenirs.at(index).getSouvenirPrice())));
            ui->tableWidget_Pacific->item(ui->tableWidget_Pacific->rowCount() - 1, 0)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_Pacific->item(ui->tableWidget_Pacific->rowCount() - 1, 1)->setTextAlignment(Qt::AlignCenter);
        }
        break;
    case 13:
        ui->tableWidget_Wisconsin->setRowCount(0);
        ui->tableWidget_Wisconsin->setColumnCount(2);
        ui->tableWidget_Wisconsin->setHorizontalHeaderItem(0, new QTableWidgetItem("Souvenir"));
        ui->tableWidget_Wisconsin->setHorizontalHeaderItem(1, new QTableWidgetItem("Price $"));
        ui->tableWidget_Wisconsin->verticalHeader()->hide();
        ui->tableWidget_Wisconsin->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

        for(int index = 0; index < tempSouvenirs.size(); index++) {
            ui->tableWidget_Wisconsin->insertRow(ui->tableWidget_Wisconsin->rowCount());
            ui->tableWidget_Wisconsin->setItem(ui->tableWidget_Wisconsin->rowCount() - 1, 0,
                                               new QTableWidgetItem(tempSouvenirs.at(index).getSouvenirName()));
            ui->tableWidget_Wisconsin->setItem(ui->tableWidget_Wisconsin->rowCount() - 1, 1,
                                               new QTableWidgetItem(QString::number(tempSouvenirs.at(index).getSouvenirPrice())));
            ui->tableWidget_Wisconsin->item(ui->tableWidget_Wisconsin->rowCount() - 1, 0)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_Wisconsin->item(ui->tableWidget_Wisconsin->rowCount() - 1, 1)->setTextAlignment(Qt::AlignCenter);
        }
        break;
    }
}

/**
 * @brief tourpurchase::on_pushButton_clicked
 */
void tourpurchase::on_pushButton_clicked()
{
    tourCampuses *t = new tourCampuses;

    t->show();
    this->close();
}

/**
 * @brief tourpurchase::on_pushButton_selectPurchase_asu_clicked
 */
void tourpurchase::on_pushButton_selectPurchase_asu_clicked()
{
    ui->pushButton_quantityAsu->show();
    ui->label_QAsu->show();
    ui->lineEdit_quantity_asu->show();

    QModelIndex current = ui->tableWidget_arizona->currentIndex();
    prices.append(ui->tableWidget_arizona->item(current.row(),1)->text().toDouble());
    souvenirName.append(ui->tableWidget_arizona->item(current.row(),0)->text());
    collegeName.append(tempSouvenirs.at(0).getSouvenirCollege().getCollegeName());
}

/**
 * @brief tourpurchase::on_pushButton_quantityAsu_clicked
 */
void tourpurchase::on_pushButton_quantityAsu_clicked()
{
    ui->label_totalAsu->show();
    ui->tableWidget_totalAsu->show();

    int quantityChosen = ui->lineEdit_quantity_asu->text().toInt();
    quantity.push_back(quantityChosen);

    total[pageIndicator] = total[pageIndicator] + (quantity.at(souvenirCount) * prices.at(souvenirCount));

    ui->tableWidget_totalAsu->setRowCount(1);
    ui->tableWidget_totalAsu->setColumnCount(1);
    ui->tableWidget_totalAsu->setHorizontalHeaderItem(0, new QTableWidgetItem("Total"));
    ui->tableWidget_totalAsu->verticalHeader()->hide();
    ui->tableWidget_totalAsu->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_totalAsu->setItem(0,0, new QTableWidgetItem("$" + QString::number(total[pageIndicator])));
    ui->tableWidget_totalAsu->item(0,0)->setTextAlignment(Qt::AlignCenter);
    souvenirCount += 1;
}

/**
 * @brief tourpurchase::on_pushButton_selectPurchase_uci_clicked
 */
void tourpurchase::on_pushButton_selectPurchase_uci_clicked()
{
    ui->pushButton_quantityUci->show();
    ui->label_QUci->show();
    ui->lineEdit_quantity_uci->show();

    QModelIndex current = ui->tableWidget_irvine->currentIndex();
    prices.append(ui->tableWidget_irvine->item(current.row(),1)->text().toDouble());
    souvenirName.append(ui->tableWidget_irvine->item(current.row(),0)->text());
    collegeName.append(tempSouvenirs.at(0).getSouvenirCollege().getCollegeName());
}

/**
 * @brief tourpurchase::on_pushButton_quantityUci_clicked
 */
void tourpurchase::on_pushButton_quantityUci_clicked()
{
    ui->label_totalUci->show();
    ui->tableWidget_totalUci->show();

    int quantityChosen = ui->lineEdit_quantity_uci->text().toInt();
    quantity.push_back(quantityChosen);

    total[pageIndicator] = total[pageIndicator] + (quantity.at(souvenirCount) * prices.at(souvenirCount));

    ui->tableWidget_totalUci->setRowCount(1);
    ui->tableWidget_totalUci->setColumnCount(1);
    ui->tableWidget_totalUci->setHorizontalHeaderItem(0, new QTableWidgetItem("Total"));
    ui->tableWidget_totalUci->verticalHeader()->hide();
    ui->tableWidget_totalUci->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_totalUci->setItem(0,0, new QTableWidgetItem("$" + QString::number(total[pageIndicator])));
    ui->tableWidget_totalUci->item(0,0)->setTextAlignment(Qt::AlignCenter);
    souvenirCount += 1;
}

/**
 * @brief tourpurchase::on_pushButton_selectPurchase_Mit_clicked
 */
void tourpurchase::on_pushButton_selectPurchase_Mit_clicked()
{
    ui->pushButton_quantityMit->show();
    ui->label_QMit->show();
    ui->lineEdit_quantity_Mit->show();

    QModelIndex current = ui->tableWidget_Mit->currentIndex();
    prices.append(ui->tableWidget_Mit->item(current.row(),1)->text().toDouble());
    souvenirName.append(ui->tableWidget_Mit->item(current.row(),0)->text());
    collegeName.append(tempSouvenirs.at(0).getSouvenirCollege().getCollegeName());
}

/**
 * @brief tourpurchase::on_pushButton_quantityMit_clicked
 */
void tourpurchase::on_pushButton_quantityMit_clicked()
{
    ui->label_totalMit->show();
    ui->tableWidget_totalMit->show();

    int quantityChosen = ui->lineEdit_quantity_Mit->text().toInt();
    quantity.push_back(quantityChosen);

    total[pageIndicator] = total[pageIndicator] + (quantity.at(souvenirCount) * prices.at(souvenirCount));

    ui->tableWidget_totalMit->setRowCount(1);
    ui->tableWidget_totalMit->setColumnCount(1);
    ui->tableWidget_totalMit->setHorizontalHeaderItem(0, new QTableWidgetItem("Total"));
    ui->tableWidget_totalMit->verticalHeader()->hide();
    ui->tableWidget_totalMit->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_totalMit->setItem(0,0, new QTableWidgetItem("$" + QString::number(total[pageIndicator])));
    ui->tableWidget_totalMit->item(0,0)->setTextAlignment(Qt::AlignCenter);
    souvenirCount += 1;
}

/**
 * @brief tourpurchase::on_pushButton_selectPurchase_Northwestern_clicked
 */
void tourpurchase::on_pushButton_selectPurchase_Northwestern_clicked()
{
    ui->pushButton_quantityNorthwestern->show();
    ui->label_QNorthwestern->show();
    ui->lineEdit_quantity_northwestern->show();

    QModelIndex current = ui->tableWidget_northwestern->currentIndex();
    prices.append(ui->tableWidget_northwestern->item(current.row(),1)->text().toDouble());
    souvenirName.append(ui->tableWidget_northwestern->item(current.row(),0)->text());
    collegeName.append(tempSouvenirs.at(0).getSouvenirCollege().getCollegeName());
}

/**
 * @brief tourpurchase::on_pushButton_quantityNorthwestern_clicked
 */
void tourpurchase::on_pushButton_quantityNorthwestern_clicked()
{
    ui->label_totalNorthwestern->show();
    ui->tableWidget_totalNorthwestern->show();

    int quantityChosen = ui->lineEdit_quantity_northwestern->text().toInt();
    quantity.push_back(quantityChosen);

    total[pageIndicator] = total[pageIndicator] + (quantity.at(souvenirCount) * prices.at(souvenirCount));

    ui->tableWidget_totalNorthwestern->setRowCount(1);
    ui->tableWidget_totalNorthwestern->setColumnCount(1);
    ui->tableWidget_totalNorthwestern->setHorizontalHeaderItem(0, new QTableWidgetItem("Total"));
    ui->tableWidget_totalNorthwestern->verticalHeader()->hide();
    ui->tableWidget_totalNorthwestern->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_totalNorthwestern->setItem(0,0, new QTableWidgetItem("$" + QString::number(total[pageIndicator])));
    ui->tableWidget_totalNorthwestern->item(0,0)->setTextAlignment(Qt::AlignCenter);
    souvenirCount += 1;
}

/**
 * @brief tourpurchase::on_pushButton_selectPurchase_ohio_clicked
 */
void tourpurchase::on_pushButton_selectPurchase_ohio_clicked()
{
    ui->pushButton_quantityOhio->show();
    ui->label_QOhio->show();
    ui->lineEdit_quantity_Ohio->show();

    QModelIndex current = ui->tableWidget_ohio->currentIndex();
    prices.append(ui->tableWidget_ohio->item(current.row(),1)->text().toDouble());
    souvenirName.append(ui->tableWidget_ohio->item(current.row(),0)->text());
    collegeName.append(tempSouvenirs.at(0).getSouvenirCollege().getCollegeName());
}

/**
 * @brief tourpurchase::on_pushButton_quantityOhio_clicked
 */
void tourpurchase::on_pushButton_quantityOhio_clicked()
{
    ui->label_totalOhio->show();
    ui->tableWidget_totalOhio->show();

    int quantityChosen = ui->lineEdit_quantity_Ohio->text().toInt();
    quantity.push_back(quantityChosen);

    total[pageIndicator] = total[pageIndicator] + (quantity.at(souvenirCount) * prices.at(souvenirCount));

    ui->tableWidget_totalOhio->setRowCount(1);
    ui->tableWidget_totalOhio->setColumnCount(1);
    ui->tableWidget_totalOhio->setHorizontalHeaderItem(0, new QTableWidgetItem("Total"));
    ui->tableWidget_totalOhio->verticalHeader()->hide();
    ui->tableWidget_totalOhio->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_totalOhio->setItem(0,0, new QTableWidgetItem("$" + QString::number(total[pageIndicator])));
    ui->tableWidget_totalOhio->item(0,0)->setTextAlignment(Qt::AlignCenter);
    souvenirCount += 1;
}

/**
 * @brief tourpurchase::on_pushButton_selectPurchase_saddleback_clicked
 */
void tourpurchase::on_pushButton_selectPurchase_saddleback_clicked()
{
    ui->pushButton_quantitySaddleback->show();
    ui->label_QSaddleback->show();
    ui->lineEdit_quantity_saddleback->show();

    QModelIndex current = ui->tableWidget_saddleback->currentIndex();
    prices.append(ui->tableWidget_saddleback->item(current.row(),1)->text().toDouble());
    souvenirName.append(ui->tableWidget_saddleback->item(current.row(),0)->text());
    collegeName.append(tempSouvenirs.at(0).getSouvenirCollege().getCollegeName());
}

/**
 * @brief tourpurchase::on_pushButton_quantitySaddleback_clicked
 */
void tourpurchase::on_pushButton_quantitySaddleback_clicked()
{
    ui->label_totalsaddleback->show();
    ui->tableWidget_totalsaddleback->show();

    int quantityChosen = ui->lineEdit_quantity_saddleback->text().toInt();
    quantity.push_back(quantityChosen);

    total[pageIndicator] = total[pageIndicator] + (quantity.at(souvenirCount) * prices.at(souvenirCount));

    ui->tableWidget_totalsaddleback->setRowCount(1);
    ui->tableWidget_totalsaddleback->setColumnCount(1);
    ui->tableWidget_totalsaddleback->setHorizontalHeaderItem(0, new QTableWidgetItem("Total"));
    ui->tableWidget_totalsaddleback->verticalHeader()->hide();
    ui->tableWidget_totalsaddleback->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_totalsaddleback->setItem(0,0, new QTableWidgetItem("$" + QString::number(total[pageIndicator])));
    ui->tableWidget_totalsaddleback->item(0,0)->setTextAlignment(Qt::AlignCenter);
    souvenirCount += 1;
}

/**
 * @brief tourpurchase::on_pushButton_selectPurchase_csuf_clicked
 */
void tourpurchase::on_pushButton_selectPurchase_csuf_clicked()
{
    ui->pushButton_quantityFullerton->show();
    ui->label_QFullerton->show();
    ui->lineEdit_quantity_fullerton->show();

    QModelIndex current = ui->tableWidget_csuf->currentIndex();
    prices.append(ui->tableWidget_csuf->item(current.row(),1)->text().toDouble());
    souvenirName.append(ui->tableWidget_csuf->item(current.row(),0)->text());
    collegeName.append(tempSouvenirs.at(0).getSouvenirCollege().getCollegeName());
}

/**
 * @brief tourpurchase::on_pushButton_quantityFullerton_clicked
 */
void tourpurchase::on_pushButton_quantityFullerton_clicked()
{
    ui->label_totalcsuf->show();
    ui->tableWidget_totalcsuf->show();

    int quantityChosen = ui->lineEdit_quantity_fullerton->text().toInt();
    quantity.push_back(quantityChosen);

    total[pageIndicator] = total[pageIndicator] + (quantity.at(souvenirCount) * prices.at(souvenirCount));

    ui->tableWidget_totalcsuf->setRowCount(1);
    ui->tableWidget_totalcsuf->setColumnCount(1);
    ui->tableWidget_totalcsuf->setHorizontalHeaderItem(0, new QTableWidgetItem("Total"));
    ui->tableWidget_totalcsuf->verticalHeader()->hide();
    ui->tableWidget_totalcsuf->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_totalcsuf->setItem(0,0, new QTableWidgetItem("$" + QString::number(total[pageIndicator])));
    ui->tableWidget_totalcsuf->item(0,0)->setTextAlignment(Qt::AlignCenter);
    souvenirCount += 1;
}

/**
 * @brief tourpurchase::on_pushButton_selectPurchase_michigan_clicked
 */
void tourpurchase::on_pushButton_selectPurchase_michigan_clicked()
{
    ui->pushButton_quantityMichigan->show();
    ui->label_QMichigan->show();
    ui->lineEdit_quantity_michigan->show();

    QModelIndex current = ui->tableWidget_michigan->currentIndex();
    prices.append(ui->tableWidget_michigan->item(current.row(),1)->text().toDouble());
    souvenirName.append(ui->tableWidget_michigan->item(current.row(),0)->text());
    collegeName.append(tempSouvenirs.at(0).getSouvenirCollege().getCollegeName());
}

/**
 * @brief tourpurchase::on_pushButton_quantityMichigan_clicked
 */
void tourpurchase::on_pushButton_quantityMichigan_clicked()
{
    ui->label_totalmichigan->show();
    ui->tableWidget_totalmichigan->show();

    int quantityChosen = ui->lineEdit_quantity_michigan->text().toInt();
    quantity.push_back(quantityChosen);

    total[pageIndicator] = total[pageIndicator] + (quantity.at(souvenirCount) * prices.at(souvenirCount));

    ui->tableWidget_totalmichigan->setRowCount(1);
    ui->tableWidget_totalmichigan->setColumnCount(1);
    ui->tableWidget_totalmichigan->setHorizontalHeaderItem(0, new QTableWidgetItem("Total"));
    ui->tableWidget_totalmichigan->verticalHeader()->hide();
    ui->tableWidget_totalmichigan->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_totalmichigan->setItem(0,0, new QTableWidgetItem("$" + QString::number(total[pageIndicator])));
    ui->tableWidget_totalmichigan->item(0,0)->setTextAlignment(Qt::AlignCenter);
    souvenirCount += 1;
}

/**
 * @brief tourpurchase::on_pushButton_selectPurchase_ucla_2_clicked
 */
void tourpurchase::on_pushButton_selectPurchase_ucla_2_clicked()
{
    ui->pushButton_quantityUcla->show();
    ui->label_QUcla->show();
    ui->lineEdit_quantity_ucla->show();

    QModelIndex current = ui->tableWidget_ucla->currentIndex();
    prices.append(ui->tableWidget_ucla->item(current.row(),1)->text().toDouble());
    souvenirName.append(ui->tableWidget_ucla->item(current.row(),0)->text());
    collegeName.append(tempSouvenirs.at(0).getSouvenirCollege().getCollegeName());
}

/**
 * @brief tourpurchase::on_pushButton_quantityUcla_clicked
 */
void tourpurchase::on_pushButton_quantityUcla_clicked()
{
    ui->label_totalUcla_2->show();
    ui->tableWidget_totalucla_2->show();

    int quantityChosen = ui->lineEdit_quantity_ucla->text().toInt();
    quantity.push_back(quantityChosen);

    total[pageIndicator] = total[pageIndicator] + (quantity.at(souvenirCount) * prices.at(souvenirCount));

    ui->tableWidget_totalucla_2->setRowCount(1);
    ui->tableWidget_totalucla_2->setColumnCount(1);
    ui->tableWidget_totalucla_2->setHorizontalHeaderItem(0, new QTableWidgetItem("Total"));
    ui->tableWidget_totalucla_2->verticalHeader()->hide();
    ui->tableWidget_totalucla_2->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_totalucla_2->setItem(0,0, new QTableWidgetItem("$" + QString::number(total[pageIndicator])));
    ui->tableWidget_totalucla_2->item(0,0)->setTextAlignment(Qt::AlignCenter);
    souvenirCount += 1;
}

/**
 * @brief tourpurchase::on_pushButton_selectPurchase_oregon_2_clicked
 */
void tourpurchase::on_pushButton_selectPurchase_oregon_2_clicked()
{
    ui->pushButton_quantityOregon->show();
    ui->label_QOregon->show();
    ui->lineEdit_quantity_Oregon->show();

    QModelIndex current = ui->tableWidget_oregon->currentIndex();
    prices.append(ui->tableWidget_oregon->item(current.row(),1)->text().toDouble());
    souvenirName.append(ui->tableWidget_oregon->item(current.row(),0)->text());
    collegeName.append(tempSouvenirs.at(0).getSouvenirCollege().getCollegeName());
}

/**
 * @brief tourpurchase::on_pushButton_quantityOregon_clicked
 */
void tourpurchase::on_pushButton_quantityOregon_clicked()
{
    ui->label_totaloregon_2->show();
    ui->tableWidget_totaloregon_2->show();

    int quantityChosen = ui->lineEdit_quantity_Oregon->text().toInt();
    quantity.push_back(quantityChosen);

    total[pageIndicator] = total[pageIndicator] + (quantity.at(souvenirCount) * prices.at(souvenirCount));

    ui->tableWidget_totaloregon_2->setRowCount(1);
    ui->tableWidget_totaloregon_2->setColumnCount(1);
    ui->tableWidget_totaloregon_2->setHorizontalHeaderItem(0, new QTableWidgetItem("Total"));
    ui->tableWidget_totaloregon_2->verticalHeader()->hide();
    ui->tableWidget_totaloregon_2->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_totaloregon_2->setItem(0,0, new QTableWidgetItem("$" + QString::number(total[pageIndicator])));
    ui->tableWidget_totaloregon_2->item(0,0)->setTextAlignment(Qt::AlignCenter);

    souvenirCount += 1;
}

/**
 * @brief tourpurchase::on_pushButton_selectPurchase_texas_clicked
 */
void tourpurchase::on_pushButton_selectPurchase_texas_clicked()
{
    ui->pushButton_quantityTexas->show();
    ui->label_QTexas->show();
    ui->lineEdit_quantity_texas->show();

    QModelIndex current = ui->tableWidget_texas->currentIndex();
    prices.append(ui->tableWidget_texas->item(current.row(),1)->text().toDouble());
    souvenirName.append(ui->tableWidget_texas->item(current.row(),0)->text());
    collegeName.append(tempSouvenirs.at(0).getSouvenirCollege().getCollegeName());
}

/**
 * @brief tourpurchase::on_pushButton_quantityTexas_clicked
 */
void tourpurchase::on_pushButton_quantityTexas_clicked()
{
    ui->label_totaltexas->show();
    ui->tableWidget_totaltexas->show();

    int quantityChosen = ui->lineEdit_quantity_texas->text().toInt();
    quantity.push_back(quantityChosen);

    total[pageIndicator] = total[pageIndicator] + (quantity.at(souvenirCount) * prices.at(souvenirCount));

    ui->tableWidget_totaltexas->setRowCount(1);
    ui->tableWidget_totaltexas->setColumnCount(1);
    ui->tableWidget_totaltexas->setHorizontalHeaderItem(0, new QTableWidgetItem("Total"));
    ui->tableWidget_totaltexas->verticalHeader()->hide();
    ui->tableWidget_totaltexas->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_totaltexas->setItem(0,0, new QTableWidgetItem("$" + QString::number(total[pageIndicator])));
    ui->tableWidget_totaltexas->item(0,0)->setTextAlignment(Qt::AlignCenter);

    souvenirCount += 1;
}

/**
 * @brief tourpurchase::on_pushButton_selectPurchase_Pacific_clicked
 */
void tourpurchase::on_pushButton_selectPurchase_Pacific_clicked()
{
    ui->pushButton_quantityPacific->show();
    ui->label_QPacific->show();
    ui->lineEdit_quantity_pacific->show();

    QModelIndex current = ui->tableWidget_Pacific->currentIndex();
    prices.append(ui->tableWidget_Pacific->item(current.row(),1)->text().toDouble());
    souvenirName.append(ui->tableWidget_Pacific->item(current.row(),0)->text());
    collegeName.append(tempSouvenirs.at(0).getSouvenirCollege().getCollegeName());
}

/**
 * @brief tourpurchase::on_pushButton_quantityPacific_clicked
 */
void tourpurchase::on_pushButton_quantityPacific_clicked()
{
    ui->label_totalPacific->show();
    ui->tableWidget_totalPacific->show();

    int quantityChosen = ui->lineEdit_quantity_pacific->text().toInt();
    quantity.push_back(quantityChosen);

    total[pageIndicator] = total[pageIndicator] + (quantity.at(souvenirCount) * prices.at(souvenirCount));

    ui->tableWidget_totalPacific->setRowCount(1);
    ui->tableWidget_totalPacific->setColumnCount(1);
    ui->tableWidget_totalPacific->setHorizontalHeaderItem(0, new QTableWidgetItem("Total"));
    ui->tableWidget_totalPacific->verticalHeader()->hide();
    ui->tableWidget_totalPacific->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_totalPacific->setItem(0,0, new QTableWidgetItem("$" + QString::number(total[pageIndicator])));
    ui->tableWidget_totalPacific->item(0,0)->setTextAlignment(Qt::AlignCenter);
    souvenirCount += 1;
}

/**
 * @brief tourpurchase::on_pushButton_selectPurchase_Wisconsin_clicked
 */
void tourpurchase::on_pushButton_selectPurchase_Wisconsin_clicked()
{
    ui->pushButton_quantityWisconsin->show();
    ui->label_QWisconsin->show();
    ui->lineEdit_quantity_Wisconsin->show();

    QModelIndex current = ui->tableWidget_Wisconsin->currentIndex();
    prices.append(ui->tableWidget_Wisconsin->item(current.row(),1)->text().toDouble());
    souvenirName.append(ui->tableWidget_Wisconsin->item(current.row(),0)->text());
    collegeName.append(tempSouvenirs.at(0).getSouvenirCollege().getCollegeName());
}

/**
 * @brief tourpurchase::on_pushButton_quantityWisconsin_clicked
 */
void tourpurchase::on_pushButton_quantityWisconsin_clicked()
{
    ui->label_totalWisconsin->show();
    ui->tableWidget_totalWisconsin->show();

    int quantityChosen = ui->lineEdit_quantity_Wisconsin->text().toInt();
    quantity.push_back(quantityChosen);

    total[pageIndicator] = total[pageIndicator] + (quantity.at(souvenirCount) * prices.at(souvenirCount));

    ui->tableWidget_totalWisconsin->setRowCount(1);
    ui->tableWidget_totalWisconsin->setColumnCount(1);
    ui->tableWidget_totalWisconsin->setHorizontalHeaderItem(0, new QTableWidgetItem("Total"));
    ui->tableWidget_totalWisconsin->verticalHeader()->hide();
    ui->tableWidget_totalWisconsin->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_totalWisconsin->setItem(0,0, new QTableWidgetItem("$" + QString::number(total[pageIndicator])));
    ui->tableWidget_totalWisconsin->item(0,0)->setTextAlignment(Qt::AlignCenter);
    souvenirCount += 1;
}

/**
 * @brief tourpurchase::on_next_3_clicked
 */
void tourpurchase::on_next_3_clicked() //ARIZONA
{
    findPage(pageIndicator);
    displaySouvenirs(tempCount);
}

/**
 * @brief tourpurchase::on_next_4_clicked
 */
void tourpurchase::on_next_4_clicked() //UCI
{
    findPage(pageIndicator);
    displaySouvenirs(tempCount);
}

/**
 * @brief tourpurchase::on_next_5_clicked
 */
void tourpurchase::on_next_5_clicked() //MIT
{
    findPage(pageIndicator);
    displaySouvenirs(tempCount);
}

/**
 * @brief tourpurchase::on_next_6_clicked
 */
void tourpurchase::on_next_6_clicked() //NORTHWESTERN
{
    findPage(pageIndicator);
    displaySouvenirs(tempCount);
}

/**
 * @brief tourpurchase::on_next_7_clicked
 */
void tourpurchase::on_next_7_clicked() //OHIO
{
    findPage(pageIndicator);
    displaySouvenirs(tempCount);
}

/**
 * @brief tourpurchase::on_next_8_clicked
 */
void tourpurchase::on_next_8_clicked() //SADDLEBACK
{
    findPage(pageIndicator);
    displaySouvenirs(tempCount);
}

/**
 * @brief tourpurchase::on_next_9_clicked
 */
void tourpurchase::on_next_9_clicked() //FULLERTON
{
    findPage(pageIndicator);
    displaySouvenirs(tempCount);
}

/**
 * @brief tourpurchase::on_next_10_clicked
 */
void tourpurchase::on_next_10_clicked() //MICHIGAN
{
    findPage(pageIndicator);
    displaySouvenirs(tempCount);
}

/**
 * @brief tourpurchase::on_next_11_clicked
 */
void tourpurchase::on_next_11_clicked() //UCLA
{
    findPage(pageIndicator);
    displaySouvenirs(tempCount);
}

/**
 * @brief tourpurchase::on_next_12_clicked
 */
void tourpurchase::on_next_12_clicked() //OREGON
{
    findPage(pageIndicator);
    displaySouvenirs(tempCount);
}

/**
 * @brief tourpurchase::on_next_13_clicked
 */
void tourpurchase::on_next_13_clicked() //TEXAS
{
    findPage(pageIndicator);
    displaySouvenirs(tempCount);
}

/**
 * @brief tourpurchase::on_next_14_clicked
 */
void tourpurchase::on_next_14_clicked() //PACIFIC
{
    findPage(pageIndicator);
    displaySouvenirs(tempCount);
}

/**
 * @brief tourpurchase::on_next_15_clicked
 */
void tourpurchase::on_next_15_clicked() //WISCONSIN
{
    findPage(pageIndicator);
    displaySouvenirs(tempCount);
}

/**
 * @brief tourpurchase::on_print_receipt_clicked
 */
void tourpurchase::on_print_receipt_clicked()
{
    qDebug() << "College Name: " << collegeName.size();
    qDebug() << "Souvenir Name: " << souvenirName.size();
    qDebug() << "Price: " << prices.size();
    qDebug() << "Quantity: " << quantity.size();

    ui->purchase_stackedWidget->setCurrentIndex(14);
    ui->tableWidget_receipt->setRowCount(0);
    ui->tableWidget_receipt->setColumnCount(4);
    ui->tableWidget_receipt->setHorizontalHeaderItem(0, new QTableWidgetItem("College Name"));
    ui->tableWidget_receipt->setHorizontalHeaderItem(1, new QTableWidgetItem("Souvenir Name"));
    ui->tableWidget_receipt->setHorizontalHeaderItem(2, new QTableWidgetItem("Price"));
    ui->tableWidget_receipt->setHorizontalHeaderItem(3, new QTableWidgetItem("Quantity"));
    ui->tableWidget_receipt->verticalHeader()->hide();
    ui->tableWidget_receipt->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_receipt->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    for(int index = 0; index < collegeName.size(); index++) {
        ui->tableWidget_receipt->insertRow(ui->tableWidget_receipt->rowCount());

        ui->tableWidget_receipt->setItem(ui->tableWidget_receipt->rowCount() - 1, 0,
                                           new QTableWidgetItem(collegeName.at(index)));
        ui->tableWidget_receipt->setItem(ui->tableWidget_receipt->rowCount() - 1, 1,
                                           new QTableWidgetItem(souvenirName.at(index)));
        ui->tableWidget_receipt->setItem(ui->tableWidget_receipt->rowCount() - 1, 2,
                                           new QTableWidgetItem("$" + QString::number(prices.at(index))));
        ui->tableWidget_receipt->setItem(ui->tableWidget_receipt->rowCount() - 1, 3,
                                           new QTableWidgetItem(QString::number(quantity.at(index))));

        ui->tableWidget_receipt->item(ui->tableWidget_receipt->rowCount() - 1, 0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_receipt->item(ui->tableWidget_receipt->rowCount() - 1, 1)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_receipt->item(ui->tableWidget_receipt->rowCount() - 1, 2)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_receipt->item(ui->tableWidget_receipt->rowCount() - 1, 3)->setTextAlignment(Qt::AlignCenter);
    }

    double totalPurchase = 0;
    for(int index = 0; index < 20; index++) {
        totalPurchase += total[index];
    }
    ui->tableWidget_totalPurchase->setRowCount(1);
    ui->tableWidget_totalPurchase->setColumnCount(1);
    ui->tableWidget_totalPurchase->setHorizontalHeaderItem(0, new QTableWidgetItem("Total Purchase"));
    ui->tableWidget_totalPurchase->verticalHeader()->hide();
    ui->tableWidget_totalPurchase->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_totalPurchase->setItem(0, 0, new QTableWidgetItem("$" + QString::number(totalPurchase)));
    ui->tableWidget_totalPurchase->item(0,0)->setTextAlignment(Qt::AlignCenter);
}

void tourpurchase::on_back_pushbutton_clicked()
{
    ui->purchase_stackedWidget->setCurrentIndex(pageIndicator);
}
