#ifndef PURCHASESOUVENIRS_H
#define PURCHASESOUVENIRS_H

#include <QDialog>
#include "mainwindow.h"
#include <QTimer>
#include <QMessageBox>

namespace Ui {
class purchaseSouvenirs;
}

class purchaseSouvenirs : public QDialog
{
    Q_OBJECT

public:
    explicit purchaseSouvenirs(QWidget *parent = 0);
    ~purchaseSouvenirs();

private slots:
    void on_comboBox_college_currentIndexChanged(int index);

    void on_comboBox_souvenir_currentIndexChanged(int index);

    void on_pushButton_add_clicked();

    void on_pushButton_receipt_clicked();

private:
    Ui::purchaseSouvenirs *ui;
    void populate();
    QVector<College> collegesList;
    QVector<Souvenir> souvenirsList;

    QString collegeName;
    QVector<QString> souvenirName;
    QVector<double>  souvenirPrice;
    QVector<int>  souvenirQuantity;

    QVector<QString> tempSouvenirName;
    QVector<double>  tempSouvenirPrice;
};

#endif // PURCHASESOUVENIRS_H
