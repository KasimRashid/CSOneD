#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include "seconddialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_loginAdmin_clicked();

    void on_pushButton_loginStudent_clicked();

private:
    Ui::MainWindow *ui;
    Dialog *dialog;
    SecondDialog *secondDialog;
};
#endif // MAINWINDOW_H
