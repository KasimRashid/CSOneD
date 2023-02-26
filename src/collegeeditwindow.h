#ifndef COLLEGEEDITWINDOW_H
#define COLLEGEEDITWINDOW_H

#include <QDialog>

namespace Ui {
class CollegeEditWindow;
}

class CollegeEditWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CollegeEditWindow(QWidget *parent = 0);
    ~CollegeEditWindow();

private slots:
    void on_addCollegeButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::CollegeEditWindow *ui;
    void fail();
};

#endif // COLLEGEEDITWINDOW_H
