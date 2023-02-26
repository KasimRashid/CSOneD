#ifndef SOUVENIR_H
#define SOUVENIR_H

#include "college.h"

/**
 * @brief The Souvenir class
 * Souvenir Class for interacting with souvenirs in the database and displaying in the menus
 */
class Souvenir {
private:
    College souvenirCollege;
    QString souvenirName;
    double souvenirPrice;
public:
    Souvenir();
    /**
     * @brief Souvenir constructor
     * @param initSouvenirCollege College selling Souvenir
     * @param initSouvenirName Name of Souvenir
     * @param initSouvenirPrice Price of Souvenir
     */
    Souvenir(College initSouvenirCollege, QString initSouvenirName, double initSouvenirPrice);
    /**
     * @brief getSouvenirCollege
     * @return College selling the Souvenir
     */
    College getSouvenirCollege() const;
    /**
     * @brief getSouvenirName
     * @return Name of the Souvenir
     */
    QString getSouvenirName() const;
    /**
     * @brief getSouvenirPrice
     * @return Price of the Souvenir
     */
    double getSouvenirPrice() const;
};

#endif // SOUVENIR_H
