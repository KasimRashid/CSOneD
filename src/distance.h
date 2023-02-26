#ifndef DISTANCE_H
#define DISTANCE_H

#include "college.h"

/**
 * @brief The Distance class
 * Represents two colleges and their distances
 */
class Distance {
private:
    College startCollege;
    College endCollege;
    int distance;
public:
    Distance();
    /**
     * @brief Distance constructor
     * @param initStartCollege Starting College
     * @param initEndCollege Ending College
     * @param initDistance Distance between starting and ending College
     */
    Distance(College initStartCollege, College initEndCollege, int initDistance);
    /**
     * @brief getStartCollege
     * @return Starting College
     */
    College getStartCollege() const;
    /**
     * @brief getEndCollege
     * @return Ending College
     */
    College getEndCollege() const;
    /**
     * @brief getDistance
     * @return Distance between the starting and ending College
     */
    int getDistance() const;
    void setDistance(College initStartCollege, College initEndCollege, int initDistance);

};

#endif // DISTANCE_H
