// Author: Tristan English
// Recitation: 225 – Connor Thompson
// Project 3

#include <string>
#ifndef DATE_H
#define DATE_H

using namespace std;

class Date
{
    public:
        Date();
        Date(int m, int d, int y);
        int split(string splitString, char separator, string arr[], int size);
        string askForInput();
        void displayDate();
        void askForDate();

        int getMonth() const;
        int getDay() const;
        int getYear() const;
        string getMonthString() const;
        string getDayString() const;
        void setDayString(string s);
        void setMonthString(string s);
        void setDate(int m, int d, int y);
        
        void daysIncrement(int days);
    private:
        int month;
        int day;
        int year;
        string sMonth;
        string sDay;

};
#endif