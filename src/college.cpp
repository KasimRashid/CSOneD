#include "college.h"
#include <QSqlRecord>
#include <QSqlQuery>
#include <QString>
#include <QVector>
#include <QDir>
#include <QDebug>

/**
 * @brief College::College
 */
College::College() {}

/**
 * @brief College::College
 * @param initID
 * @param initName
 */
College::College(int initID, QString initName) : collegeID(initID), collegeName(initName) {}

/**
 * @brief College::getCollegeID
 * @return
 */
int College::getCollegeID() const
{
    return this->collegeID;
}

/**
 * @brief College::getCollegeName
 * @return
 */
QString College::getCollegeName() const
{
    return this->collegeName;
}

/**
 * @brief College::setCollegeName
 * @param name
 */
void College::setCollegeName(QString name)
{
    collegeName = name;
}

/**
 * @brief College::setCollegeId
 * @param id
 */
void College::setCollegeId(int id)
{
    collegeID = id;
}

/**
 * @brief College::setCollege
 * @param name
 * @param id
 */
void College::setCollege(QString name, int id)
{
    collegeID   = id;
    collegeName = name;
}

QVector<College> College::getColleges()
{
    QVector<College> collegeVec;

    QSqlQuery query("SELECT * FROM College_Touring ORDER BY Name");

    int collegeID1 = query.record().indexOf("ID");
    int collegeName1 = query.record().indexOf("Universities");

    while(query.next())
    {
        College newCollege = College(query.value(collegeID1).toInt(), query.value(collegeName1).toString());

        collegeVec.push_back(newCollege);
    }

    return collegeVec;
}
