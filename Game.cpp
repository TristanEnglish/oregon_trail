// Author: Tristan English
// Recitation: 225 – Connor Thompson
// Project 3

#include "Wagon.h"
#include "Player.h"
#include "Shop.h"
#include "Date.h"
#include "OT.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*
* This function takes input from a user provided the input is a Y or N
* Parameters: none
* Return: inputString - the Y or N input as a string
*/
string askForInputChar()
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

/*
* This function takes input from a user provided that the input isn't empty
* Parameters: none
* Return: tempInput - the non-empty input we got from the user as a string
*/
string askForInput()
{
    string tempInput;
    getline(cin, tempInput);
    // While the user enters an empty string, keep asking them
    while (tempInput.length() == 0)
    {
        getline(cin, tempInput);
    }

    // Return their string input
    return tempInput;
    
}


int main()
{
    string inputString;
    bool isSick = false;
    OT main;
    Date tempDate;
    Wagon tempWagon;
    // Ask the player for the name of the wagon leader
    cout << "What is the first name of the wagon leader?" << endl;
    Player player1 = Player(askForInput(), isSick);
    tempWagon.setPlayer1(player1);

    // Ask the player for the names of the family members
    cout << "What are the first names of the four other members in your party?" << endl;
    tempWagon.setFamilyMember1(Player(askForInput(), isSick));
    tempWagon.setFamilyMember2(Player(askForInput(), isSick));
    tempWagon.setFamilyMember3(Player(askForInput(), isSick));
    tempWagon.setFamilyMember4(Player(askForInput(), isSick));

    main.setWagon(tempWagon);

    // Ask the user if they'd like to visit the store
    cout << "You are starting at mile: " << main.getWagon().getMilesTraveled() << "." << endl;
    cout << "There are 2040 miles that you must travel to reach your destination." << endl;
    cout << "Before the start of your trip, you can visit the store and buy supplies: food, oxen," << endl;
    cout << "bullets and wagon parts. Would you like to visit the store? (Y/N)" << endl;
    inputString = askForInputChar();

    // If the user says yes
    if (inputString == "Y" || inputString == "y")
    {
        // Display the shop to them w/ options
        main.displayShop();
    }

    // Ask the user if they'd like to change the date
    cout << "Your departure date currently is: 03/28/1847. Would you like to change it? (Y/N)" << endl;
    inputString = askForInputChar();

    // If the user says yes
    if (inputString == "Y" || inputString == "y")
    {
        // Get a date from the user
        tempDate.askForDate();
    }
    
    main.setDate(tempDate);

    // Read the milestones from "milestones.txt"
    main.readMilestones();

    // Display the first status update to the user
    cout << endl;
    cout << "You must reach Oregon City by 11/30/1847. " << endl;
    cout << endl;
    cout << "Let the journey begin!" << endl;
    cout << endl;
    cout << "--------------STATUS UPDATE--------------" << endl;
    main.getDate().displayDate();
    cout << endl;
    cout << "Miles Traveled: " << "0" << endl;
    cout << "Miles to Next Milestone: " << "0" << endl;
    cout << "Next Milestone: " << main.getMilestones().at(0).getName() << endl;
    cout << "Food: " << main.getWagon().getFood() << " lbs" << endl;
    cout << "Bullets: " << main.getWagon().getBullets() << endl;
    cout << "Wagon Parts: " << main.getWagon().getWagonParts() << endl;
    cout << "Oxen: " << main.getWagon().getOxen() << endl;
    cout << "Cash: $" << main.getWagon().getBalance() << endl;
    cout << "Wagon Members: ";
    cout << main.getWagon().getPlayer1().getUsername() << " ";
    cout << main.getWagon().getFamilyMember1().getUsername() << " ";
    cout << main.getWagon().getFamilyMember2().getUsername() << " ";
    cout << main.getWagon().getFamilyMember3().getUsername() << " ";
    cout << main.getWagon().getFamilyMember4().getUsername() << " ";
    cout << endl;
    cout << endl;


    // Continue to play the game unitl we get a game over
    while (main.takeTurn() != -1)
    {

    }

    // When the game ends, write the player's results to "results.txt"
    main.gameOver();



    return 0;
}