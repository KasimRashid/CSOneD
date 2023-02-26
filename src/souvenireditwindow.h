#ifndef SOUVENIREDITWINDOW_H
#define SOUVENIREDITWINDOW_H

#include <QDialog>
#include "college.h"
#include "souvenir.h"

namespace Ui {
class SouvenirEditWindow;
}

class SouvenirEditWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SouvenirEditWindow(QWidget *parent = 0);
    ~SouvenirEditWindow();

private slots:
    void on_pushButton_3_clicked();
    void on_addSouvenirButton_clicked();

    void on_add_item_button_clicked();

    void on_delete_item_button_clicked();

    void on_deleteSouvenirButton_clicked();

    void populate();

private:
    Ui::SouvenirEditWindow *ui;
    QVector<College> colleges1;
    QVector<QString> souvenirs1;
};

#endif // SOUVENIREDITWINDOW_H
