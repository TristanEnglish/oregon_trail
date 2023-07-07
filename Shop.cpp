// Author: Tristan English
// Recitation: 225 – Connor Thompson
// Project 3

#include "Wagon.h"
#include "Player.h"
#include "Shop.h"
#include <iostream>
using namespace std;

// Default constructor
Shop::Shop()
{
    storeNumber = 1;
    bill = 0;
    bulletsPrice = 2;
    foodPrice = 0.50;
    oxenPrice = 40;
    wagonPartPrice = 20;
    medPrice = 25;
}

// Parameterized constructor
Shop::Shop(int sn, int b, int bullet, double food, int oxen, int wagonPart, int med)
{
    storeNumber = sn;
    bill = b;
    bulletsPrice = bullet;
    foodPrice = food;
    oxenPrice = oxen;
    wagonPartPrice = wagonPart;
    medPrice = med;
}


/*
* This function takes input from the user given the input is an integer number.
* Parameters: none
* Return: integer input (int)
*/
int Shop::askForNumInput()
{
    string tempInput;
    getline(cin, tempInput);
    // If the user enters an empty string, don't take it
    while (tempInput.length() == 0)
    {
        getline(cin, tempInput);
    }
    
    // If the user didn't enter a digit, ask for input again until they do
    for (int i = 0; i < tempInput.length(); i++)
    {
        while (!isdigit(tempInput[i]))
        {
            cout << "Invalid input. Please enter an integer number" << endl;
            getline(cin, tempInput);
        }
    }

    // Return the user's input as an integer
    return stoi(tempInput);
    
}

/*
* This function displays the user's current bill.
* Parameters: none
* Return: nothing (void)
*/
void Shop::displayBill()
{
    // Tell the user their current bill
    cout << "Your current bill is " << getBill() << endl;
}

double Shop::getBulletsPrice() const
{
    return bulletsPrice;
}

double Shop::getFoodPrice() const
{
    return foodPrice;
}

double Shop::getOxenPrice() const
{
    return oxenPrice;
}

double Shop::getWagonPartPrice() const
{
    return wagonPartPrice;
}

double Shop::getMedPrice() const
{
    return medPrice;
}

int Shop::getStoreNumber() const
{
    return storeNumber;
}

double Shop::getBill() const
{
    return bill;
}

void Shop::setStoreNumber(int num)
{
    storeNumber = num;
}

void Shop::setBill(int b)
{
    bill  = b;
}

void Shop::setBulletsPrice(double b)
{
    bulletsPrice = b;
}

void Shop::setFoodPrice (double f)
{
    foodPrice = f;
}

void Shop::setOxenPrice(double o)
{
    oxenPrice = o;
}

void Shop::setWagonPartPrice(double wp)
{
    wagonPartPrice = wp;
}

void Shop::setMedPrice(double m)
{
    medPrice = m;
}
