#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql>
#include <QVector>
#include <QQueue>


class dbManager
{
public:
    dbManager();
    ~dbManager();
    QSqlQueryModel *loadCampusNamesOnly();
    QSqlQueryModel *loadRemainingCampusNamesOnly(QVector<QString> campuses);
    QSqlQueryModel *loadOtherCampusAndDist(QString campus);
    QSqlQueryModel *loadCampusSouvenirs(QString campus);
    QSqlQueryModel* loadSouvCart(QString sQry);
    void createCart();
    void deleteCart();
    void updateCartQuantity(QString campus, QString souv, int quantity);
    double GetTotalCost(QString campusIn, QString souvIn);
    double GetDistBtwn(QString start, QString end);
    bool checkCampusName(QString campus);
    int GetCampusCount(QString campus);

private:
    QSqlDatabase tourDB; /**< QSqlDatabase variable*/
};

#endif // DBMANAGER_H
