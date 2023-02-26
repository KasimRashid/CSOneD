#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adminlogin.h"
#include "tourcampuses.h"
#include "purchasesouvenirs.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    // populate vectors
    populate();

    // hide display window buttons for tours and souvenir purchases
    ui->tour_button->hide();
    ui->purchase_button->hide();

    // stretch vertical headers to fit table
    //ui->display_college_table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // center header text
    ui->display_college_table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    // no editing elements
    ui->display_college_table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // select entire rows instead of single cells
    ui->display_college_table->setSelectionBehavior(QAbstractItemView::SelectRows);

    // stretch horizontal headers, will later stretch elements to fit remaining width in the table
    ui->display_college_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // hide vertical header
    ui->display_college_table->verticalHeader()->hide();
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::populate
 */
void MainWindow::populate()
{
    // default connection
    QSqlDatabase db = QSqlDatabase::database();

    // show database status
    if (!db.isOpen()) {
        //ui->status->setStyleSheet("color:red");
        //ui->status->setText("Error: Failed to connect to database");
        return; // exit
    } else {
        //ui->status->setStyleSheet("color:green");
        //ui->status->setText("Database connected successfully");
    }

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

    // reading from the SQL Database into the Distance vector
    QSqlQuery distances_qry("SELECT * FROM distances");

    while (distances_qry.next()) {
        // find College by ID from existing list
        College startCollege(distances_qry.record().value("startingPointCollegeId").toInt(),
                             distances_qry.record().value("startingPointCollegeName").toString());
        College endCollege(distances_qry.record().value("endingPointCollegeId").toInt(),
                             distances_qry.record().value("endingPointCollegeName").toString());

        distancesList.push_back(Distance(startCollege, endCollege, distances_qry.record().value("distance").toInt()));
    }
}

/**
 * @brief MainWindow::distance_by_ID
 * @param ID
 * @return
 */
int MainWindow::distance_by_ID(int ID)
{
    // find Distance object that starts at Saddleback and ends at our College
    int distance = -1;

    // if our College is Saddleback than distance to Saddleback is 0
    if (ID == 8918) {
        distance = 0;
    } else {
        for (int j = 0; j < distancesList.size(); ++j) {
            // if start College is Saddleback and end College is our College get distance
            if (distancesList.at(j).getStartCollege().getCollegeID() == 8918 &&
                    distancesList.at(j).getEndCollege().getCollegeID() == ID) {
                distance = distancesList.at(j).getDistance(); // set distance to distance of object that matches
                break;
            }
        }
    }

    return distance;
}

/**
 * @brief MainWindow::on_display_comboBox_currentIndexChanged
 * @param index
 */
void MainWindow::on_display_comboBox_currentIndexChanged(int index)
{
    ui->purchase_button->hide();
    ui->tour_button->hide();

    // clear rows
    ui->display_college_table->setRowCount(0);

    switch (index) {
    case 0:
        ui->display_college_table->setColumnCount(0);
        break;
    case 1:
        ui->tour_button->show();

        ui->display_college_table->setColumnCount(3);
        ui->display_college_table->setHorizontalHeaderItem(0, new QTableWidgetItem("IDs"));
        ui->display_college_table->setHorizontalHeaderItem(1, new QTableWidgetItem("Colleges"));
        ui->display_college_table->setHorizontalHeaderItem(2, new QTableWidgetItem("Distance from Saddleback"));

        // stretch College name
        ui->display_college_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

        // show search items if search_edit is not empty, then return
        if (!ui->search_edit->text().isEmpty()) {
            on_search_edit_textEdited(ui->search_edit->text());
            return;
        }

        for (int i = 0; i < collegesList.size(); ++i) {
            ui->display_college_table->insertRow(ui->display_college_table->rowCount());

            ui->display_college_table->setItem(ui->display_college_table->rowCount() - 1, 0,
                                               new QTableWidgetItem(QString::number(collegesList.at(i).getCollegeID())));
            ui->display_college_table->setItem(ui->display_college_table->rowCount() - 1, 1,
                                               new QTableWidgetItem(collegesList.at(i).getCollegeName()));
            ui->display_college_table->setItem(ui->display_college_table->rowCount() - 1, 2,
                                               new QTableWidgetItem(QString::number(distance_by_ID(collegesList.at(i).getCollegeID()))));

            // center text
            for (int col = 0; col < ui->display_college_table->columnCount(); ++col)
                ui->display_college_table->item(ui->display_college_table->rowCount() - 1, col)->setTextAlignment(Qt::AlignCenter);
        }
        break;
    case 2:
        ui->purchase_button->show();

        ui->display_college_table->setColumnCount(4);
        ui->display_college_table->setHorizontalHeaderItem(0, new QTableWidgetItem("IDs"));
        ui->display_college_table->setHorizontalHeaderItem(1, new QTableWidgetItem("Campuses"));
        ui->display_college_table->setHorizontalHeaderItem(2, new QTableWidgetItem("Souvenirs"));
        ui->display_college_table->setHorizontalHeaderItem(3, new QTableWidgetItem("Prices"));

        // stretch college name
        ui->display_college_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

        // show search items if search_edit is not empty, then return
        if (!ui->search_edit->text().isEmpty()) {
            on_search_edit_textEdited(ui->search_edit->text());
            return;
        }

        for (int i = 0; i < souvenirsList.size(); ++i) {
            ui->display_college_table->insertRow(ui->display_college_table->rowCount());

            ui->display_college_table->setItem(ui->display_college_table->rowCount() - 1, 0,
                                               new QTableWidgetItem(QString::number(souvenirsList.at(i).getSouvenirCollege().getCollegeID())));
            ui->display_college_table->setItem(ui->display_college_table->rowCount() - 1, 1,
                                               new QTableWidgetItem(souvenirsList.at(i).getSouvenirCollege().getCollegeName()));
            ui->display_college_table->setItem(ui->display_college_table->rowCount() - 1, 2,
                                               new QTableWidgetItem(souvenirsList.at(i).getSouvenirName()));
            ui->display_college_table->setItem(ui->display_college_table->rowCount() - 1, 3,
                                               new QTableWidgetItem("$" + QString::number(souvenirsList.at(i).getSouvenirPrice())));

            // center text
            for (int col = 0; col < ui->display_college_table->columnCount(); ++col)
                ui->display_college_table->item(ui->display_college_table->rowCount() - 1, col)->setTextAlignment(Qt::AlignCenter);
        }
        // fall through
    }
}

/**
 * @brief MainWindow::on_login_button_clicked
 */
void MainWindow::on_login_button_clicked()
{
    AdminLogin *login_window = new AdminLogin;
    login_window->show();
    this->close();
}

/**
 * @brief MainWindow::on_purchase_button_clicked
 */
void MainWindow::on_purchase_button_clicked()
{
    purchaseSouvenirs *purchase_souvenirs = new purchaseSouvenirs;
    purchase_souvenirs->show();
}

/**
 * @brief MainWindow::on_search_edit_textEdited
 * @param arg1
 */
void MainWindow::on_search_edit_textEdited(const QString &arg1)
{
    if (arg1.length() == 0) {
        // display all colleges and exit
        on_display_comboBox_currentIndexChanged(ui->display_comboBox->currentIndex());
        return;
    }

    ui->display_college_table->setRowCount(0);

    switch (ui->display_comboBox->currentIndex()) {
    case 0:
        return;
    case 1:
        for (int i = 0; i < collegesList.size(); ++i) {
            // add matching colleges
            if (collegesList.at(i).getCollegeName().toLower().contains(arg1.toLower())) {
                ui->display_college_table->insertRow(ui->display_college_table->rowCount());

                ui->display_college_table->setItem(ui->display_college_table->rowCount() - 1, 0,
                                                   new QTableWidgetItem(QString::number(collegesList.at(i).getCollegeID())));
                ui->display_college_table->setItem(ui->display_college_table->rowCount() - 1, 1,
                                                   new QTableWidgetItem(collegesList.at(i).getCollegeName()));
                ui->display_college_table->setItem(ui->display_college_table->rowCount() - 1, 2,
                                                   new QTableWidgetItem(QString::number(distance_by_ID(collegesList.at(i).getCollegeID()))));

                // center text
                for (int col = 0; col < ui->display_college_table->columnCount(); ++col)
                    ui->display_college_table->item(ui->display_college_table->rowCount() - 1, col)->setTextAlignment(Qt::AlignCenter);
            }
        }
        break;
    case 2:
        for (int i = 0; i < souvenirsList.size(); ++i) {
            // add matching colleges
            if (souvenirsList.at(i).getSouvenirCollege().getCollegeName().toLower().contains(arg1.toLower())) {
                ui->display_college_table->insertRow(ui->display_college_table->rowCount());

                ui->display_college_table->setItem(ui->display_college_table->rowCount() - 1, 0,
                                                   new QTableWidgetItem(QString::number(souvenirsList.at(i).getSouvenirCollege().getCollegeID())));
                ui->display_college_table->setItem(ui->display_college_table->rowCount() - 1, 1,
                                                   new QTableWidgetItem(souvenirsList.at(i).getSouvenirCollege().getCollegeName()));
                ui->display_college_table->setItem(ui->display_college_table->rowCount() - 1, 2,
                                                   new QTableWidgetItem(souvenirsList.at(i).getSouvenirName()));
                ui->display_college_table->setItem(ui->display_college_table->rowCount() - 1, 3,
                                                   new QTableWidgetItem("$" + QString::number(souvenirsList.at(i).getSouvenirPrice())));

                // center text
                for (int col = 0; col < ui->display_college_table->columnCount(); ++col)
                    ui->display_college_table->item(ui->display_college_table->rowCount() - 1, col)->setTextAlignment(Qt::AlignCenter);
            }
        }
        // fall through
    }
}

/**
 * @brief MainWindow::on_tour_button_clicked
 */
void MainWindow::on_tour_button_clicked()
{
    tourCampuses *tourWindow = new tourCampuses;
    tourWindow->show();
    this->close();
}

/**
 * @brief MainWindow::on_nextPage_2_clicked
 */
void MainWindow::on_nextPage_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

/**
 * @brief MainWindow::on_backPage_1_clicked
 */
void MainWindow::on_backPage_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

/**
 * @brief MainWindow::on_nextPage_3_clicked
 */
void MainWindow::on_nextPage_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

/**
 * @brief MainWindow::on_backPage_2_clicked
 */
void MainWindow::on_backPage_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

/**
 * @brief MainWindow::on_nextPage_4_clicked
 */
void MainWindow::on_nextPage_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

/**
 * @brief MainWindow::on_backPage_3_clicked
 */
void MainWindow::on_backPage_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

/**
 * @brief MainWindow::on_nextPage_5_clicked
 */
void MainWindow::on_nextPage_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

/**
 * @brief MainWindow::on_backPage_4_clicked
 */
void MainWindow::on_backPage_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

/**
 * @brief MainWindow::on_nextPage_6_clicked
 */
void MainWindow::on_nextPage_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

/**
 * @brief MainWindow::on_backPage_5_clicked
 */
void MainWindow::on_backPage_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

/**
 * @brief MainWindow::on_nextPage_7_clicked
 */
void MainWindow::on_nextPage_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

/**
 * @brief MainWindow::on_backPage_6_clicked
 */
void MainWindow::on_backPage_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

/**
 * @brief MainWindow::on_nextPage_8_clicked
 */
void MainWindow::on_nextPage_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}


/**
 * @brief MainWindow::on_backPage_7_clicked
 */
void MainWindow::on_backPage_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

/**
 * @brief MainWindow::on_nextPage_9_clicked
 */
void MainWindow::on_nextPage_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

/**
 * @brief MainWindow::on_backPage_8_clicked
 */
void MainWindow::on_backPage_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

/**
 * @brief MainWindow::on_nextPage_10_clicked
 */
void MainWindow::on_nextPage_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

/**
 * @brief MainWindow::on_backPage_9_clicked
 */
void MainWindow::on_backPage_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

/**
 * @brief MainWindow::on_nextPage_11_clicked
 */
void MainWindow::on_nextPage_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}

/**
 * @brief MainWindow::on_backPage_10_clicked
 */
void MainWindow::on_backPage_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

/**
 * @brief MainWindow::on_nextPage_12_clicked
 */
void MainWindow::on_nextPage_12_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);
}

/**
 * @brief MainWindow::on_backPage_11_clicked
 */
void MainWindow::on_backPage_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}

/**
 * @brief MainWindow::on_nextPage_13_clicked
 */
void MainWindow::on_nextPage_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(12);
}

/**
 * @brief MainWindow::on_backPage_12_clicked
 */
void MainWindow::on_backPage_12_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);
}

/**
 * @brief MainWindow::on_nextPage_14_clicked
 */
void MainWindow::on_nextPage_14_clicked()
{
    ui->stackedWidget->setCurrentIndex(13);
}

/**
 * @brief MainWindow::on_backPage_13_clicked
 */
void MainWindow::on_backPage_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(12);
}

/**
 * @brief MainWindow::on_nextPage_15_clicked
 */
void MainWindow::on_nextPage_15_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

/**
 * @brief MainWindow::on_visitCampuses_button_clicked
 */
void MainWindow::on_visitCampuses_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

/**
 * @brief MainWindow::on_colleges_table_button_clicked
 */
void MainWindow::on_colleges_table_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(14);

}
