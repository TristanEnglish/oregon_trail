// Author: Tristan English
// Recitation: 225 – Connor Thompson
// Project 3

#include <string>
#include "Player.h"
#include "Milestone.h"
#include "Date.h"
#include <vector>
#ifndef WAGON_H
#define WAGON_H

using namespace std;

class Wagon
{
    public:
        Wagon();
        Wagon(int food, int bullets, int wagonParts, int medKit, int balance, int oxen, Player family[], int milesTraveled);
        string askForInputChar();
        int askForNumInput();
        void setFood(int food);
        int getFood() const;
        void setBullets(int bullets);
        int getBullets() const;
        void setWagonParts(int wagonParts);
        int getWagonParts() const;
        void setMedKit(int medKit);
        int getMedKit() const;
        void setBalance(int balance);
        int getBalance() const;
        void setOxen(int oxen);
        int getOxen() const;
        void setMilesTraveled(int miles);
        int getMilesTraveled() const;
        int getRandomMilesTraveled();
        Player getPlayer1();
        Player getFamilyMember1();
        Player getFamilyMember2();
        Player getFamilyMember3();
        Player getFamilyMember4();

        
        Date getDate();
        int getNumFamilyMembers();
        void setNumFamilyMembers(int n);
        void setFamilyMember1(Player p);
        void setFamilyMember2(Player p);
        void setFamilyMember3(Player p);
        void setFamilyMember4(Player p);
        void setDate(Date d);
        void setPlayer1(Player p);
    private:
        int food;
        Player player1;
        int bullets;
        int wagonParts;
        int medKit;
        int balance;
        int oxen;
        int milesTraveled;
        static const int SIZE = 4;
        int numFamilyMembers;
        Player family[SIZE];
};
#endif