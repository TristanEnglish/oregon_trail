// Author: Tristan English
// Recitation: 225 – Connor Thompson
// Project 3

#include "Milestone.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

// Default constructor
Milestone::Milestone()
{
    type = "Default Milestone";
    miles = 100;
    name = "Default Name";
}

// Parameterized constructor
Milestone::Milestone(int m, string t, string n)
{
    type = t;
    miles = m;
    name = n;
}

string Milestone::getType() const
{
    return type;
}

int Milestone::getMiles() const
{
    return miles;
}
        
string Milestone::getName() const
{
    return name;
}

void Milestone::setName(string n)
{
    name = n;
}

void Milestone::setMiles(int m)
{
    miles = m;
}

void Milestone::setType(string t)
{
    type = t;
}