#ifndef SOUVENIRCHANGEPRICE_H
#define SOUVENIRCHANGEPRICE_H

#include <QDialog>
#include "souvenir.h"

namespace Ui {
class SouvenirChangePrice;
}

class SouvenirChangePrice : public QDialog
{
    Q_OBJECT

public:
    explicit SouvenirChangePrice(QWidget *parent = 0);
    ~SouvenirChangePrice();

private slots:
    void on_pushChange_clicked();

    void on_pushButton_clicked();

private:
    Ui::SouvenirChangePrice *ui;
    QVector<QString> souvenirs1;
};

#endif // SOUVENIRCHANGEPRICE_H
