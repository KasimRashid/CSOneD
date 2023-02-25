#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("res/project.sqlite");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
