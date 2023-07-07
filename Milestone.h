// Author: Tristan English
// Recitation: 225 – Connor Thompson
// Project 3

#include <string>
#include <vector>
#ifndef MILESTONE_H
#define MILESTONE_H

using namespace std;

class Milestone
{
    public:
        Milestone();
        Milestone(int m, string t, string n);
        string getType() const;
        int getMiles() const;
        string getName() const;
        void setName(string n);
        void setMiles(int m);
        void setType(string t);
    private:
        string type;
        string name;
        int miles;
};
#endif