#ifndef STUDENTPAGE_H
#define STUDENTPAGE_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlQuery>
#include <QInputDialog>
#include <QIntValidator>
#include <QAbstractTableModel>

#include "dbmanager.h"

namespace Ui {

class studentpage;
}

class studentpage : public QMainWindow
{
    Q_OBJECT

public:
    enum tour
    {
        none,
        uci,
        saddleback,
        asu,
        custom
    };

    struct Souvenir
    {
        QString souvName;
        QString campus;
        double cost;
        int quantity;
    };

    explicit studentpage(QWidget *parent = nullptr);

    ~studentpage();

    void showDBView(QSqlQueryModel *model);

    void showCampusDBCombo(QSqlQueryModel *model);

    bool checkCampusVectorNames(QVector<QString> campuses);

    void showStartAvaliListView(QSqlQueryModel *model);

    void showStartAvaliListCombo(QSqlQueryModel *model);

    void showAvaliListView(QSqlQueryModel *model);

    void showSelectListView();

    void showAvaliListCombo(QSqlQueryModel *model);

    void recursiveCollegeSort(QString currentCamp);

    void calcTotalDist();

    void goToSouvenirShop();

    void showSelectCampusComboBox(QStringListModel *model);

    void showSouvTableView(QSqlQueryModel *model);

    void showSouvCartTableView(QSqlQueryModel *model);

    void showTotalCost(double itemCost);

    void goToReceipt();


private slots:

    void on_back_button_select_clicked();

    void on_campDB_button_clicked();

    void on_other_button_clicked();

    void on_souv_button_clicked();

    void on_back_button_db_clicked();

    void on_UCI_button_clicked();

    void on_Saddle_button_clicked();

    void on_ASU_button_clicked();

    void on_enter_button_asu_clicked();

    void on_back_button_asu_clicked();

    void on_custom_button_clicked();

    void on_enter_button_1_clicked();

    void on_back_button_custom_clicked();

    void on_enter_button_2_clicked();

    void on_done_button_clicked();

    void on_back_button_general_clicked();

    void on_addSouvenir_button_clicked();

    void on_selectCampus_comboBox_currentIndexChanged();

    void on_checkout_button_clicked();

    void on_backFromSouv_button_clicked();

    void on_finish_button_clicked();

private:
    Ui::studentpage *ui;
    dbManager database;

    tour tourType;

    QVector<QString> selectedCampuses;
    QQueue<QString> sortedCampuses;
    double tourDist;

    int asuNum;
    int selectNum;

    QStack<Souvenir> souvenirCart;
    double totalCost;
    QString sQry;
};

#endif // STUDENTPAGE_H
