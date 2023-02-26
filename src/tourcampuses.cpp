#include "tourcampuses.h"
#include "ui_tourcampuses.h"
#include "mainwindow.h"
#include "QModelIndex"
#include <QMessageBox>

/**
 * @brief tourCampuses::tourCampuses
 * @param parent
 */
tourCampuses::tourCampuses(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tourCampuses)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);
    ui->purchaseTour_pushButton->hide();

    populate();
    totalUciDistance = 0;
    totalMiDistance = 0;
    totalSaDistance = 0;
    counter = 0;

    ui->purchaseTour_MichiganTour->hide();
    ui->startingCampus_table->setRowCount(0);
    ui->startingCampus_table->setColumnCount(2);
    ui->startingCampus_table->setHorizontalHeaderItem(0, new QTableWidgetItem("IDs"));
    ui->startingCampus_table->setHorizontalHeaderItem(1, new QTableWidgetItem("Colleges"));
    ui->startingCampus_table->setColumnHidden(0,true);
    ui->startingCampus_table->verticalHeader()->hide();
    // stretch College name
    ui->startingCampus_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    ui->endingCampus_table->setRowCount(0);
    ui->endingCampus_table->setColumnCount(2);
    ui->endingCampus_table->setHorizontalHeaderItem(0, new QTableWidgetItem("IDs"));
    ui->endingCampus_table->setHorizontalHeaderItem(1, new QTableWidgetItem("Colleges"));
    ui->endingCampus_table->setColumnHidden(0,true);
    ui->endingCampus_table->verticalHeader()->hide();
    ui->endingCampus_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    ui->collegeList_table->setRowCount(0);
    ui->collegeList_table->setColumnCount(2);
    ui->collegeList_table->setHorizontalHeaderItem(0, new QTableWidgetItem("IDs"));
    ui->collegeList_table->setHorizontalHeaderItem(1, new QTableWidgetItem("Colleges"));
    ui->collegeList_table->setColumnHidden(0,true);
    ui->collegeList_table->verticalHeader()->hide();
    // stretch College name
    ui->collegeList_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    for (int i = 0; i < collegeList.size(); ++i) {
        ui->startingCampus_table->insertRow(ui->startingCampus_table->rowCount());
        ui->endingCampus_table->insertRow(ui->endingCampus_table->rowCount());
        ui->collegeList_table->insertRow(ui->collegeList_table->rowCount());

        ui->startingCampus_table->setItem(ui->startingCampus_table->rowCount() - 1, 0,
                                           new QTableWidgetItem(QString::number(collegeList.at(i).getCollegeID())));
        ui->startingCampus_table->setItem(ui->startingCampus_table->rowCount() - 1, 1,
                                           new QTableWidgetItem(collegeList.at(i).getCollegeName()));

        ui->endingCampus_table->setItem(ui->endingCampus_table->rowCount() - 1, 0,
                                           new QTableWidgetItem(QString::number(collegeList.at(i).getCollegeID())));
        ui->endingCampus_table->setItem(ui->endingCampus_table->rowCount() - 1, 1,
                                           new QTableWidgetItem(collegeList.at(i).getCollegeName()));

        ui->collegeList_table->setItem(ui->collegeList_table->rowCount() - 1, 0,
                                           new QTableWidgetItem(QString::number(collegeList.at(i).getCollegeID())));
        ui->collegeList_table->setItem(ui->collegeList_table->rowCount() - 1, 1,
                                           new QTableWidgetItem(collegeList.at(i).getCollegeName()));

        // center text
        for (int col = 0; col < ui->startingCampus_table->columnCount(); ++col) {
            ui->startingCampus_table->item(ui->startingCampus_table->rowCount() - 1, col)->setTextAlignment(Qt::AlignCenter);  
            ui->endingCampus_table->item(ui->endingCampus_table->rowCount() - 1, col)->setTextAlignment(Qt::AlignCenter);
            ui->collegeList_table->item(ui->collegeList_table->rowCount() - 1, col)->setTextAlignment(Qt::AlignCenter);
        }
    }
}

/**
 * @brief tourCampuses::~tourCampuses
 */
tourCampuses::~tourCampuses()
{
    delete ui;
}

/**
 * @brief tourCampuses::on_back_to_main_clicked
 */
void tourCampuses::on_back_to_main_clicked()
{
    MainWindow *main_window = new MainWindow;
    main_window->show();
    this->close();
}

/**
 * @brief tourCampuses::populate
 */
void tourCampuses::populate()
{
    // reading from the SQL database into the College vector
    QSqlQuery colleges_qry("SELECT * FROM College_Touring");

    while (colleges_qry.next()) {
        // push back College
        collegeList.push_back(College(colleges_qry.record().value("ID").toInt(),
                                colleges_qry.record().value("Universities").toString()));
    }
//    while (colleges_qry.next()) {
//        // push back College
//        collegeList.push_back(College(colleges_qry.record().value("ID").toInt(),
//                                colleges_qry.record().value("Universities").toString()));
//    }

    // read from the SQL Database into the Souvenir vector
    QSqlQuery souvenirs_qry("SELECT * FROM colleges_souvenirs");

    while (souvenirs_qry.next()) {
        // push back Souvenir
        souvenirsList.push_back(Souvenir(College(souvenirs_qry.record().value("ID").toInt(),
                                                 souvenirs_qry.record().value("Universities").toString()),
                                                 souvenirs_qry.record().value("souvenir").toString(),
                                                 souvenirs_qry.record().value("price").toDouble()));
    }

    // reading from the SQL Database into the Distance vector
    QSqlQuery distances_qry("SELECT * FROM distances");

    while (distances_qry.next()) {
        // find College by ID from existing list
        College startCollege(distances_qry.record().value("startingPointCollegeId").toInt(),
                             distances_qry.record().value("startingPointCollegeName").toString());
        College endCollege(distances_qry.record().value("endingPointCollegeId").toInt(),
                             distances_qry.record().value("endingPointCollegeName").toString());

        distanceList.push_back(Distance(startCollege, endCollege, distances_qry.record().value("distance").toDouble()));
    }
}

/**
 * @brief tourCampuses::on_pushButton_startColleges_clicked
 */
void tourCampuses::on_pushButton_startColleges_clicked()
{
    QModelIndex current = ui->startingCampus_table->currentIndex();
    IdsDistances[0] = ui->startingCampus_table->item(current.row(),0)->text().toInt();
}

void tourCampuses::on_endingCollege_pushButton_clicked()
{
    QModelIndex current = ui->endingCampus_table->currentIndex();
    IdsDistances[1] =  ui->endingCampus_table->item(current.row(),0)->text().toInt();

    findDistanceTwoCollege();
}

/**
 * @brief tourCampuses::findDistanceTwoCollege
 */
void tourCampuses::findDistanceTwoCollege()
{
    double distance;

    if(IdsDistances[0] == IdsDistances[1]) {
        distance = 0;
    } else {
    int index = 0;
        while(index < distanceList.size()) {
            if(IdsDistances[0] == distanceList.at(index).getStartCollege().getCollegeID() &&
               IdsDistances[1] == distanceList.at(index).getEndCollege().getCollegeID()) {
                distance = distanceList.at(index).getDistance();
            }
            index++;
        }
    }

    ui->distance_table->setRowCount(1);
    ui->distance_table->setColumnCount(1);
    ui->distance_table->verticalHeader()->hide();
    ui->distance_table->setHorizontalHeaderItem(0, new QTableWidgetItem("Distance (Miles)"));
    ui->distance_table->verticalHeader()->hide();
    ui->distance_table->setItem(0,0, new QTableWidgetItem(QString::number(distance)));
    ui->distance_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->distance_table->item(0,0)->setTextAlignment(Qt::AlignCenter);
}

/**
 * @brief tourCampuses::on_distanceMode_pushButton_clicked
 */
void tourCampuses::on_distanceMode_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

/**
 * @brief tourCampuses::on_tripMode_pushButton_clicked
 */
void tourCampuses::on_tripMode_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

/**
 * @brief tourCampuses::on_addColleges_button_clicked
 */
void tourCampuses::on_addColleges_button_clicked()
{
    College obj;
    QModelIndex current = ui->collegeList_table->currentIndex();
    if(!current.isValid()) {
        QMessageBox::warning(this, "Error", "Select A College from the table!");
    } else {
        obj.setCollegeId(ui->collegeList_table->item(current.row(),0)->text().toInt());
        obj.setCollegeName(ui->collegeList_table->item(current.row(),1)->text());
        selectedColleges.push_back(obj);

    displaySelectedColleges();
    }
}

/**
 * @brief tourCampuses::on_deleteColleges_button_clicked
 */
void tourCampuses::on_deleteColleges_button_clicked()
{
    if(selectedColleges.empty()) {
        QMessageBox::warning(this, "Error", "There is no college selected!");
    } else {
        selectedColleges.pop_back();
        displaySelectedColleges();
    }
}

/**
 * @brief tourCampuses::displaySelectedColleges
 */
void tourCampuses::displaySelectedColleges()
{
    ui->selectedVisitColleges_table->setRowCount(0);
    ui->selectedVisitColleges_table->setColumnCount(2);
    ui->selectedVisitColleges_table->setHorizontalHeaderItem(0, new QTableWidgetItem("IDs"));
    ui->selectedVisitColleges_table->setHorizontalHeaderItem(1, new QTableWidgetItem("Colleges"));
    ui->selectedVisitColleges_table->setColumnHidden(0,true);
    ui->selectedVisitColleges_table->verticalHeader()->hide();

    // stretch College name
    ui->startingCampus_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    // stretch College name
    ui->selectedVisitColleges_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    for (int i = 0; i < selectedColleges.size(); ++i) {
        ui->selectedVisitColleges_table->insertRow(ui->selectedVisitColleges_table->rowCount());

        ui->selectedVisitColleges_table->setItem(ui->selectedVisitColleges_table->rowCount() - 1, 0,
                                           new QTableWidgetItem(QString::number(selectedColleges.at(i).getCollegeID())));
        ui->selectedVisitColleges_table->setItem(ui->selectedVisitColleges_table->rowCount() - 1, 1,
                                           new QTableWidgetItem(selectedColleges.at(i).getCollegeName()));

        // center text
        for (int col = 0; col < ui->selectedVisitColleges_table->columnCount(); ++col) {
            ui->selectedVisitColleges_table->item(ui->selectedVisitColleges_table->
                                                  rowCount() - 1, col)->setTextAlignment(Qt::AlignCenter);

        }
    }
}

/**
 * @brief tourCampuses::on_beginTrip_pushButton_clicked
 */
void tourCampuses::on_beginTrip_pushButton_clicked()
{
    if(selectedColleges.empty()) {
        return;
    } else {
        findTrip(0,0,0);
        ui->purchaseTour_pushButton->show();
    }
}

/**
 * @brief tourCampuses::findTrip
 * @param count
 * @param visitedCollege
 * @param totalDistance
 */
void tourCampuses::findTrip(int count, int visitedCollege, double totalDistance)
{
    if(count == 0) {
        ui->trip_table->setRowCount(0);
        ui->trip_table->setColumnCount(3);
        ui->trip_table->setHorizontalHeaderItem(0, new QTableWidgetItem("Visiting Colleges"));
        ui->trip_table->setHorizontalHeaderItem(1, new QTableWidgetItem("Distance"));
        ui->trip_table->setHorizontalHeaderItem(2, new QTableWidgetItem("IDs"));
        ui->trip_table->setColumnHidden(1,true);
       // ui->trip_table->setColumnHidden(2,true);
        ui->trip_table->verticalHeader()->hide();
        ui->trip_table->insertRow(ui->trip_table->rowCount());
        ui->trip_table->setItem(ui->trip_table->rowCount() - 1, 0,
                                           new QTableWidgetItem(selectedColleges.at(0).getCollegeName()));
        ui->trip_table->setItem(ui->trip_table->rowCount() - 1, 2,
                                           new QTableWidgetItem(QString::number(selectedColleges.at(0).getCollegeID())));
        ui->trip_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    }

    if(selectedColleges.empty()) {
        count = 0;
        ui->totalDistanceTraveled_table->setRowCount(0);
        ui->totalDistanceTraveled_table->setColumnCount(1);
        ui->totalDistanceTraveled_table->verticalHeader()->hide();
        ui->totalDistanceTraveled_table->setHorizontalHeaderItem(0, new QTableWidgetItem("Total Distance"));
        ui->totalDistanceTraveled_table->insertRow(ui->totalDistanceTraveled_table->rowCount());
        ui->totalDistanceTraveled_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        ui->totalDistanceTraveled_table->setItem(ui->totalDistanceTraveled_table->rowCount() - 1,0,
                                                 new QTableWidgetItem(QString::number(totalDistance)));
        ui->totalDistanceTraveled_table->item(0,0)->setTextAlignment(Qt::AlignCenter);
        return;
    } else {
        Distance distObj;
        College  initCollegeObj;
        College  endCollegeObj;
        int index = 0;
        // finds the first college visited in the database
        while(selectedColleges.at(visitedCollege).getCollegeID() !=
              distanceList.at(index).getStartCollege().getCollegeID()) {
            index++;
        }
        // creating the vector for all the visiting colleges
        for(int counter = 1; counter < selectedColleges.size(); counter++) {
            for(int i = index; i < distanceList.size()/*collegeList.size() - 1 + index*/; i++) {
                if(selectedColleges.at(counter).getCollegeID() == distanceList.at(i).getEndCollege().getCollegeID()) {
                    initCollegeObj.setCollege(selectedColleges.at(visitedCollege).getCollegeName(),
                                              selectedColleges.at(visitedCollege).getCollegeID());
                    endCollegeObj.setCollege(distanceList.at(i).getEndCollege().getCollegeName(),
                                             distanceList.at(i).getEndCollege().getCollegeID());
                    distObj.setDistance(initCollegeObj, endCollegeObj, distanceList.at(i).getDistance());
                    tourDistanceColleges.push_back(distObj);
                }
            }
        }
        // sorting the colleges visited
        for(int j = 1; j < tourDistanceColleges.size(); j++) {
            Distance temp = tourDistanceColleges.at(j);
            int k = j - 1;
            while(k >= 0 && tourDistanceColleges.at(k).getDistance() > temp.getDistance()) {
                tourDistanceColleges.replace(k+1, tourDistanceColleges.at(k));
                k = k - 1;
            }
            tourDistanceColleges.replace(k+1, temp);
        }
        ui->trip_table->insertRow(ui->trip_table->rowCount());
        ui->trip_table->setItem(ui->trip_table->rowCount() - 1, 0,
                                new QTableWidgetItem(tourDistanceColleges.at(0).getEndCollege().getCollegeName()));
        ui->trip_table->setItem(ui->trip_table->rowCount() - 1, 2,
                                new QTableWidgetItem(QString::number(tourDistanceColleges.at(0).getEndCollege().getCollegeID())));
        int r = 0;
        while(tourDistanceColleges.at(0).getEndCollege().getCollegeID() != selectedColleges.at(r).getCollegeID()) {
            r++;
        }
        totalDistance += tourDistanceColleges.at(0).getDistance();
        selectedColleges.pop_front();
        if(selectedColleges.size() == 1) {
            selectedColleges.pop_front();
        } else {
            College tempObj = selectedColleges.at(0);
            selectedColleges.replace(0, selectedColleges.at(r - 1));
            selectedColleges.replace(r - 1, tempObj);
        }
        tourDistanceColleges.clear();
        findTrip(count + 1, 0, totalDistance);
    }
}

/**
 * @brief tourCampuses::on_pushButton_UCI_clicked
 */
void tourCampuses::on_pushButton_UCI_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

    //store all the colleges into the uciTourColleges
    for(int i=0; i<collegeList.size(); i++)
    {
        uciTourColleges.push_back(collegeList.at(i));
        qDebug() << uciTourColleges.at(i).getCollegeID();
    }

    int k;
     for(int i=0; i< uciTourColleges.size(); i++) {
         if(uciTourColleges.at(i).getCollegeID() == 1314) {
             k = i;
         }
     }

     //switching uci with the first element
      College temp1 = uciTourColleges.at(0);
      College temp2 = uciTourColleges.at(k);
      uciTourColleges.replace(k, temp1);
      uciTourColleges.replace(0, temp2);

      qDebug() <<"---------------------------";
      for(int i=0; i<collegeList.size(); i++)
      {
          qDebug() << uciTourColleges.at(i).getCollegeID();
      }

    findUciTrip(0,0);


    ui->distance_table_uci->setRowCount(1);
    ui->distance_table_uci->setColumnCount(1);
    ui->distance_table_uci->verticalHeader()->hide();
    ui->distance_table_uci->setHorizontalHeaderItem(0, new QTableWidgetItem("Miles"));
    ui->distance_table_uci->verticalHeader()->hide();
    ui->distance_table_uci->setItem(0,0, new QTableWidgetItem(QString::number(totalUciDistance)));
    ui->distance_table_uci->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->distance_table_uci->item(0,0)->setTextAlignment(Qt::AlignCenter);
}

/**
 * @brief tourCampuses::findUciTrip
 * @param count
 * @param uciVisitedColleges
 */
void tourCampuses::findUciTrip(int count, int uciVisitedColleges)
{
    if(count == 0) {
        ui->trip_table_uci->setRowCount(0);
        ui->trip_table_uci->setColumnCount(2);
        ui->trip_table_uci->setHorizontalHeaderItem(0, new QTableWidgetItem("Visiting Colleges"));
        ui->trip_table_uci->setHorizontalHeaderItem(1, new QTableWidgetItem("IDs"));
        //ui->trip_table_uci->setColumnHidden(1,true);
        ui->trip_table_uci->verticalHeader()->hide();
        ui->trip_table_uci->insertRow(ui->trip_table_uci->rowCount());
        ui->trip_table_uci->setItem(ui->trip_table_uci->rowCount() - 1, 0,
                                           new QTableWidgetItem(uciTourColleges.at(0).getCollegeName()));
        ui->trip_table_uci->setItem(ui->trip_table_uci->rowCount() - 1, 1,
                                           new QTableWidgetItem(QString::number(uciTourColleges.at(0).getCollegeID())));
        ui->trip_table_uci->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    }

    if(uciTourColleges.empty()) {
        count = 0;
        return;
    } else {
        Distance distObj;
        College  initCollegeObj;
        College  endCollegeObj;
        int index = 0;
        // finds the first college visited in the database
        while(uciTourColleges.at(uciVisitedColleges).getCollegeID() !=
              distanceList.at(index).getStartCollege().getCollegeID()) {
            index++;
        }
        // creating the vector for all the visiting colleges
        for(int counter = 1; counter < uciTourColleges.size(); counter++) {
            for(int i = index; i < distanceList.size(); i++) {
                if(uciTourColleges.at(counter).getCollegeID() == distanceList.at(i).getEndCollege().getCollegeID()) {
                    initCollegeObj.setCollege(uciTourColleges.at(uciVisitedColleges).getCollegeName(),
                                              uciTourColleges.at(uciVisitedColleges).getCollegeID());
                    endCollegeObj.setCollege(distanceList.at(i).getEndCollege().getCollegeName(),
                                             distanceList.at(i).getEndCollege().getCollegeID());
                    distObj.setDistance(initCollegeObj, endCollegeObj, distanceList.at(i).getDistance());
                    uciTourDistanceColleges.push_back(distObj);
                }
            }
        }
        // sorting the colleges visited
        for(int j = 1; j < uciTourDistanceColleges.size(); j++) {
            Distance temp = uciTourDistanceColleges.at(j);
            int k = j - 1;
            while(k >= 0 && uciTourDistanceColleges.at(k).getDistance() > temp.getDistance()) {
                uciTourDistanceColleges.replace(k+1, uciTourDistanceColleges.at(k));
                k = k - 1;
            }
            uciTourDistanceColleges.replace(k+1, temp);
        }
        ui->trip_table_uci->insertRow(ui->trip_table_uci->rowCount());
        ui->trip_table_uci->setItem(ui->trip_table_uci->rowCount() - 1, 0,
                                    new QTableWidgetItem(uciTourDistanceColleges.at(0).getEndCollege().getCollegeName()));
        ui->trip_table_uci->setItem(ui->trip_table_uci->rowCount() - 1, 1,
                                       new QTableWidgetItem(QString::number(uciTourDistanceColleges.at(0).getEndCollege().getCollegeID())));
        //----------------------------
        //calculating the total distance
        totalUciDistance = totalUciDistance + uciTourDistanceColleges.at(0).getDistance();
        //----------------------------
        int r = 0;
        while(uciTourDistanceColleges.at(0).getEndCollege().getCollegeID() != uciTourColleges.at(r).getCollegeID()) {
            r++;
        }
        uciTourColleges.pop_front();
        if(uciTourColleges.size() == 1) {
            uciTourColleges.pop_front();
        } else {
            College tempObj = uciTourColleges.at(0);
            uciTourColleges.replace(0, uciTourColleges.at(r - 1));
            uciTourColleges.replace(r - 1, tempObj);
        }
        uciTourDistanceColleges.clear();
        findUciTrip(count + 1, 0);
    }
}

/**
 * @brief tourCampuses::on_pushButton_MICHIGAN_clicked
 */
void tourCampuses::on_pushButton_MICHIGAN_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);

    //display all the colleges in trip_table_michigan_2
    ui->trip_table_michigan_2->setRowCount(0);
    ui->trip_table_michigan_2->setColumnCount(2);
    ui->trip_table_michigan_2->setHorizontalHeaderItem(0, new QTableWidgetItem("College Campuses"));
    ui->trip_table_michigan_2->setHorizontalHeaderItem(1, new QTableWidgetItem("ID"));
    //ui->trip_table_michigan_2->setColumnHidden(1,true);
    ui->trip_table_michigan_2->verticalHeader()->hide();
    ui->trip_table_michigan_2->insertRow(ui->trip_table_michigan_2->rowCount());
    ui->trip_table_michigan_2->setItem(ui->trip_table_michigan_2->rowCount() - 1, 0,
                                       new QTableWidgetItem(collegeList.at(0).getCollegeName()));
    ui->trip_table_michigan_2->setItem(ui->trip_table_michigan_2->rowCount() - 1, 1,
                                       new QTableWidgetItem(QString::number(collegeList.at(0).getCollegeID())));
    ui->trip_table_michigan_2->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    for(int k = 1; k< collegeList.size(); k++)
    {
        ui->trip_table_michigan_2->insertRow(ui->trip_table_michigan_2->rowCount());
        ui->trip_table_michigan_2->setItem(ui->trip_table_michigan_2->rowCount() - 1, 0,
                                           new QTableWidgetItem(collegeList.at(k).getCollegeName()));
        ui->trip_table_michigan_2->setItem(ui->trip_table_michigan_2->rowCount() - 1, 1,
                                            new QTableWidgetItem(QString::number(collegeList.at(k).getCollegeID())));
    }
}


void tourCampuses::on_pushButton_startMiTour_clicked()
{
    ui->purchaseTour_MichiganTour->show();

    //store all the colleges into the uciTourColleges
    for(int i=0; i<collegeList.size(); i++) {
        miTourColleges.push_back(collegeList.at(i));
    }

     int k;
      for(int i=0; i< miTourColleges.size(); i++) {
          if(miTourColleges.at(i).getCollegeID() == 2325) {
              k = i;
          }
      }

      //switching uci with the first element
       College temp1 = miTourColleges.at(0);
       College temp2 = miTourColleges.at(k);
       miTourColleges.replace(k, temp1);
       miTourColleges.replace(0, temp2);

     if(ui->lineEdit_collegeNum->text().isEmpty())
     {
         collegeNum = 1;
     }
     else
     {
         collegeNum = ui->lineEdit_collegeNum->text().toInt();
     }

    findMichiganTrip(0,0);

    ui->distance_table_mi->setRowCount(1);
    ui->distance_table_mi->setColumnCount(1);
    ui->distance_table_mi->verticalHeader()->hide();
    ui->distance_table_mi->setHorizontalHeaderItem(0, new QTableWidgetItem("Miles"));
    ui->distance_table_mi->verticalHeader()->hide();
    ui->distance_table_mi->setItem(0,0, new QTableWidgetItem(QString::number(totalMiDistance)));
    ui->distance_table_mi->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->distance_table_mi->item(0,0)->setTextAlignment(Qt::AlignCenter);

    miTourColleges.clear();
    miTourDistanceColleges.clear();
    ui->lineEdit_collegeNum->clear();
    counter = 0;
    totalMiDistance = 0;
}

/**
 * @brief tourCampuses::findMichiganTrip
 * @param count
 * @param miVisitedColleges
 */
void tourCampuses::findMichiganTrip(int count, int miVisitedColleges)
{
    if(counter < collegeNum) {
    if(count == 0) {
        ui->trip_table_michigan->setRowCount(0);
        ui->trip_table_michigan->setColumnCount(2);
        ui->trip_table_michigan->setHorizontalHeaderItem(0, new QTableWidgetItem("Visiting Colleges"));
        ui->trip_table_michigan->setHorizontalHeaderItem(1, new QTableWidgetItem("ID"));
       // ui->trip_table_michigan->setColumnHidden(1,true);
        ui->trip_table_michigan->verticalHeader()->hide();
        ui->trip_table_michigan->insertRow(ui->trip_table_michigan->rowCount());
        ui->trip_table_michigan->setItem(ui->trip_table_michigan->rowCount() - 1, 0,
                                           new QTableWidgetItem(miTourColleges.at(0).getCollegeName()));
        ui->trip_table_michigan->setItem(ui->trip_table_michigan->rowCount() - 1, 1,
                                           new QTableWidgetItem(QString::number(miTourColleges.at(0).getCollegeID())));
        ui->trip_table_michigan->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        counter = 1;
    }

    if(miTourColleges.empty()) {
        count = 0;
        return;
    } else {
        Distance distObj;
        College  initCollegeObj;
        College  endCollegeObj;
        int index = 0;
        // finds the first college visited in the database
        while(miTourColleges.at(miVisitedColleges).getCollegeID() !=
              distanceList.at(index).getStartCollege().getCollegeID()) {
            index++;
        }
        // creating the vector for all the visiting colleges
        for(int counter = 1; counter < miTourColleges.size(); counter++) {
            for(int i = index; i < distanceList.size(); i++) {
                if(miTourColleges.at(counter).getCollegeID() == distanceList.at(i).getEndCollege().getCollegeID()) {
                    initCollegeObj.setCollege(miTourColleges.at(miVisitedColleges).getCollegeName(),
                                              miTourColleges.at(miVisitedColleges).getCollegeID());
                    endCollegeObj.setCollege(distanceList.at(i).getEndCollege().getCollegeName(),
                                             distanceList.at(i).getEndCollege().getCollegeID());
                    distObj.setDistance(initCollegeObj, endCollegeObj, distanceList.at(i).getDistance());
                    miTourDistanceColleges.push_back(distObj);
                }
            }
        }
        // sorting the colleges visited
        for(int j = 1; j < miTourDistanceColleges.size(); j++) {
            Distance temp = miTourDistanceColleges.at(j);
            int k = j - 1;
            while(k >= 0 && miTourDistanceColleges.at(k).getDistance() > temp.getDistance()) {
                miTourDistanceColleges.replace(k+1, miTourDistanceColleges.at(k));
                k = k - 1;
            }
            miTourDistanceColleges.replace(k+1, temp);
        }
        ui->trip_table_michigan->insertRow(ui->trip_table_michigan->rowCount());
        ui->trip_table_michigan->setItem(ui->trip_table_michigan->rowCount() - 1, 0,
                                         new QTableWidgetItem(miTourDistanceColleges.at(0).getEndCollege().getCollegeName()));
        ui->trip_table_michigan->setItem(ui->trip_table_michigan->rowCount() - 1, 1,
                                           new QTableWidgetItem(QString::number(miTourDistanceColleges.at(0).getEndCollege().getCollegeID())));
        //----------------------------
        //calculating the total distance
        totalMiDistance = totalMiDistance + miTourDistanceColleges.at(0).getDistance();
        //----------------------------
        int r = 0;
        while(miTourDistanceColleges.at(0).getEndCollege().getCollegeID() != miTourColleges.at(r).getCollegeID()) {
            r++;
        }
        miTourColleges.pop_front();
        if(miTourColleges.size() == 1) {
            miTourColleges.pop_front();
        } else {
            College tempObj = miTourColleges.at(0);
            miTourColleges.replace(0, miTourColleges.at(r - 1));
            miTourColleges.replace(r - 1, tempObj);
        }
        miTourDistanceColleges.clear();
        counter++;
        findMichiganTrip(count + 1, 0);
    }
    }
}

/**
 * @brief tourCampuses::on_pushButton_SADDLEBACK_clicked
 */
void tourCampuses::on_pushButton_SADDLEBACK_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);

    //store all the colleges into the uciTourColleges
    for(int i=0; i<collegeList.size(); i++) {
        saTourColleges.push_back(collegeList.at(i));
    }

    int k;
     for(int i=0; i< saTourColleges.size(); i++) {
         if(saTourColleges.at(i).getCollegeID() == 8918) {
             k = i;
         }
     }

    //switching uci with the first element
     College temp1 = saTourColleges.at(0);
     College temp2 = saTourColleges.at(k);
     saTourColleges.replace(k, temp1);
     saTourColleges.replace(0, temp2);

    findSaddlebackTrip(0,0);

    ui->distance_table_sa->setRowCount(1);
    ui->distance_table_sa->setColumnCount(1);
    ui->distance_table_sa->verticalHeader()->hide();
    ui->distance_table_sa->setHorizontalHeaderItem(0, new QTableWidgetItem("Miles"));
    ui->distance_table_sa->verticalHeader()->hide();
    ui->distance_table_sa->setItem(0,0, new QTableWidgetItem(QString::number(totalSaDistance)));
    ui->distance_table_sa->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->distance_table_sa->item(0,0)->setTextAlignment(Qt::AlignCenter);

}

/**
 * @brief tourCampuses::findSaddlebackTrip
 * @param count
 * @param saVisitedColleges
 */
void tourCampuses::findSaddlebackTrip(int count, int saVisitedColleges)
{
    if(count == 0) {
        ui->trip_table_saddleback->setRowCount(0);
        ui->trip_table_saddleback->setColumnCount(2);
        ui->trip_table_saddleback->setHorizontalHeaderItem(0, new QTableWidgetItem("Visiting Colleges"));
        ui->trip_table_saddleback->setHorizontalHeaderItem(1, new QTableWidgetItem("IDs"));
        ui->trip_table_saddleback->setColumnHidden(1,true);
        ui->trip_table_saddleback->verticalHeader()->hide();
        ui->trip_table_saddleback->insertRow(ui->trip_table_saddleback->rowCount());
        ui->trip_table_saddleback->setItem(ui->trip_table_saddleback->rowCount() - 1, 0,
                                           new QTableWidgetItem(saTourColleges.at(0).getCollegeName()));
        ui->trip_table_saddleback->setItem(ui->trip_table_saddleback->rowCount() - 1, 1,
                                    new QTableWidgetItem(QString::number(saTourColleges.at(0).getCollegeID())));
        ui->trip_table_saddleback->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    }

    if(saTourColleges.empty()) {
        count = 0;
        return;
    } else {
        Distance distObj;
        College  initCollegeObj;
        College  endCollegeObj;
        int index = 0;
        // finds the first college visited in the database
        while(saTourColleges.at(saVisitedColleges).getCollegeID() !=
              distanceList.at(index).getStartCollege().getCollegeID()) {
            index++;
        }
        // creating the vector for all the visiting colleges
        for(int counter = 1; counter < saTourColleges.size(); counter++) {
            for(int i = index; i < distanceList.size(); i++) {
                if(saTourColleges.at(counter).getCollegeID() == distanceList.at(i).getEndCollege().getCollegeID()) {
                    initCollegeObj.setCollege(saTourColleges.at(saVisitedColleges).getCollegeName(),
                                              saTourColleges.at(saVisitedColleges).getCollegeID());
                    endCollegeObj.setCollege(distanceList.at(i).getEndCollege().getCollegeName(),
                                             distanceList.at(i).getEndCollege().getCollegeID());
                    distObj.setDistance(initCollegeObj, endCollegeObj, distanceList.at(i).getDistance());
                    saTourDistanceColleges.push_back(distObj);
                }
            }
        }
        // sorting the colleges visited
        for(int j = 1; j < saTourDistanceColleges.size(); j++) {
            Distance temp = saTourDistanceColleges.at(j);
            int k = j - 1;
            while(k >= 0 && saTourDistanceColleges.at(k).getDistance() > temp.getDistance()) {
                saTourDistanceColleges.replace(k+1, saTourDistanceColleges.at(k));
                k = k - 1;
            }
            saTourDistanceColleges.replace(k+1, temp);
        }
        ui->trip_table_saddleback->insertRow(ui->trip_table_saddleback->rowCount());
        ui->trip_table_saddleback->setItem(ui->trip_table_saddleback->rowCount() - 1, 0,
                                            new QTableWidgetItem(saTourDistanceColleges.at(0).getEndCollege().getCollegeName()));
        ui->trip_table_saddleback->setItem(ui->trip_table_saddleback->rowCount() - 1, 1,
                                    new QTableWidgetItem(QString::number(saTourDistanceColleges.at(0).getEndCollege().getCollegeID())));
        //----------------------------
        //calculating the total distance
        totalSaDistance = totalSaDistance + saTourDistanceColleges.at(0).getDistance();
        //----------------------------
        int r = 0;
        while(saTourDistanceColleges.at(0).getEndCollege().getCollegeID() != saTourColleges.at(r).getCollegeID()) {
            r++;
        }
        saTourColleges.pop_front();
        if(saTourColleges.size() == 1) {
            saTourColleges.pop_front();
        } else {
            College tempObj = saTourColleges.at(0);
            saTourColleges.replace(0, saTourColleges.at(r - 1));
            saTourColleges.replace(r - 1, tempObj);
        }
        saTourDistanceColleges.clear();
        findSaddlebackTrip(count + 1, 0);
    }
}

/**
 * @brief tourCampuses::on_purchaseTour_pushButton_clicked
 */
void tourCampuses::on_purchaseTour_pushButton_clicked()
{
    tourpurchase *p = new tourpurchase;
    p->show();
    this->close();

    //********************************************************************
    qDebug() << "***********************" << ui->trip_table->rowCount();
    //********************************************************************
    QVector<int> selectedTourCampuses;
    QVector<int> keys;

    for(int row = 0; row < ui->trip_table->rowCount(); row++) {
        int collegeId = ui->trip_table->item(row, 2)->text().toInt();

        if(collegeId == 1018) {           // ARIZONA
            keys.append(1);
        } else if(collegeId == 1314) {    // UCI
            keys.append(2);
        } else if(collegeId == 2178) {
            keys.append(3);
        } else if(collegeId == 1739) {
            keys.append(4);
        } else if(collegeId == 3090) {
            keys.append(5);
        } else if(collegeId == 8918) {
            keys.append(6);
        } else if(collegeId == 1137) {
            keys.append(7);
        } else if(collegeId == 2325) {
            keys.append(8);
        } else if(collegeId == 1315) {
            keys.append(9);
        } else if(collegeId == 3193) {
            keys.append(10);
        } else if(collegeId == 3658) {
            keys.append(11);
        } else if(collegeId == 1329) {
            keys.append(12);
        } else if(collegeId == 3897) {
            keys.append(13);
        }
        selectedTourCampuses.append(collegeId);
    }
    tourpurchase t(keys, selectedTourCampuses, souvenirsList);
}

void tourCampuses::on_purchaseTour_uciTour_clicked()
{
    tourpurchase *l = new tourpurchase;
    l->show();
    this->close();

    QVector<int> selectedTourCampuses;
    QVector<int> keys;

    for(int row = 0; row < ui->trip_table_uci->rowCount(); row++) {
        int collegeId = ui->trip_table_uci->item(row, 1)->text().toInt();

        if(collegeId == 1018) {           // ARIZONA
            keys.append(1);
        } else if(collegeId == 1314) {    // UCI
            keys.append(2);
        } else if(collegeId == 2178) {
            keys.append(3);
        } else if(collegeId == 1739) {
            keys.append(4);
        } else if(collegeId == 3090) {
            keys.append(5);
        } else if(collegeId == 8918) {
            keys.append(6);
        } else if(collegeId == 1137) {
            keys.append(7);
        } else if(collegeId == 2325) {
            keys.append(8);
        } else if(collegeId == 1315) {
            keys.append(9);
        } else if(collegeId == 3193) {
            keys.append(10);
        } else if(collegeId == 3658) {
            keys.append(11);
        } else if(collegeId == 1329) {
            keys.append(12);
        } else if(collegeId == 3897) {
            keys.append(13);
        }
        selectedTourCampuses.append(collegeId);
    }
    tourpurchase c(keys, selectedTourCampuses, souvenirsList);
}

void tourCampuses::on_purchaseTour_saddlebackTour_clicked()
{
    tourpurchase *m = new tourpurchase;
    m->show();
    this->close();

    QVector<int> selectedTourCampuses;
    QVector<int> keys;

    for(int row = 0; row < ui->trip_table_saddleback->rowCount(); row++) {
        int collegeId = ui->trip_table_saddleback->item(row, 1)->text().toInt();

        if(collegeId == 1018) {           // ARIZONA
            keys.append(1);
        } else if(collegeId == 1314) {    // UCI
            keys.append(2);
        } else if(collegeId == 2178) {
            keys.append(3);
        } else if(collegeId == 1739) {
            keys.append(4);
        } else if(collegeId == 3090) {
            keys.append(5);
        } else if(collegeId == 8918) {
            keys.append(6);
        } else if(collegeId == 1137) {
            keys.append(7);
        } else if(collegeId == 2325) {
            keys.append(8);
        } else if(collegeId == 1315) {
            keys.append(9);
        } else if(collegeId == 3193) {
            keys.append(10);
        } else if(collegeId == 3658) {
            keys.append(11);
        } else if(collegeId == 1329) {
            keys.append(12);
        } else if(collegeId == 3897) {
            keys.append(13);
        }
        selectedTourCampuses.append(collegeId);
    }
    tourpurchase n(keys, selectedTourCampuses, souvenirsList);
}

void tourCampuses::on_purchaseTour_MichiganTour_clicked()
{
    tourpurchase *o = new tourpurchase;
    o->show();
    this->close();

    QVector<int> selectedTourCampuses;
    QVector<int> keys;

    for(int row = 0; row < ui->trip_table_michigan->rowCount(); row++) {
        int collegeId = ui->trip_table_michigan->item(row, 1)->text().toInt();

        if(collegeId == 1018) {           // ARIZONA
            keys.append(1);
        } else if(collegeId == 1314) {    // UCI
            keys.append(2);
        } else if(collegeId == 2178) {
            keys.append(3);
        } else if(collegeId == 1739) {
            keys.append(4);
        } else if(collegeId == 3090) {
            keys.append(5);
        } else if(collegeId == 8918) {
            keys.append(6);
        } else if(collegeId == 1137) {
            keys.append(7);
        } else if(collegeId == 2325) {
            keys.append(8);
        } else if(collegeId == 1315) {
            keys.append(9);
        } else if(collegeId == 3193) {
            keys.append(10);
        } else if(collegeId == 3658) {
            keys.append(11);
        } else if(collegeId == 1329) {
            keys.append(12);
        } else if(collegeId == 3897) {
            keys.append(13);
        }
        selectedTourCampuses.append(collegeId);
    }
    tourpurchase v(keys, selectedTourCampuses, souvenirsList);

}
