#include "souvenir.h"

/**
 * @brief Souvenir::Souvenir
 */
Souvenir::Souvenir() {}

/**
 * @brief Souvenir::Souvenir
 * @param initSouvenirCollege
 * @param initSouvenirName
 * @param initSouvenirPrice
 */
Souvenir::Souvenir(College initSouvenirCollege, QString initSouvenirName, double initSouvenirPrice) :
    souvenirCollege(initSouvenirCollege), souvenirName(initSouvenirName), souvenirPrice(initSouvenirPrice) {}

/**
 * @brief Souvenir::getSouvenirCollege
 * @return
 */
College Souvenir::getSouvenirCollege() const
{
    return this->souvenirCollege;
}

/**
 * @brief Souvenir::getSouvenirName
 * @return
 */
QString Souvenir::getSouvenirName() const
{
    return this->souvenirName;
}

/**
 * @brief Souvenir::getSouvenirPrice
 * @return
 */
double Souvenir::getSouvenirPrice() const
{
    return this->souvenirPrice;
}
