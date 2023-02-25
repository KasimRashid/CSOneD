#ifndef TOURPURCHASE_H
#define TOURPURCHASE_H

#include <QDialog>
#include <QHash>
#include "college.h"
#include "souvenir.h"
#include "tourcampuses.h"

namespace Ui {
class tourpurchase;
}

class tourpurchase : public QDialog
{
    Q_OBJECT

public:
    explicit tourpurchase(QWidget *parent = 0);
    ~tourpurchase();
    tourpurchase(QVector<int> tour_keys, QVector<int> chosenTour, QVector<Souvenir> souvenirs);

private slots:
    /**
     * @brief on_shopping_button_clicked
     */
    void on_shopping_button_clicked();

    /**
     * @brief displaySouvenirs
     * @param count
     */
    void displaySouvenirs(int count);

    /**
     * @brief findPage
     * @param index
     */
    void findPage(int index);

    /**
     * @brief tourPurchasesTable
     * @param count
     */
    void tourPurchasesTable(int count);

    /**
     * @brief on_pushButton_clicked
     */
    void on_pushButton_clicked();

    /**
     * @brief on_pushButton_selectPurchase_asu_clicked
     */
    void on_pushButton_selectPurchase_asu_clicked();

    /**
     * @brief on_pushButton_quantityAsu_clicked
     */
    void on_pushButton_quantityAsu_clicked();

    /**
     * @brief on_next_3_clicked
     */
    void on_next_3_clicked();

    /**
     * @brief on_next_4_clicked
     */
    void on_next_4_clicked();

    /**
     * @brief on_next_11_clicked
     */
    void on_next_11_clicked();

    /**
     * @brief on_next_5_clicked
     */
    void on_next_5_clicked();

    /**
     * @brief on_next_6_clicked
     */
    void on_next_6_clicked();

    /**
     * @brief on_next_7_clicked
     */
    void on_next_7_clicked();

    /**
     * @brief on_next_8_clicked
     */
    void on_next_8_clicked();

    /**
     * @brief on_next_9_clicked
     */
    void on_next_9_clicked();

    /**
     * @brief on_next_10_clicked
     */
    void on_next_10_clicked();

    /**
     * @brief on_next_12_clicked
     */
    void on_next_12_clicked();

    /**
     * @brief on_next_13_clicked
     */
    void on_next_13_clicked();

    /**
     * @brief on_next_14_clicked
     */
    void on_next_14_clicked();

    /**
     * @brief on_next_15_clicked
     */
    void on_next_15_clicked();


    void on_pushButton_selectPurchase_uci_clicked();

    void on_pushButton_quantityUci_clicked();

    void on_print_receipt_clicked();

    void on_pushButton_selectPurchase_Mit_clicked();

    void on_pushButton_quantityMit_clicked();

    void on_pushButton_selectPurchase_Northwestern_clicked();

    void on_pushButton_quantityNorthwestern_clicked();

    void on_pushButton_selectPurchase_ohio_clicked();

    void on_pushButton_quantityOhio_clicked();

    void on_pushButton_selectPurchase_saddleback_clicked();

    void on_pushButton_quantitySaddleback_clicked();

    void on_pushButton_selectPurchase_csuf_clicked();

    void on_pushButton_quantityFullerton_clicked();

    void on_pushButton_selectPurchase_michigan_clicked();

    void on_pushButton_quantityMichigan_clicked();

    void on_pushButton_selectPurchase_ucla_2_clicked();

    void on_pushButton_quantityUcla_clicked();

    void on_pushButton_selectPurchase_oregon_2_clicked();

    void on_pushButton_quantityOregon_clicked();

    void on_pushButton_selectPurchase_texas_clicked();

    void on_pushButton_quantityTexas_clicked();

    void on_pushButton_selectPurchase_Pacific_clicked();

    void on_pushButton_quantityPacific_clicked();

    void on_pushButton_selectPurchase_Wisconsin_clicked();

    void on_pushButton_quantityWisconsin_clicked();

    void on_back_pushbutton_clicked();

private:
    Ui::tourpurchase *ui;
     QVector<Souvenir> tempSouvenirs;
    static QVector<int> keys;
    static QVector<int> selectedTourColleges;
    static QVector<Souvenir> souvenirList;

     double total[20] = {0};
     int souvenirCount;
     int pageIndicator;
    int tempCount;

    QVector<Souvenir> receipt;

    QVector<double> prices;
    QVector<int> quantity;
    QVector<QString> collegeName;
    QVector<QString> souvenirName;
};

#endif // TOURPURCHASE_H
