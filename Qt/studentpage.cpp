#include "studentpage.h"
#include <QMessageBox>
#include <QComboBox>
#include "ui_studentpage.h"
#include <iomanip>

studentpage::studentpage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::studentpage)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentWidget(ui->StudentSelect);

    showCampusDBCombo(database.loadCampusNamesOnly());

    tourType = none;
    asuNum = 0;
    selectNum = 0;
    totalCost = 0.00;
}

studentpage::~studentpage()
{
    delete ui;
    database.deleteCart();
}

void studentpage::on_back_button_select_clicked()
{
    studentpage::close();
}

void studentpage::showDBView(QSqlQueryModel *model)
{
    ui->tableView->setModel(model);
}

void studentpage::showCampusDBCombo(QSqlQueryModel *model)
{
    ui->campus_combo->setModel(model);
}

void studentpage::on_campDB_button_clicked()
{
    QMessageBox::information(this, "Loading...", "Now moving to Database Viewing Screen.", QMessageBox::Ok, QMessageBox::NoButton);
    ui->stackedWidget->setCurrentWidget(ui->databaseDisplay);
    showCampusDBCombo(database.loadCampusNamesOnly());
}

void studentpage::on_other_button_clicked()
{
    ui->database_label->setText(ui->campus_combo->currentText());
    showDBView(database.loadOtherCampusAndDist(ui->campus_combo->currentText()));
    ui->tableView->setColumnWidth(0, 450);
    ui->tableView->setColumnWidth(1, 280);
}


void studentpage::on_souv_button_clicked()
{
    ui->database_label->setText(ui->campus_combo->currentText());
    showDBView(database.loadCampusSouvenirs(ui->campus_combo->currentText()));
    ui->tableView->setColumnWidth(0, 460);
    ui->tableView->setColumnWidth(1, 280);
}

void studentpage::on_back_button_db_clicked()
{
    QMessageBox::information(this, "Loading...", "Now moving to Main Student Screen.", QMessageBox::Ok, QMessageBox::NoButton);
    ui->stackedWidget->setCurrentWidget(ui->StudentSelect);
}

bool studentpage::checkCampusVectorNames(QVector<QString> campuses)
{
    bool found = true;
    QString *p = campuses.begin();
    while (p != campuses.end() && found == true)
    {
        if(!database.checkCampusName(*p))
        {
            found = false;

        }
        else
        {
            p++;
        }
    }
    return found;
}

void studentpage::on_UCI_button_clicked()
{
    QVector<QString> initial11{"University of California, Irvine (UCI)",
                               "Arizona State University",
                               "Massachusetts Institute of Technology (MIT)",
                               "Northwestern",
                               "Ohio State University",
                               "Saddleback College",
                               "University of  Michigan",
                               "University of California, Los Angeles (UCLA)",
                               "University of Oregon",
                               "University of Wisconsin",
                               "University of the Pacific",
                               };

    bool allFound = checkCampusVectorNames(initial11);

    if(!allFound)
    {
        QMessageBox::warning(this, "ERROR", "NOT ALL 11 INITIAL CAMPUSES ARE IN THE DATABASE. ADMINISTRATOR ACTION NEEDED.", QMessageBox::Ok, QMessageBox::NoButton);
    }
    else
    {
        selectedCampuses.append(initial11);
        tourType = uci;

        //send to souvenir shop
        QMessageBox::information(this, "Loading...", "UCI tour type has been selected. Now moving to Souviner Shop Screen.", QMessageBox::Ok, QMessageBox::NoButton);
        goToSouvenirShop();
    }
}

void studentpage::on_Saddle_button_clicked()
{
    QVector<QString> campus13{"Saddleback College",
                               "Arizona State University",
                               "Massachusetts Institute of Technology (MIT)",
                               "Northwestern",
                               "Ohio State University",
                               "University of California, Irvine (UCI)",
                               "University of  Michigan",
                               "University of California, Los Angeles (UCLA)",
                               "University of Oregon",
                               "University of Wisconsin",
                               "University of the Pacific",
                               "California State University, Fullerton",
                               "University of Texas"};

    bool allFound = checkCampusVectorNames(campus13);

    if(!allFound)
    {
         QMessageBox::warning(this, "ERROR", "NOT ALL 13 CAMPUSES ARE IN THE DATABASE. ADMINISTRATOR ACTION NEEDED.", QMessageBox::Ok, QMessageBox::NoButton);
    }
    else
    {
        selectedCampuses.append(campus13);
        tourType = saddleback;

        //go to souvenir shop
        QMessageBox::information(this, "Loading...", "Saddleback tour type has been selected. Now moving to Souvenir Screen.", QMessageBox::Ok, QMessageBox::NoButton);
        goToSouvenirShop();
    }
}

void studentpage::on_ASU_button_clicked()
{

    tourType = asu;
    int campusCount = database.GetCampusCount("Arizona State University");
    for(int i = 1; i <= campusCount; i++)
    {
        ui->asu_combo->addItem(QString::number(i));
    }
    QMessageBox::information(this, "Loading...", "ASU tour type has been selected. Now moving to ASU Number Selection Screen.", QMessageBox::Ok, QMessageBox::NoButton);
    ui->stackedWidget->setCurrentWidget(ui->asuCollegeTour);
}

void studentpage::on_enter_button_asu_clicked()
{
    selectedCampuses.push_back("Arizona State University");
    selectNum++;
    asuNum = ui->asu_combo->currentIndex() + 1;

    //The program leaves the start screen to the main tour planning screen
    QMessageBox::information(this, "Loading...", "Maximum number of visitable campuses has been selected. Now moving to College Selection Screen.", QMessageBox::Ok, QMessageBox::NoButton);
    ui->stackedWidget->setCurrentWidget(ui->collegeTour);

    //Populates the main tour planning screen Avaliable Campuses list view with the names of the campuses
    showAvaliListView(database.loadRemainingCampusNamesOnly(selectedCampuses));
    //Populates the main tour planning screen Selected Campus list view with the names of the campueses
    showSelectListView();
    //Populates the main tour planning screen Avaliable Campuses combo box with the names of the campuses
    showAvaliListCombo(database.loadRemainingCampusNamesOnly(selectedCampuses));
}

void studentpage::on_back_button_asu_clicked()
{
    tourType = none;QMessageBox::information(this, "Loading...", "Now moving to Main Student Screen.", QMessageBox::Ok, QMessageBox::NoButton);
    ui->stackedWidget->setCurrentWidget(ui->StudentSelect);

}

void studentpage::showStartAvaliListView(QSqlQueryModel *model)
{
    ui->start_listView->setModel(model);
}

void studentpage::showStartAvaliListCombo(QSqlQueryModel *model)
{
    ui->start_combo->setModel(model);
}

void studentpage::on_custom_button_clicked()
{
    tourType = custom;
    QMessageBox::information(this, "Loading...", "Custom tour type has been selected. Now moving to Starting Campus Selection Screen.", QMessageBox::Ok, QMessageBox::NoButton);
    ui->stackedWidget->setCurrentWidget(ui->startCollegeTour);

    showStartAvaliListView(database.loadCampusNamesOnly());
    showStartAvaliListCombo(database.loadCampusNamesOnly());
}

void studentpage::on_enter_button_1_clicked()
{
    //Students choice is saved into the vector
    QString campus = ui->start_combo->currentText();
    selectedCampuses.push_back(campus);
    selectNum++;

    //The program leaves the start screen to the main tour planning screen
    QMessageBox::information(this, "Loading...", "Starting campus has been selected. Now moving to College Selection Screen.", QMessageBox::Ok, QMessageBox::NoButton);
    ui->stackedWidget->setCurrentWidget(ui->collegeTour);

    //Populates the main tour planning screen Avaliable Campuses list view with the names of the campuses
    showAvaliListView(database.loadRemainingCampusNamesOnly(selectedCampuses));
    //Populates the main tour planning screen Selected Campus list view with the names of the campueses
    showSelectListView();
    //Populates the main tour planning screen Avaliable Campuses combo box with the names of the campuses
    showAvaliListCombo(database.loadRemainingCampusNamesOnly(selectedCampuses));
}

void studentpage::on_back_button_custom_clicked()
{
    QMessageBox::information(this, "Loading...", "Now moving to Main Student Screen.", QMessageBox::Ok, QMessageBox::NoButton);
    tourType = none;
    ui->stackedWidget->setCurrentWidget(ui->StudentSelect);
}

void studentpage::showAvaliListView(QSqlQueryModel *model)
{
    ui->avali_listView->setModel(model);
}

void studentpage::showSelectListView()
{
    ui->select_listView->setModel(new QStringListModel(QList<QString>::fromVector(selectedCampuses)));
}

void studentpage::showAvaliListCombo(QSqlQueryModel *model)
{
    ui->next_combo->setModel(model);
}

void studentpage::on_enter_button_2_clicked()
{
    QString campus = ui->next_combo->currentText();
    //No campuses
    if(campus == "")
    {
        QMessageBox::warning(this, "ERROR", "NO MORE CAMPUSES! PLEASE CLICK DONE!", QMessageBox::Ok, QMessageBox::NoButton);
    }
    //ASU tour
    else if (selectNum == asuNum)
    {
        QMessageBox::warning(this, "ERROR", "YOU HAVE REACHED YOUR MAX FOR THE ASU TOUR! PLEASE CLICK DONE!", QMessageBox::Ok, QMessageBox::NoButton);
    }
    //Campuses remain
    else
    {
        //Pushes newly selected campus to the back of the vector
        selectedCampuses.push_back(campus);
        selectNum++;
        //Refreshes list views and combo box
        showAvaliListView(database.loadRemainingCampusNamesOnly(selectedCampuses));
        showSelectListView();
        showAvaliListCombo(database.loadRemainingCampusNamesOnly(selectedCampuses));
    }
}

void studentpage::on_done_button_clicked()
{
    if(asuNum == 0 || selectNum == asuNum)
    {
        //Go to souvenirShop widget
        QMessageBox::information(this, "Loading...", "Now moving to Souvenir Shop Screen.", QMessageBox::Ok, QMessageBox::NoButton);
        goToSouvenirShop();
    }
    else
    {
        int left = asuNum - selectNum;
        QMessageBox::warning(this, "ERROR", "PLEASE SELECT " + QString::number(left) + " MORE CAMPUSES.", QMessageBox::Ok, QMessageBox::NoButton);
    }
}

void studentpage::on_back_button_general_clicked()
{
    while(!selectedCampuses.empty())
    {
          selectedCampuses.pop_back();
    }
    asuNum = 0;
    selectNum = 0;

    if(tourType == asu)
    {
        QMessageBox::information(this, "Loading...", "ASU tour reseting. Now moving to ASU Number Select Screen.", QMessageBox::Ok, QMessageBox::NoButton);
          ui->stackedWidget->setCurrentWidget(ui->asuCollegeTour);
    }
    else if(tourType == custom)
    {
        QMessageBox::information(this, "Loading...", "Custom tour reseting. Now moving to Starting Campus Selection Screen.", QMessageBox::Ok, QMessageBox::NoButton);
          ui->stackedWidget->setCurrentWidget(ui->startCollegeTour);
    }
    totalCost = 0;
    sQry.clear();
}

void studentpage::recursiveCollegeSort(QString currentCamp)
{
   sortedCampuses.enqueue(currentCamp);
   selectedCampuses.removeAll(currentCamp);

   if(selectedCampuses.isEmpty())
   {
       return;
   }
   else
   {
        QString* otherCamp = selectedCampuses.begin();
        int currentIndex = 0;

        double leastDist = database.GetDistBtwn(currentCamp, *otherCamp);
        int leastIndex = 0;

        otherCamp++;
        currentIndex++;

        while(otherCamp != selectedCampuses.end())
        {
            double currentDist = database.GetDistBtwn(currentCamp, *otherCamp);
            if (currentDist < leastDist)
            {
                leastDist = currentDist;
                leastIndex = currentIndex;
            }
            else
            {
                otherCamp++;
                currentIndex++;
            }
        }
        QString nextCamp = selectedCampuses.at(leastIndex);
        recursiveCollegeSort(nextCamp);
   }
}

void studentpage::calcTotalDist()
{
    tourDist = 0;
    for(int i = 1; i < sortedCampuses.count(); i++)
    {
        double currentDistBtwn = database.GetDistBtwn(sortedCampuses[i-1], sortedCampuses[i]);
        tourDist += currentDistBtwn;
    }
}

void studentpage::goToSouvenirShop()
{
    //Go to souvenirShop widget
    ui->stackedWidget->setCurrentWidget(ui->souvenirShop);
    showSouvTableView(database.loadCampusSouvenirs(""));
    showSelectCampusComboBox(new QStringListModel(QList<QString>::fromVector(selectedCampuses)));

    showSouvTableView(database.loadCampusSouvenirs(ui->selectCampus_comboBox->currentText()));
    //create Cart table
    database.createCart();
    showSouvCartTableView(database.loadSouvCart(sQry));
    showTotalCost(totalCost);

}

void studentpage::showSelectCampusComboBox(QStringListModel *model)
{
    ui ->selectCampus_comboBox->setModel(model);
}

void studentpage::showSouvTableView(QSqlQueryModel *model)
{
    ui->souv_tableView->setModel(model);
    ui->souv_comboBox->setModel(model);
}

void studentpage::showSouvCartTableView(QSqlQueryModel *model)
{
    ui->souvCart_tableView->setModel(model);
}

void studentpage::showTotalCost(double itemCost)
{
    totalCost += itemCost;
    QString totalCostStr = QString::number(totalCost, 'f', 2);
    ui->totalCart_label->setText(totalCostStr);
}

void studentpage::on_addSouvenir_button_clicked()
{
    Souvenir souv;
    //name and campus
    QString name, campus;
    name = ui->souv_comboBox->currentText();
    souv.souvName = name;
    campus = ui->selectCampus_comboBox->currentText();
    souv.campus = campus;


    //quantity and item cost
    int quantity = ui-> quantity_spinBox -> cleanText().toInt();
    souv.quantity = quantity;
    double itemCost = database.GetTotalCost(campus, name);
    itemCost = itemCost * quantity;
    souv.cost = itemCost;

    souvenirCart.push(souv);

    //update Cart table
    database.updateCartQuantity(campus, name, quantity);

    //displays cart in table
   if(sQry == "")
   {
       sQry += "select souvCollege as 'College', souvTrad as 'Souvenirs', souvCost as 'Cost', quantity as 'Quantity' "
                       "from Cart where souvCollege = '" +campus+ "' and souvTrad = '" +name+ "'";
   }
   else
   {
       sQry += " union select souvCollege as 'College', souvTrad as 'Souvenirs', souvCost as 'Cost', quantity as 'Quantity'"
                       "from Cart where souvCollege = '" +campus+ "' and souvTrad = '" +name+ "'";
   }

   showSouvCartTableView(database.loadSouvCart(sQry));

   showTotalCost(itemCost);

}

void studentpage::on_selectCampus_comboBox_currentIndexChanged()
{
    QString campus = ui->selectCampus_comboBox->currentText();
    showSouvTableView(database.loadCampusSouvenirs(campus));
}

void studentpage::on_checkout_button_clicked()
{
    QMessageBox::information(this, "Loading...", "Shopping Complete. Now moving to Receipt Screen.", QMessageBox::Ok, QMessageBox::NoButton);
    goToReceipt();
}

void studentpage::on_backFromSouv_button_clicked()
{
    if(tourType == uci || tourType == saddleback)
    {
        while(!selectedCampuses.empty())
        {
            selectedCampuses.pop_front();
        }
        totalCost = 0;
        sQry.clear();
        if(tourType == uci)
            QMessageBox::information(this, "Loading...", "UCI tour reseting. Now moving to Main Student Screen.", QMessageBox::Ok, QMessageBox::NoButton);
        else
            QMessageBox::information(this, "Loading...", "Saddleback tour reseting. Now moving to Main Student Screen.", QMessageBox::Ok, QMessageBox::NoButton);
        ui->stackedWidget->setCurrentWidget(ui->StudentSelect);
    }
    else
    {
         QMessageBox::information(this, "Loading...", "Now moving to College Selection Screen.", QMessageBox::Ok, QMessageBox::NoButton);
        ui->stackedWidget->setCurrentWidget(ui->collegeTour);
    }

}

void studentpage::goToReceipt()
{
    QString start = *selectedCampuses.begin();
    recursiveCollegeSort(start);
    calcTotalDist();

    ui->stackedWidget->setCurrentWidget(ui->SortCollegeTour);

    for(int i = 0; i < sortedCampuses.count(); i++)
    {
        ui->sort_listWidget->addItem(sortedCampuses[i]);
    }

    //Total tour distance
    QString tourDistStr = QString::number(tourDist);
    ui->distanceNum_label->setText(tourDistStr);

    //Souvenirs
    QVector<QString> names;
    QVector<QString> quantities;
    while(!souvenirCart.empty())
    {
        names.push_back(souvenirCart.top().souvName);
        quantities.push_back(QString::number(souvenirCart.top().quantity));
        souvenirCart.pop();
    }

    //Souv Names
    ui->souvFinal_listView->setModel(new QStringListModel(QList<QString>::fromVector(names)));
    //Souv Quanitities
    ui->quantityFinal_listView->setModel(new QStringListModel(QList<QString>::fromVector(quantities)));

    while(!names.empty())
    {
        names.pop_back();
        quantities.pop_back();
    }
    //Total Souvenir Cost
    QString totalCostStr = QString::number(totalCost, 'f', 2);
    ui->totalNum_label->setText(totalCostStr);

    //Delete Cart Table
    database.deleteCart();
}

void studentpage::on_finish_button_clicked()
{
     QMessageBox::information(this, "Loading...", "Tour Complete. Now moving to Main Student Screen.", QMessageBox::Ok, QMessageBox::NoButton);
    asuNum = 0;
    selectNum = 0;
    totalCost = 0;
    while(!sortedCampuses.empty())
    {
        sortedCampuses.pop_front();
    }
    ui->sort_listWidget->clear();
    sQry.clear();
    ui->stackedWidget->setCurrentWidget(ui->StudentSelect);
}
