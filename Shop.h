// Author: Tristan English
// Recitation: 225 – Connor Thompson
// Project 3

#include <string>
#include "Wagon.h"

#ifndef SHOP_H
#define SHOP_H

class Shop
{
    public:
        Shop();
        Shop(int storeNumber, int balance, int bulletPrice, double foodPrice, int oxenPrice, int wagonPartPrice, int medPrice);
        int askForNumInput();
       
        void displayBill();

        double getBulletsPrice() const;
        double getFoodPrice() const;
        double getOxenPrice() const;
        double getWagonPartPrice() const;
        double getMedPrice() const;
        int getStoreNumber() const;
        double getBill() const;
        void setStoreNumber(int num);
        void setBill(int b);
        void setBulletsPrice(double b);
        void setFoodPrice (double f);
        void setOxenPrice(double o);
        void setWagonPartPrice(double wp);
        void setMedPrice(double m);

    private:
        double bulletsPrice;
        double foodPrice;
        double oxenPrice;
        double wagonPartPrice;
        double medPrice;
        int storeNumber;
        double bill;

};
#endif