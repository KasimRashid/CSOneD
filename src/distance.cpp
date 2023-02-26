#include "distance.h"

/**
 * @brief Distance::Distance
 */
Distance::Distance() {}

/**
 * @brief Distance::Distance
 * @param initStartCollege
 * @param initEndCollege
 * @param initDistance
 */
Distance::Distance(College initStartCollege, College initEndCollege, int initDistance) :
    startCollege(initStartCollege), endCollege(initEndCollege), distance(initDistance) {}

/**
 * @brief Distance::getStartCollege
 * @return
 */
College Distance::getStartCollege() const
{
    return this->startCollege;
}

/**
 * @brief Distance::getEndCollege
 * @return
 */
College Distance::getEndCollege() const
{
    return this->endCollege;
}

/**
 * @brief Distance::getDistance
 * @return
 */
int Distance::getDistance() const
{
    return this->distance;
}

/**
 * @brief Distance::setDistance
 * @param initStartCollege
 * @param initEndCollege
 * @param initDistance
 */
void Distance::setDistance(College initStartCollege, College initEndCollege, int initDistance)
{
    startCollege = initStartCollege;
    endCollege   = initEndCollege;
    distance     = initDistance;
}
