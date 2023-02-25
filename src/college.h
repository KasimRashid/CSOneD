#ifndef COLLEGE_H
#define COLLEGE_H

#include <QString>
#include <QVector>

/**
 * @brief The College class
 * Represents a College that may be selling Souvenirs
 */
class College {
private:
    int collegeID;
    QString collegeName;
public:
    College();
    /**
     * @brief College constructor
     * @param collegeID ID of College
     * @param collegeName Name of College
     */
    College(int collegeID, QString collegeName);
    /**
     * @brief getCollegeID
     * @return ID of College
     */
    int getCollegeID() const;
    /**
     * @brief getCollegeName
     * @return Name of the College
     */
    QString getCollegeName() const;

    void setCollegeName(QString name);
    void setCollegeId(int id);
    void setCollege(QString name, int id);
    QVector<College> getColleges();
    QVector<College> colleges;
};

#endif // COLLEGE_H
