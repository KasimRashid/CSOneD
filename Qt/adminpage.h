
#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QMainWindow>
#include "ui_adminpage.h"
#include "dbmanager.h"
#include <QtSql>
#include <QSqlQuery>
#include <QMessageBox>
#include <QInputDialog>
#include <QIntValidator>

namespace Ui {
class adminpage;
}

class adminpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminpage(QWidget *parent = nullptr);
    ~adminpage();
    void setupConnections();
    void changeToAdminHomePage();
    void changeToSouvenirPage();
    void changeToSouvenirPricePage();
    void changeToSouvenirDeletePage();
    void showSouvenirComboBoxDeletePage(QSqlQueryModel *model);
    void showCampusComboBoxAddPage(QSqlQueryModel * model);
    void showchangeSouvenirPageCampusNameComboBox(QSqlQueryModel * model);

private slots:
    void on_viewDistancesBtn_clicked();
    void on_viewSouvenirBtn_clicked();
    void on_addCampusThroughInputFile_clicked();
    void on_addSouvenirThroughInputFile_clicked();
    void on_changeSouvPriceBackBtn_clicked();
    void on_changeSouvenirPriceBtn_clicked();
    void on_updateSouvenirPriceBtn_clicked();
    void on_addSouvenirBtn_clicked();
    void on_createSouvenirBtn_clicked();
    void on_deleteSouvenirBtn_clicked();
    void on_deletePageBackBtn_clicked();
    void on_deleteSouvenirConfirmBtn_clicked();

private:
    Ui::adminpage *ui;
    dbManager database_;
};
#endif // ADMINPAGE_H
