#ifndef TOURCAMPUSES_H
#define TOURCAMPUSES_H

#include <QDialog>
#include "mainwindow.h"
#include "tourpurchase.h"

namespace Ui {
class tourCampuses;
}

class tourCampuses : public QDialog
{
    Q_OBJECT

public:
    explicit tourCampuses(QWidget *parent = 0);
    ~tourCampuses();

private slots:
    /**
     * @brief populate
     */
    void populate();

    /**
     * @brief on_back_to_main_clicked
     */
    void on_back_to_main_clicked();

    /**
     * @brief on_pushButton_startColleges_clicked
     */
    void on_pushButton_startColleges_clicked();

    /**
     * @brief on_endingCollege_pushButton_clicked
     */
    void on_endingCollege_pushButton_clicked();

    /**
     * @brief findDistanceTwoCollege
     */
    void findDistanceTwoCollege();

    /**
     * @brief displaySelectedColleges
     */
    void displaySelectedColleges();

    /**
     * @brief on_distanceMode_pushButton_clicked
     */
    void on_distanceMode_pushButton_clicked();

    /**
     * @brief on_tripMode_pushButton_clicked
     */
    void on_tripMode_pushButton_clicked();

    /**
     * @brief on_addColleges_button_clicked
     */
    void on_addColleges_button_clicked();

    /**
     * @brief on_deleteColleges_button_clicked
     */
    void on_deleteColleges_button_clicked();

    /**
     * @brief on_beginTrip_pushButton_clicked
     */
    void on_beginTrip_pushButton_clicked();

    /**
     * @brief findTrip
     * @param count
     * @param visitedCollege
     * @param totalDistance
     */
    void findTrip(int count, int visitedCollege, double totalDistance);

    /**
     * @brief findUciTrip
     * @param count
     * @param uciVisitedColleges
     */
    void findUciTrip(int count, int uciVisitedColleges);

    /**
     * @brief findMichiganTrip
     * @param count
     * @param miVisitedColleges
     */
    void findMichiganTrip(int count, int miVisitedColleges);

    /**
     * @brief findSaddlebackTrip
     * @param count
     * @param saVisitedColleges
     */
    void findSaddlebackTrip(int count, int saVisitedColleges);

    /**
     * @brief on_pushButton_UCI_clicked
     */
    void on_pushButton_UCI_clicked();

    /**
     * @brief on_pushButton_MICHIGAN_clicked
     */
    void on_pushButton_MICHIGAN_clicked();

    /**
     * @brief on_pushButton_SADDLEBACK_clicked
     */
    void on_pushButton_SADDLEBACK_clicked();

    /**
     * @brief on_purchaseTour_pushButton_clicked
     */
    void on_purchaseTour_pushButton_clicked();

    /**
     * @brief on_pushButton_startMiTour_clicked
     */
    void on_pushButton_startMiTour_clicked();

    void on_purchaseTour_uciTour_clicked();

    void on_purchaseTour_saddlebackTour_clicked();

    void on_purchaseTour_MichiganTour_clicked();

private:
    Ui::tourCampuses *ui;
    QVector<College>  collegeList;
    QVector<Distance> distanceList;
    QVector<Souvenir> souvenirsList;
    int IdsDistances[2];
    QVector<College> selectedColleges;
    QVector<Distance> tourDistanceColleges;

    QVector<College> uciTourColleges;
    QVector<Distance> uciTourDistanceColleges;
    double totalUciDistance;
    QVector<College> miTourColleges;
    QVector<Distance> miTourDistanceColleges;
    double totalMiDistance;
    int collegeNum;
    QVector<College> saTourColleges;
    QVector<Distance> saTourDistanceColleges;
    double totalSaDistance;
    int counter;
};

#endif // TOURCAMPUSES_H
