// Author: Tristan English
// Recitation: 225 – Connor Thompson
// Project 3

#include "Wagon.h"
#include "Player.h"
#include "Shop.h"
#include "Date.h"
#include <iostream>
#include <string>
using namespace std;

// Default constructor
Date::Date()
{
    month = 3;
    day = 28;
    year = 1847;
}

// Parameterized constructor
Date::Date(int m, int d, int y)
{
    month = m;
    day = d;
    year = y;
}

/*
* This function takes a string, splits it at every occurrence of a delimiter, and then
populates an array of strings with the split pieces, up to the provided maximum number of pieces.
* Parameters: splitString - string we are splitting up, separator - delimeter we break the string at,
arr[] - array we are filling with split pieces, size - size of the array (maximum number of pieces)
* Return: the number of pieces the string was split into, as an integer.
*/
int Date::split(string splitString, char separator, string arr[], int size)
{
    // Declare variables for the index of the string, the delimeter counter, the index of the array (arrayPosition),
    // and a counter for how many elements we have split (splitElements)
    int index = 0;
    int counter = 0;
    int arrayPosition = 0;
    int splitElements = 1;

    // Declare a temporary string (we will use this to find the length of our substring))
    string tempSplitString = "";

    // If we are given an empty string, return 0
    if (splitString.length() == 0)
    {
        return 0;
    }

    // Traverse each character of the string
    for (int i = 0; i < splitString.length(); i++)
    {
        // If we have more elements than we can hold in the string, return -1
        if (splitElements > size)
        {
            return -1;
        }

        // If we find a delimeter
        if (splitString[i] == separator || splitString[i] == separator)
        {
            // Record the index where the delimeter is
            index = i;

            // Take our word before the delimeter and put it into the array
            arr[arrayPosition] = splitString.substr(0,i);

            // Make our temporary string our word so we can find the length
            tempSplitString = splitString.substr(0,i);

            // Incremenet the array position by 1 so our next word goes into the next value of the array
            arrayPosition +=1;

            // Take our string we are traversing, and remove the word we just split out if it
            // For example, in the first case of (Apple/Banana/Orange), our new string will be (Banana/Orange)
            splitString = splitString.substr(index + 1, splitString.length() - tempSplitString.length() - 1);

            // Increment the delimeter counter since we found a delimeter
            counter++;

            // Increment the element counter by 1 since a new delimeter also means a new element (we don't have cases where
            // the delimeter occurs at the end of the string)
            splitElements++;

            // Reset i to 0 so we start iterating at the beginning of our new string
            i = 0;
        }
    }

    // If we don't find any delimeters
    if (counter == 0)
    {
        // The first element of our array will just be the original string
        arr[0] = splitString;
        // Return 1
        return 1;
    }

    // At the very end of the string, we will be left with a word without any delimeters.
    // Set the next element of our array to just be the entire remaining string
    // Ex: At the end of (Apple/Banana/Orange), we will be left with (Banana). Put "Banana" into the array
    arr[arrayPosition] = splitString.substr(0, splitString.length());

    // Return the number of elements we have split
    return splitElements;
}

/*
* This function takes input from a user provided that the input isn't empty
* Parameters: none
* Return: tempInput - the non-empty input we got from the user as a string
*/
string Date::askForInput()
{
    string tempInput;
    getline(cin, tempInput);
    // While the user enters an empty string, keep asking them for input
    while (tempInput.length() == 0)
    {
        getline(cin, tempInput);
    }
    // Return the string input
    return tempInput;
    
}

/*
* This function asks the user for the date, checks to make sure it is valid, and sets the date.
* Parameters: none
* Return: nothing (void)
*/
void Date::askForDate()
{
    string inputString;
    const int SIZE = 3;
    string arr[SIZE];
    bool dayTooLarge = false;

    // Ask the user for a date
    cout << "You can change it to any date between: 03/01/1847 to 05/01/1847" << endl;
    cout << "Date (mm/dd/yyyy): ";
    inputString = askForInput();

    // If the user enters something that is not 10 characters long, ask again
    while (inputString.length() != 10)
    {
        cout << "Invalid input. Please put the date in the format (mm/dd/yyyy)" << endl;
        cout << "Invalid format." << endl;
        cout << "Date (mm/dd/yyyy): ";
        inputString = askForInput();
        split(inputString, '/', arr, 3);
    }

    // Split the date into pieces by the '/', and put it into an array of strings
    split(inputString, '/', arr, 3);
 
    // Go through the entire input string
    for (int i = 0; i < inputString.length(); i++)
    {
        // If we find any character that is not either a digit or a '/', invalid character
        while (!isdigit(inputString[i]) && inputString[i] != '/')
        {
            cout << "Invalid input. Please put the date in the format (mm/dd/yyyy)" << endl;
            cout << "Invalid character." << endl;
            cout << "Date (mm/dd/yyyy): ";
            inputString = askForInput();
            split(inputString, '/', arr, 3);
            i = 0;
        }
    }

    // If the year is not 1847, invalid
    while(arr[2] != "1847")
    {
        cout << "Invalid input. Remember you can change it to any date between: 03/01/1847 to 05/01/1847" << endl;
        cout << "Invalid year." << endl;
        cout << "Date (mm/dd/yyyy): ";
        inputString = askForInput();
        split(inputString, '/', arr, 3);
    }

    // If the length of each split element is not 2, 2, 4 respectively, invalid
    while (arr[0].length() != 2 || arr[1].length() != 2 || arr[2].length() != 4)
    {
        cout << "Invalid input. Please put the date in the format (mm/dd/yyyy)" << endl;
        cout << "Invalid format." << endl;
        cout << "Date (mm/dd/yyyy): ";
        inputString = askForInput();
        split(inputString, '/', arr, 3);
    }

    // If the month is not between 3 and 5 or we have an empty day/month, invalid
    while(stoi(arr[0]) > 5 || stoi(arr[0]) < 3 || arr[0] == "00" || arr[1] == "00")
    {
        cout << "Invalid input. Remember you can change it to any date between: 03/01/1847 to 05/01/1847" << endl;
        cout << "Invalid month." << endl;
        cout << "Date (mm/dd/yyyy): ";
        inputString = askForInput();
        split(inputString, '/', arr, 3);
    }

    // If the month is May but past the 1st, invalid
    while (stoi(arr[0]) == 5 && stoi(arr[1]) > 1)
    {
        cout << "Invalid input. Remember you can change it to any date between: 03/01/1847 to 05/01/1847" << endl;
        cout << "Invalid day." << endl;
        cout << "Date (mm/dd/yyyy): ";
        inputString = askForInput();
        split(inputString, '/', arr, 3);
    }

    // Enter a switch statement for the month
    switch(stoi(arr[0]))
    {
        // If the month is January, March, May, July, August, October, or December
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            // and if the day is greater than 30
            if (stoi(arr[1]) > 31)
            {
                // Our day is too large
                dayTooLarge = true;
            }
            // Otherwise our day is not too large
            else
            {
                dayTooLarge = false;
            }
            break;
        // If the month is February
        case 2:
            // and if the day is greater than 28
            if (stoi(arr[1]) > 28)
            {
                // Our day is too large
                dayTooLarge = true;
            }
            // Otherwise, our day is not too large
            else
            {
                dayTooLarge = false;
            }
            break;
        // If the day is April, June, September, or November
        case 4:
        case 6:
        case 9:
        case 11:
            // and if the day is greater than 30
            if (stoi(arr[1]) > 30)
            {
                // Our day is too large
                dayTooLarge = true;
            }
            // Otherwise, our day is not too large
            else
            {
                dayTooLarge = false;
            }
            break;
    }

    // While the day is too large
    while(dayTooLarge)
    {
        // Tell the user they can't have this many days in that month
        cout << "Invalid input. You cannot have this many days in this month" << endl;
        cout << "Date (mm/dd/yyyy): ";
        // Ask the user for input, and split it up again
        inputString = askForInput();
        split(inputString, '/', arr, 3);

        // Check it again using the same switch statement
        switch(stoi(arr[0]))
        {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if (stoi(arr[1]) > 31)
                {
                    dayTooLarge = true;
                }
                else
                {
                    dayTooLarge = false;
                }
                break;
            case 2:
                if (stoi(arr[1]) > 28)
                {
                    dayTooLarge = true;
                }
                else
                {
                    dayTooLarge = false;
                }
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                if (stoi(arr[1]) > 30)
                {
                    dayTooLarge = true;
                }
                else
                {
                    dayTooLarge = false;
                }
                break;
        }
    }

    // Finally split it up into an array
    split(inputString, '/', arr, 3);
    // Put the pieces into month, day, and year
    month = stoi(arr[0]);
    day = stoi(arr[1]);
    year = stoi(arr[2]);
}

/*
* This function displays the date to the user in the format mm/dd/yyyy, adding appropriate zeros where necessary.
* Parameters: none
* Return: nothing (void)
*/
void Date::displayDate()
{

   // Check the day 
   switch (day)
   {
       // If the day is 1-9 (one digit)
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            // Add a zero to the front of the day string (9 = 09)
            sDay = '0' + to_string(day);
            break;
        // If it's a two digit number, leave the string unchanged
        default:
            sDay = to_string(day);
            break;
   }

   // Check the month 
   switch (month)
   {
       // If the month is 1-9 (one digit)
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            // Add a zero to the front of the month string (9 = 09)
            sMonth = '0' + to_string(month);
            break;
        // Otherwise, leave the month string unchanged
        default:
            sMonth = to_string(month);
            break;
   }

    // Output the date to the user using these strings
   cout << "Today's date is: " << sMonth << "/" << sDay << "/" << year << endl;
}

int Date::getMonth() const
{
    return month;
}

int Date::getDay() const
{
    return day;
}

int Date::getYear() const
{
    return year;
}

string Date::getMonthString() const
{
    return sMonth;
}

string Date::getDayString() const
{
    return sDay;
}

void Date::setDayString(string s)
{
    sDay = s;
}

void Date::setMonthString(string s)
{
    sMonth = s;
}

void Date::setDate(int m, int d, int y)
{
    month = m;
    day = d;
    year = y;
}

/*
* This function increments the day by a certain number, accounting for month and year changes for months with
* 31/30/28 days
* Parameters: days - integer number of days we are incrementing by
* Return: nothing (void)
*/
void Date::daysIncrement(int days)
{
    // Increment the date day by day
    for (int i = 1; i <= days; i++)
    {
        day += 1;
        // Check the month
        switch (month)
        {
            // If the month is January, March, May, July, August, or October
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
                // and if the day is greater than 31
                if (day > 31)
                {
                    // Increment the month
                    month += 1;
                    // Set the day to 1
                    day = 1;
                }
                break;
            // If the month is December
            case 12:
                // and if the day is greater than 31
                if (day > 31)
                {
                    // Set the month to January
                    month = 1;
                    // Set the day to 1
                    day = 1;
                    // Increment the year
                    year += 1;
                }
                break;
            // If the month is February
            case 2:
                // and if the day is greater than 38
                if (day > 28)
                {
                    // Increment the month
                    month += 1;
                    // Set the day to 1
                    day = 1;
                }
                break;
            // If the month is April, June, September, November
            case 4:
            case 6:
            case 9:
            case 11:
                // and if the day is greater than 30
                if (day > 30)
                {
                    // Increment the month
                    month += 1;
                    // Set the day to 1
                    day = 1;
                }
                break;
            // If somehow the month is not one of these numbers, output an error message
            default:
                cout << "Something went wrong..." << endl;
                break;
        }
    }
}