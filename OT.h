// Author: Tristan English
// Recitation: 225 – Connor Thompson
// Project 3

#include <string>
#include <vector>
#include "Player.h"
#include "Milestone.h"
#include "Date.h"
#include "Wagon.h"
#include "Shop.h"
#ifndef OT_H
#define OT_H

using namespace std;

class OT
{
    public:
        OT();
        OT(Date d, Wagon w, Shop s, vector <Milestone> m, int index, int miles, int turnmiles);

        Date getDate();
        void setDate(Date d);
        Shop getShop();
        void setShop(Shop s);
        Wagon getWagon();
        void setWagon(Wagon w);


        void setTurnMiles(int m);
        int getTurnMiles();
        void setMilestones(vector <Milestone> m);
        vector <Milestone> getMilestones();
        int getMilestoneIndex() const;
        int getMilesToMilestone() const;
        void setMilestoneIndex(int i);
        void setMilesToMilestone(int m);

        int buyMeds();
        int buyWagonParts();
        int buyOxen();
        int buyFood();
        int buyBullets();
        void displayShop();


        int Stop();
        int checkGameOver();
        void Rest();
        void sickRest();
        void Continue();
        void Hunt();
        void Run();
        void Attack();
        void Surrender();
        int Puzzle();
        int Sick(Player p);

        int split(string splitString, char separator, string arr[], int size);
        void readMilestones();
        int calculateMilesToMilestone();
        int takeTurn();
        void displayStatusUpdate();
        int rollSick();
        int rollOxenDeath();
        int rollBreakage();
        void rollRaiders(int milesTraveled);
        void gameOver();
    private:
        Date date;
        Wagon wagon;
        Shop shop;
        vector <Milestone> milestones;
        int milestoneIndex;
        int milesToMilestone;
        int turnMiles;
};
#endif