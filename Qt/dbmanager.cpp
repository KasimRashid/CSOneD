#include "dbmanager.h"


dbManager::dbManager()
{
    //Connects the database to the project
    tourDB = QSqlDatabase::addDatabase("QSQLITE");
    tourDB.setDatabaseName("/Users/trevorholm/Documents/CS1D/Projects/build-untitled1-Desktop_Qt_5_12_12_clang_64bit-Debug/College and Souvenirs.db");
    if(!tourDB.open())
    {
        qDebug() << "\nError Opening Database\n";
    }

}

dbManager::~dbManager() {}


QSqlQueryModel* dbManager::loadCampusNamesOnly()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QString sQry = "select distStart as \"Campuses\" from Distances group by distStart;";
    QSqlQuery qry;
    qry.prepare(sQry);

    if(!qry.exec())
    {
        qDebug() << "\nError Loading Campuses\n";
    }

    model->setQuery(qry);
    return model;
}

QSqlQueryModel* dbManager::loadRemainingCampusNamesOnly(QVector<QString> campuses)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QString* p = campuses.begin();
    QString sQry = "select distStart as \"Campuses\" from Distances where not distStart = '" +*p+ "'";
    p++;
    while (p != campuses.end())
    {
        sQry += " and not distStart = '" +*p+ "'";
        p++;
    }
    sQry += " group by distStart;";
    QSqlQuery qry;
    qry.prepare(sQry);

    if(!qry.exec())
    {
        qDebug() << "\nError Loading Campuses\n";
    }

    model->setQuery(qry);
    return model;
}

QSqlQueryModel* dbManager::loadOtherCampusAndDist(QString campus)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QString sQry = "SELECT distEnd as 'Campuses', distBtwn as 'Distance(mi)' FROM Distances WHERE distStart='" + campus + "';";
    QSqlQuery qry;
    qry.prepare(sQry);

    if(!qry.exec())
    {
        qDebug() << "\nError Loading Campuses\n";
    }

    model->setQuery(qry);
    return model;
}

QSqlQueryModel* dbManager::loadCampusSouvenirs(QString campus)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QString sQry = "select souvTrad as 'Souvenirs', souvCost as 'Cost($)' from Souvenirs where souvCollege = '" +campus+ "';";
    qDebug() << sQry;
    QSqlQuery qry;
    qry.prepare(sQry);

    if(!qry.exec())
    {
        qDebug() << "\nError Loading Campuses\n";
    }

    model->setQuery(qry);
    return model;
}

void dbManager::createCart()
{
    //cartQry - temporary table
    QSqlQuery cartQry;
    cartQry.prepare("create table Cart as SELECT * from Souvenirs;");

    if(!cartQry.exec())
    {
        qDebug() << "\nError Creating Cart\n";
    }
    cartQry.prepare("ALTER table Cart add quantity real default 0;");
    if(!cartQry.exec())
    {
        qDebug() << "\nError Creating Quanitity Column\n";
    }
}

void dbManager::deleteCart()
{
    //cartQry - temporary table
    QSqlQuery cartQry;
    cartQry.prepare("drop table Cart;");

    if(!cartQry.exec())
    {
        qDebug() << "\nError dropping Cart\n";
    }
}

void dbManager::updateCartQuantity(QString campus, QString souv, int quant)
{
    //Update quantity
    QSqlQuery updateQry;
    QString uQry = "UPDATE Cart SET quantity = quantity+" +QString::number(quant)+ " WHERE souvCollege = '" +campus+ "' and souvTrad = '" +souv+ "';";
    updateQry.prepare(uQry);

    if(!updateQry.exec())
    {
        qDebug() << "\nError updating Cart\n";
    }
}

QSqlQueryModel* dbManager::loadSouvCart(QString sQry)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare(sQry);

    if(!qry.exec())
    {
        qDebug() << "\nError Loading Souvenirs\n";
    }

    model->setQuery(qry);
    return model;
}

double dbManager::GetTotalCost(QString campusIn, QString souvIn)
{
    double total = 0.0;

    QString sQry = "select souvCost as 'Cost' "
                    "from Souvenirs where souvCollege = '" +campusIn+ "' and souvTrad = '" +souvIn+ "'";
    QSqlQuery qry;
    qry.prepare(sQry);
    qry.exec();

    if(qry.next())
    {
        total = qry.value(0).toDouble();
    }
    return total;
}

double dbManager::GetDistBtwn(QString start, QString end)
{
    double distBtwn = 0;
    QString sQry = "select distBtwn from Distances where distStart = '" +start+ "' and distEnd = '" +end+ "';";

    QSqlQuery qry;
    qry.prepare(sQry);
    qry.exec();

    if(qry.next())
    {
        distBtwn = qry.value(0).toDouble();
    }

    return distBtwn;
}

bool dbManager::checkCampusName(QString campus)
{
    bool execute = false;
    QSqlQuery qry;
    qry.prepare("SELECT * from Distances where distStart = '" +campus+ "'");

    if(qry.exec())
    {
        execute = qry.next();
    }
    return execute;
}

int dbManager::GetCampusCount(QString campus)
{
    int campusCount = 0;
    QString sQry = "select count(distStart) from Distances where distStart = '" +campus+ "';";

    QSqlQuery qry;
    qry.prepare(sQry);
    qry.exec();

    if(qry.next())
    {
        campusCount= qry.value(0).toInt();
    }

    return campusCount + 1;
}
