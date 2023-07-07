// Author: Tristan English
// Recitation: 225 – Connor Thompson
// Project 3

#include "Wagon.h"
#include <iostream>
using namespace std;


// Default constructor
Wagon::Wagon()
{
    food = 0;
    bullets = 0;
    wagonParts = 0;
    medKit = 0;
    balance = 1600;
    oxen = 0;
    milesTraveled = 0;
    numFamilyMembers = 5;
}

// Parameterized constructor
Wagon::Wagon(int f, int b, int wp, int mk, int bal, int ox, Player fam[], int mt)
{
    food = f;
    bullets = b;
    wagonParts = wp;
    medKit = mk;
    balance = bal;
    oxen = ox;
    milesTraveled = mt;

    for (int i = 0; i < 4; i++)
    {
        family[i] = fam[i];
    }
}

/*
* This function takes input from the user given the input is an integer number.
* Parameters: none
* Return: integer input (int)
*/
int Wagon::askForNumInput()
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
* This function takes input from a user provided the input is a Y or N
* Parameters: none
* Return: inputString - the Y or N input as a string
*/
string Wagon::askForInputChar()
{
    string inputString;
    getline(cin, inputString);
    // While the user is not entering a Y or and N, keep asking them
    while (inputString != "Y" && inputString != "y" && inputString != "N" && inputString != "n")
    {
        cout << "Invalid input. Please enter Y or N" << endl;
        getline(cin, inputString);
    }
    // Return the y or n character as a string
    return inputString;
}

void Wagon::setFood(int f)
{
    food = f;
}

int Wagon::getFood() const
{
    return food;
}

void Wagon::setBullets(int b)
{
    bullets = b;
}

int Wagon::getBullets() const
{
    return bullets;
}

void Wagon::setWagonParts(int wp)
{
    wagonParts = wp;
}

int Wagon::getWagonParts() const
{
    return wagonParts;
}

void Wagon::setMedKit(int mk)
{
    medKit = mk;
}

int Wagon::getMedKit() const
{
    return medKit;
}

void Wagon::setBalance(int bal)
{
    balance = bal;
}

int Wagon::getBalance() const
{
    return balance;
}

void Wagon::setOxen(int ox)
{
    oxen = ox;
}


int Wagon::getOxen() const
{
    return oxen;
}

void Wagon::setMilesTraveled(int miles)
{
    milesTraveled = miles;
}

int Wagon::getMilesTraveled() const
{
    return milesTraveled;
}

int Wagon::getRandomMilesTraveled()
{
    /*
    - Get a random number from 70 to 140
    - This number will be the number of miles we travel on a turn
    - Return the number of miles the user travels this turn
    */
    srand(time(NULL));
    int randomNum = rand() % (140 - 70 + 1) + 70;
    return randomNum;
}

Player Wagon::getPlayer1()
{
    return player1;
}

Player Wagon::getFamilyMember1() 
{
    return family[0];
}

Player Wagon::getFamilyMember2()
{
    return family[1];
}

Player Wagon::getFamilyMember3()
{
    return family[2];
}

Player Wagon::getFamilyMember4()
{
    return family[3];
}


int Wagon::getNumFamilyMembers()
{
    return numFamilyMembers;
}

void Wagon::setNumFamilyMembers(int n)
{
    numFamilyMembers = n;
}

void Wagon::setFamilyMember1(Player p)
{
    family[0] = p;
}

void Wagon::setFamilyMember2(Player p)
{
    family[1] = p;
}

void Wagon::setFamilyMember3(Player p)
{
    family[2] = p;
}

void Wagon::setFamilyMember4(Player p)
{
    family[3] = p;
}

void Wagon::setPlayer1(Player p)
{
    player1 = p;
}
