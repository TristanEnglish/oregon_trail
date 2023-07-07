
#include "Wagon.h"
#include "Player.h"
#include "Date.h"
#include "Milestone.h"
#include "Shop.h"
#include "OT.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

// Default constructor
OT::OT()
{
    date = Date();
    wagon = Wagon();
    shop = Shop();
    vector <Milestone> m;
    milestones = m;
    milestoneIndex = 0;
    milesToMilestone = 0;
    turnMiles = 0;
}

// Parameterized constructor
OT::OT(Date d, Wagon w, Shop s, vector <Milestone> m, int index, int miles, int turnmiles)
{
    date = d;
    wagon = w;
    shop = s;
    milestones = m;
    milestoneIndex = index;
    milesToMilestone = miles;
    turnMiles = turnmiles;
}


Shop OT::getShop()
{
    return shop;
}

void OT::setShop(Shop s)
{
    shop = s;
}


/*
* This function displays a shop to the user, allowing them to buy items over and over again until quitting.
* Parameters: none
* Return: nothing (void)
*/
void OT::displayShop()
{
    int shopInput;
    // Display the shop info to the user
    cout << endl;
    cout << "YOU HAD SAVED $1600 TO SPEND FOR THE TRIP, AND YOU HAVE A" << endl;
    cout << "WAGON. YOU WILL NEED TO SPEND THE REST OF YOUR MONEY ON THE" << endl;
    cout << "FOLLOWING ITEMS:" << endl;
    cout << endl;
    cout << "- OXEN. YOU CAN SPEND $100-$200 ON YOUR TEAM. THE MORE YOU" << endl;
    cout << "SPEND, THE FASTER YOU'LL GO BECAUSE YOU'LL HAVE BETTER ANIMALS." << endl;
    cout << "- FOOD. THE MORE YOU HAVE, THE LESS CHANCE THERE IS OF GETTING" << endl;
    cout << "SICK." << endl;
    cout << "- AMMUNITION. YOU WILL NEED BULLETS FOR ATTACKS BY ANIMALS AND" << endl;
    cout << "BANDITS, AND FOR HUNTING FOOD." << endl;
    cout << "- MISCELLANEOUS SUPPLIES. THIS INCLUDES MEDICINE AND OTHER" << endl;
    cout << "THINGS YOU WILL NEED FOR SICKNESS AND EMERGENCY REPAIRS." << endl;
    cout << endl;
    cout << "YOU CAN SPEND ALL YOUR MONEY BEFORE YOU START YOUR TRIP, OR YOU" << endl;
    cout << "CAN SAVE SOME OF YOUR CASH TO SPEND AT FORTS ALONG THE WAY WHEN" << endl;
    cout << "YOU RUN LOW. HOWEVER, ITEMS COST MORE AT THE FORTS. YOU CAN ALSO" << endl;
    cout << "GO HUNTING ALONG THE WAY TO GET MORE FOOD." << endl;
    cout << endl;
    
    // Tell the user their current balance
    cout << "Right now you have: $" << wagon.getBalance() << endl;
    
    // Display the menu to the user and prompt them for input
    cout << "You can purchase Oxen, Food, Bullets, Wagon Parts, and Med Kits." << endl;
    cout << "1. Oxen" << endl;
    cout << "2. Food" << endl;
    cout << "3. Bullets" << endl;
    cout << "4. Wagon Parts" << endl;
    cout << "5. Med Kits" << endl;
    cout << "6. Quit Shop" << endl;
    cout << "What would you like to purchase?: ";
    shopInput = wagon.askForNumInput();

    // Repeat the following steps until the user quits:
    while (shopInput != 6)
    {
        switch (shopInput)
        {
            // User chooses Oxen
            case 1:
                buyOxen();
                break;
            // User chooses Food
            case 2:
                buyFood();
                break;
            // User chooses Bullets
            case 3:
                buyBullets();
                break;
            // User chooses Wagon Parts
            case 4:
                buyWagonParts();
                break;
            // User chooses Med Kits
            case 5:
                buyMeds();
                break;
            default:
                cout << "Invalid input. Please enter a number 1 through 6" << endl;
        }
        
        // Display the menu to the user again, this time within the loop
        cout << "You can purchase Oxen, Food, Bullets, Wagon Parts, and Med Kits." << endl;
        cout << "1. Oxen" << endl;
        cout << "2. Food" << endl;
        cout << "3. Bullets" << endl;
        cout << "4. Wagon Parts" << endl;
        cout << "5. Med Kits" << endl;
        cout << "6. Quit Shop" << endl;
        cout << "What would you like to purchase?: ";
        shopInput = wagon.askForNumInput();
    }

    // Display the final bill to the user
    cout << endl;
    cout << "Your final bill is: $" << shop.getBill() << endl;
    cout << "You have $" << wagon.getBalance() << " left. Thank you for visiting the store!" << endl;


}

/*
* This function asks a user for a number of bullets and sets the player's bullets, bill, and balance accordingly
* Parameters: none
* Return: the user's bill after calculating (int)
*/
int OT::buyBullets()
{
    double price;
    int boxes;

    // Tell the user bullets information and prompt them for input
    cout << "BULLETS: A box of 20 bullets costs $" <<  shop.getBulletsPrice() <<". You will need bullets for hunting along the way." << endl;
    cout << "How many boxes of bullets do you wish to purchase?: ";

    boxes = wagon.askForNumInput();

    // Calculate the total price of their potential purchase
    price = boxes * shop.getBulletsPrice();

    // If they can afford it
    if (wagon.getBalance() >= price)
    {
        // Set the player's bullets, bill, and balance accordingly
        // Display the bill to them
        // Return the bill
        wagon.setBullets(boxes * 20 + wagon.getBullets());
        shop.setBill(shop.getBill() + price);
        wagon.setBalance(wagon.getBalance() - price);
        cout << endl;
        shop.displayBill();
        return shop.getBill();
    }
    
    // If they can't afford it, tell them so, and prompt them for input again
    while (wagon.getBalance() < price)
    {
        cout << "You do not have enough money to purchase this many bullets. Please try again" << endl;
        cout << "How many boxes of bullets do you wish to purchase?: ";
        boxes = wagon.askForNumInput();
        price = boxes * shop.getBulletsPrice();
    }

    // Set the player's bullets, bill, and balance accordingly
    // Display the bill to them
    // Return the bill
    wagon.setBullets(boxes * 20 + wagon.getBullets());
    shop.setBill(shop.getBill() + price);
    wagon.setBalance(wagon.getBalance() - price);
    cout << endl;
    shop.displayBill();
    return shop.getBill();

}

/*
* This function asks a user for pounds of food and sets the player's food, bill, and balance accordingly
* Parameters: none
* Return: the user's bill (int)
*/
int OT::buyFood()
{
    double price;
    int food;

    // Tell the user food information and prompt them for input
    cout << "FOOD: I recommend at least 200 lbs. per person at the price of $" << shop.getFoodPrice() << " per pound." << endl;
    cout << "Remember the wagon cannot hold more than 1000 lbs. of food." << endl;
    cout << "How many pounds of food do you wish to purchase?: ";

    food = wagon.askForNumInput();

    // Calculate the price of their order
    price = food * shop.getFoodPrice();

    // If the user can afford it, and there is enough space in their wagon
    if (wagon.getBalance() >= price && food + wagon.getFood() <= 1000)
    {
        // Set variables accordingly and display the bill
        wagon.setFood(food + wagon.getFood());
        shop.setBill(shop.getBill() + price);
        wagon.setBalance(wagon.getBalance() - price);
        cout << endl;
        shop.displayBill();
        return shop.getBill();
    }
    
    // If the user can't afford it, tell them so and ask for input again
    while (wagon.getBalance() < price)
    {
        cout << "You do not have enough money to purchase this much food. Please try again" << endl;
        cout << "How many pounds of food do you wish to purchase?: ";
        food = wagon.askForNumInput();
        price = food * shop.getFoodPrice();
    }

    // If the wagon can't hold that much food, tell the user, tell them how much food they have, and prompt them for input again
    while (food + wagon.getFood() > 1000)
    {
        cout << "Your wagon cannot hold this much food." << endl;
        cout << "Your wagon is currently holding " << wagon.getFood() << " pounds of food." << endl;
        cout << "How many pounds of food do you wish to purchase?: ";
        food = wagon.askForNumInput();
        price = food * shop.getFoodPrice();
    }

    // Set variables accordingly and display the bill
    wagon.setFood(food + wagon.getFood());
    shop.setBill(shop.getBill() + price);
    wagon.setBalance(wagon.getBalance() - price);
    cout << endl;
    shop.displayBill();
    return shop.getBill();

}

/*
* This function asks a user for a number of oxen and sets the player's oxen, bill, and balance accordingly
* Parameters: none
* Return: the user's bill (int)
*/
int OT::buyOxen()
{
    double price;
    int yokes;

    // Tell the user oxen info and prompt them for input
    cout << "OXEN: You must purchase between 3 and 5 yokes." << endl;
    cout << "There are 2 oxen in a yoke and the price of each yoke is $" << shop.getOxenPrice() << "." << endl;
    cout << "How many yokes do you wish to purchase?: ";

    yokes = wagon.askForNumInput();

    // Calculate the price
    price = yokes * shop.getOxenPrice();

    // If the user can afford it, and they'll have between 3 and 5 yokes
    if (wagon.getBalance() >= price && (wagon.getOxen() / 2) + yokes >= 3 && (wagon.getOxen() / 2) + yokes <= 5)
    {
        // Set variables accordingly and display the bill
        wagon.setOxen((yokes * 2) + wagon.getOxen());
        shop.setBill(shop.getBill() + price);
        wagon.setBalance(wagon.getBalance() - price);
        cout << endl;
        shop.displayBill();
        return shop.getBill();
    }

    // If the user can't afford it, tell them and prompt them for input again
    while (wagon.getBalance() < price)
    {
        cout << "You do not have enough money to purchase this many yokes. Please try again" << endl;
        cout << "How many yokes do you wish to purchase?: ";
        yokes = wagon.askForNumInput();
        price = yokes * shop.getOxenPrice();
    }

    // If the user won't have between 3 and 5 yokes, tell them and ask for input again
    while ((wagon.getOxen() / 2) + yokes < 3 || (wagon.getOxen() / 2) + yokes > 5)
    { 
        cout << "You cannot buy this many oxen. Please try again" << endl;
        cout << "You currently have " << wagon.getOxen() / 2 << " yokes." << endl;
        cout << "Remember: You can only purchase 3 to 5 yokes, total." << endl;
        cout << "How many yokes do you wish to purchase?: ";
        yokes = wagon.askForNumInput();
        price = yokes * shop.getOxenPrice();
    }

    // Set variables accordingly and display the bill
    wagon.setOxen(yokes * 2 + wagon.getOxen());
    shop.setBill(shop.getBill() + price);
    wagon.setBalance(wagon.getBalance() - price);
    cout << endl;
    shop.displayBill();
    return shop.getBill();
}

/*
* This function asks a user for a number of wagon parts and sets the player's wagon parts, bill, and balance accordingly
* Parameters: none
* Return: the user's bill (int)
*/
int OT::buyWagonParts()
{
    double price;
    int wagonParts;

    // Tell the user wagon parts info and prompt them for input
    cout << "A wagon part (wheels, axels, tongues) costs $" << shop.getWagonPartPrice() << "." << endl;
    cout << "If the wagon breaks along the way, any wagon parts will be used to fix it." << endl;
    cout << "How many wagon parts do you wish to purchase?: ";

    wagonParts = wagon.askForNumInput();

    // Calculate the price
    price = wagonParts * shop.getWagonPartPrice();

    // If the user can afford it
    if (wagon.getBalance() >= price)
    { 
        // Set variables accordingly and display the bill
        wagon.setWagonParts(wagonParts + wagon.getWagonParts());
        shop.setBill(shop.getBill() + price);
        wagon.setBalance(wagon.getBalance() - price);
        cout << endl;
        shop.displayBill();
        return shop.getBill();
    }

    // If the user can't afford it
    while (wagon.getBalance() < price)
    {
        // Tell the user and prompt them for input again
        cout << "You do not have enough money to purchase this many wagon parts. Please try again" << endl;
        cout << "How many wagon parts do you wish to purchase?: ";
        wagonParts = wagon.askForNumInput();
        price = wagonParts * shop.getWagonPartPrice();
    }

    // Set variables accordingly and display the bill
    wagon.setWagonParts(wagonParts + wagon.getWagonParts());
    shop.setBill(shop.getBill() + price);
    wagon.setBalance(wagon.getBalance() - price);
    cout << endl;
    shop.displayBill();
    return shop.getBill();
}

/*
* This function asks a user for a number of med kits and sets the player's med kits, bill, and balance accordingly
* Parameters: none
* Return: the user's bill (int)
*/
int OT::buyMeds()
{
    double price;
    int medKits;

    // Tell the user med kit info and prompt the user for input
    cout << "A medical aid kit costs $" << shop.getMedPrice() << "." << endl;
    cout << "If anyone gets sick or hurt during the journey, a med kit can be used to help them." << endl;
    cout << "How many medical aid kits do you wish to purchase?: ";

    medKits = wagon.askForNumInput();

    // Calculate the price
    price = medKits * shop.getMedPrice();

    // If the user can afford it
    if (wagon.getBalance() >= price)
    {
        // Set variables accordingly and display the bill
        wagon.setMedKit(medKits + wagon.getMedKit());
        shop.setBill(shop.getBill() + price);
        wagon.setBalance(wagon.getBalance() - price);
        cout << endl;
        shop.displayBill();
        return shop.getBill();;
    }

    // If the user can't afford it
    while (wagon.getBalance() < price)
    {
        // Tell the user and ask for input again
        cout << "You do not have enough money to purchase this many med kits. Please try again" << endl;
        cout << "How many medical aid kits do you wish to purchase?: ";
        medKits = wagon.askForNumInput();
        price = medKits * shop.getMedPrice();
    }

    // Set variables accordingly and display the bill
    wagon.setMedKit(medKits + wagon.getMedKit());
    shop.setBill(shop.getBill() + price);
    wagon.setBalance(wagon.getBalance() - price);
    cout << endl;
    shop.displayBill();
    return shop.getBill();;
}


Wagon OT::getWagon()
{
    return wagon;
}

void OT::setWagon(Wagon w)
{
    wagon = w;
}


void OT::setTurnMiles(int m)
{
    turnMiles = m;
}

int OT::getTurnMiles()
{
    return turnMiles;
}

void OT::setMilestones(vector <Milestone> m)
{
    milestones = m;
}

vector <Milestone> OT::getMilestones()
{
    return milestones;
}

int OT::getMilestoneIndex() const
{
    return milestoneIndex;
}

int OT::getMilesToMilestone() const
{
    return milesToMilestone;
}

void OT::setMilestoneIndex(int i)
{
    milestoneIndex = i;
}

void OT::setMilesToMilestone(int m)
{
    milesToMilestone = m;
}

Date OT::getDate()
{
    return date;
}

void OT::setDate(Date d)
{
    date = d;
}


/*
* This function lets the wagon members rest for a random (1 - 3) number of days. Food and days are updated accordingly
* Parameters: none
* Return: nothing (void)
*/
void OT::Rest()
{
    int miles = 0;
    // Get a random number 1 to 3 - this will be how many days we rest for
    srand(time(NULL));
    int randomNum = rand() % (3 - 1 + 1) + 1;
    // Tell the user how many days they will rest for
    cout << "You have chosen to rest for " << randomNum << " days. Your food will be updated accordingly." << endl;
    date.daysIncrement(randomNum);
    // Subtract 3 pounds of food per person per day
    wagon.setFood(wagon.getFood() - (3 * wagon.getNumFamilyMembers() * randomNum));
}

/*
* This function lets the wagon members rest for exactly 3 days, updating days and food accordingly
* Parameters: none
* Return: nothing (void)
*/
void OT::sickRest()
{
    int miles = 0;
    cout << "You have chosen to rest for " << 3 << " days. Your food will be updated accordingly." << endl;
    // Increment days by 3
    date.daysIncrement(3);
    // Subract 3 pounds of food per person per day
    wagon.setFood(wagon.getFood() - (3 * wagon.getNumFamilyMembers() * 3));
}

/*
* This function lets the wagon members rest for 2 weeks, moving a random number of miles and updating food and days accordingly
* Parameters: none
* Return: nothing (void)
*/
void OT::Continue()
{

    int miles = 0;
    cout << "You have chosen to travel for 2 weeks. Your food will be updated accordingly." << endl;
    // Increment the days by 14 (2 weeks)
    date.daysIncrement(14);
    // Subract 3 pounds of food per person per day
    wagon.setFood(wagon.getFood() - (3 * wagon.getNumFamilyMembers() * 14));
    // Get a random number of miles traveled
    miles = wagon.getRandomMilesTraveled();
    turnMiles = miles;
    // Tell the user how many miles they will travel
    cout << "You will travel " << miles << " miles." << endl;
    // Increment miles traveled by this many miles
    wagon.setMilesTraveled(wagon.getMilesTraveled() + miles);

}

/*
* This function lets the player hunt for random animals. If they pass a puzzle, their food storage will go up.
* Parameters: none
* Return: nothing (void)
*/
void OT::Hunt()
{

    string inputString;
    int foodAcquired = 0;
    // Increment the days by 1
    date.daysIncrement(1);

    // Get a random number 1 to 2
    srand(time(NULL));
    int randomNum = rand() % (2 - 1 + 1) + 1;

    // If the number is 1 (50%)
    if (randomNum == 1)
    {
        // The user encounters a Rabbit! Ask them if they'd like to hunt
        cout << "You have encountered a Rabbit! Would you like to hunt for it?: (Y/N)";
        inputString = wagon.askForInputChar();

        // If the user says yes
        if (inputString == "Y" || inputString == "y")
        {  
            // If the user doesn't have at least 10 bullets
            if (wagon.getBullets() < 10)
            {
                // They can't hunt
                cout << "Sorry, you need at least 10 bullets to successfully hunt." << endl;
                cout << "Right now, you only have " << wagon.getBullets() << " bullets." << endl;
            }
            // Otherwise, if they have enough bullets, display a puzzle to them
            // If they win the puzzle,
            else if (Puzzle() == 1)
            {
                // The user gets 5 pounds of food
                foodAcquired += 5;
                // Lose 10 bullets
                wagon.setBullets(wagon.getBullets() - 10);
                cout << "You gained 5 pounds of food." << endl;
                cout << "You used 10 bullets." << endl;
            }
        }
    }

    // Get a random number 1 to 4
    randomNum = rand() % (4 - 1 + 1) + 1;
    // If the number is 1 (25%)
    if (randomNum == 1)
    {
        // The user finds a Fox! Ask them if they'd like to hunt for it
        cout << "You have encountered a Fox! Would you like to hunt for it?: (Y/N)";
        inputString = wagon.askForInputChar();

        // If the user says yes
        if (inputString == "Y" || inputString == "y")
        {  
            // If the user doesn't have at least 10 bullets
            if (wagon.getBullets() < 10)
            {
                // They can't hunt
                cout << "Sorry, you need at least 10 bullets to successfully hunt." << endl;
                cout << "Right now, you only have " << wagon.getBullets() << " bullets." << endl;
            }
            // Otherwise, if the user has enough bullets, make them solve a puzzle
            // If the user solves the puzzle,
            else if (Puzzle() == 1)
            {
                // The user gets 10 pounds of food
                foodAcquired += 10;
                // User loses 8 bullets
                wagon.setBullets(wagon.getBullets() - 8);
                cout << "You gained 10 pounds of food." << endl;
                cout << "You used 8 bullets." << endl;
            }
        }
    }

    // Get a random number 1 to 20
    randomNum = rand() % (20 - 1 + 1) + 1;
    // If the number is a 1,2,3 (15%)
    if (randomNum == 1 || randomNum == 2 || randomNum == 3)
    {
        // We found a deer! Ask the user if they'd like to hunt for it
        cout << "You have encountered a Deer! Would you like to hunt for it?: (Y/N)";
        inputString = wagon.askForInputChar();

        // If the user says yes
        if (inputString == "Y" || inputString == "y")
        {  
            // If they don't have at least 10 bullets
            if (wagon.getBullets() < 10)
            {
                // They can't hunt
                cout << "Sorry, you need at least 10 bullets to successfully hunt." << endl;
                cout << "Right now, you only have " << wagon.getBullets() << " bullets." << endl;
            }
            // If the user has enough bullets, make them solve a puzzle
            // If the user wins the puzzle
            else if (Puzzle() == 1)
            {
                // The user gets 60 pounds of food
                foodAcquired += 60;
                // Loses 5 bullets
                wagon.setBullets(wagon.getBullets() - 5);
                cout << "You gained 60 pounds of food." << endl;
                cout << "You used 5 bullets." << endl;
            }
        }

    }

    // Get a random number 1 to 100
    randomNum = rand() % (100 - 1 + 1) + 1;
    // If the number is 1,2,3,4,5,6,7 (7%)
    if (randomNum == 1 || randomNum == 2 || randomNum == 3 || randomNum == 4 || randomNum == 5 || randomNum == 6 || randomNum == 7)
    {
        // We found a Bear! Ask the user if they'd like to hunt for it
        cout << "You have encountered a Bear! Would you like to hunt for it?: (Y/N)";
        inputString = wagon.askForInputChar();

        // If the user says yes
        if (inputString == "Y" || inputString == "y")
        {  
            // If the user doesn't have at least 10 bullets
            if (wagon.getBullets() < 10)
            {
                // The user can't hunt
                cout << "Sorry, you need at least 10 bullets to successfully hunt." << endl;
                cout << "Right now, you only have " << wagon.getBullets() << " bullets." << endl;
            }
            // If the user has enough bullets, make them solve a puzzle
            // If the user solves the puzzle
            else if (Puzzle() == 1)
            {
                // They get 200 pounds of food
                foodAcquired += 200;
                // Lose 10 bullets
                wagon.setBullets(wagon.getBullets() - 10);
                cout << "You gained 200 pounds of food." << endl;
                cout << "You used 10 bullets." << endl;
            }
        }
    }

    // Get a random number 1-20
    randomNum = rand() % (20 - 1 + 1) + 1;
    // If the number is 7 (5%)
    if (randomNum == 7)
    {
        // We found a Moose! Ask the user if they'd like to hunt for it
        cout << "You have encountered a Moose! Would you like to hunt for it?: (Y/N)";
        inputString = wagon.askForInputChar();

        // If the user says yes
        if (inputString == "Y" || inputString == "y")
        {  
            // If the user doesn't have at least 10 bullets
            if (wagon.getBullets() < 10)
            {
                // They can't hunt
                cout << "Sorry, you need at least 10 bullets to successfully hunt." << endl;
                cout << "Right now, you only have " << wagon.getBullets() << " bullets." << endl;
            }
            // If the user has enough bullets, make them solve a puzzle
            // If they solve the puzzle,
            else if (Puzzle() == 1)
            {
                // They get 500 pounds of food
                foodAcquired += 500;
                // Lose 12 bullets
                wagon.setBullets(wagon.getBullets() - 12);;
                cout << "You gained 500 pounds of food." << endl;
                cout << "You used 12 bullets." << endl;
            }
        }
    }

    // At the end of the hunt, ask the user how well they want to eat
    cout << "How well do you want to eat?" << endl;
    cout << "1. Poorly" << endl;
    cout << "2. Moderately" << endl;
    cout << "3. Well" << endl;
    int option = wagon.askForNumInput();
    switch(option)
    {
        // Poorly
        case 1:
        // Lose 2 pounds of food per person
            wagon.setFood(wagon.getFood() - (2 * wagon.getNumFamilyMembers()));
            break;
        // Moderately
        case 2:
            // Lose 3 pounds of food per person
            wagon.setFood(wagon.getFood() - (3 * wagon.getNumFamilyMembers()));
            break;
        // Well
        case 3:
            // Lose 5 pounds of food per person
            wagon.setFood(wagon.getFood() - (5 * wagon.getNumFamilyMembers()));
            break;
    }
    // If, at the end of the hunt, the user has acquired enough food that would push their food over 1000 pounds
    if (wagon.getFood() + foodAcquired > 1000)
    {
        // Calculate how much they'll lose
        int lost = wagon.getFood() + foodAcquired - 1000;
        // Substract this amount from their food storage
        wagon.setFood(wagon.getFood() + foodAcquired - lost);
        // Tell the user they had to leave some food behind
        cout << "You had to leave some food behind, as your wagon can only hold 1000 pounds." << endl;
    }
}


/*
* This function gets a random number 1 to 10 and gives the user 3 tries to guess it correctly 
* Parameters: none
* Return: -1 (if they fail the puzzle),  1 (if they win the puzzle)
*/
int OT::Puzzle()
{
    srand(time(NULL));
    int guess1;
    int guess2;
    int guess3;
    // Get a random number 1 to 10
    int randomNum = rand() % (10 - 1 + 1) + 1;
    // Welcome the user to the puzzle
    cout << "----------WELCOME TO THE PUZZLE!----------" << endl;
    cout << "To solve this puzzle, you must correctly guess a number 1-10" << endl;
    cout << "You will be given three tries." << endl;

    // Ask the user for their first guess
    cout << "Guess #1: ";
    guess1 = wagon.askForNumInput();

    // If they guess it right, they won!
    if (guess1 == randomNum)
    {
        cout << "CORRECT! YOU WIN!" << endl;
        return 1;
    }
    // If they don't, give them another try
    else
    {
        // Ask the user for their second guess
        cout << "INCORRECT. TRY AGAIN." << endl;
        cout << "Guess #2: ";
        guess2 = wagon.askForNumInput(); 
        // If they guess it right, they won!
        if (guess2 == randomNum)
        {
            cout << "CORRECT! YOU WIN!" << endl;
            return 1;
        }   
        // If they don't, give them another try
        else
        {
            // Ask the user for their third and final guess
            cout << "INCORRECT. TRY AGAIN." << endl;
            cout << "Guess #3: ";
            guess3 = wagon.askForNumInput(); 
            // If the user gets it right, they win!
            if (guess3 == randomNum)
            {  
                cout << "CORRECT! YOU WIN!" << endl;
                return 1;
            }   
            // If they don't, they've failed the puzzle
            else
            {
                cout << "YOU HAVE FAILED THE PUZZLE" << endl;
                return -1;
            }
        }
    }
}


/*
* This function stops the user at a milestone and allows them to Rest/Continue or Rest/Shop/Continue.
* Parameters: none
* Return: -1 (if the game is over),  1 (if the game should continue)
*/
int OT::Stop()
{
    // Tell the user that they've stopped at a milestone
    int input;
    cout << "You were prepared to travel " << turnMiles << " but you stopped at the " << endl;
    cout << milestones[milestoneIndex].getName() << ". What would you like to do?" << endl;

    // If we are at a river crossing or landmark
    if (milestones[milestoneIndex].getType() == "River Crossing" || milestones[milestoneIndex].getType() == "Landmark")
    {
        // Present the user with options
        cout << "1. Rest" << endl;
        cout << "2. Continue" << endl;
        input = wagon.askForNumInput();

        // While the user hasn't pressed continue
        while (input != 2)
        {
            switch (input)
            {
                // If the user presses rest
                case 1:
                    // Call the Rest() function
                    Rest();
                    // If our food is negative, make it zero and end the game
                    if (wagon.getFood() <= 0)
                    {
                        wagon.setFood(0);
                        cout << "YOU ARE OUT OF FOOD" << endl;
                        return -1;
                    }
                    // Display status
                    // Increment the milestone index (so when we display status if they rest, it'll show the next milestone)
                    milestoneIndex++;
                    displayStatusUpdate();
                    // Decrement the milestone index back to normal
                    milestoneIndex--;
                    // End the game if there's a game over (-1)
                    if (checkGameOver() == -1)
                    {
                        return -1;
                    }
                    break;
            }
            // Display options again, this time within the loop
            cout << "What would you like to do?" << endl;
            cout << "1. Rest" << endl;
            cout << "2. Continue" << endl;
            input = wagon.askForNumInput();
        }
        // When the user presses 2, Continue
        Continue();
        // If the our food is negative, make it zero and end the game
        if (wagon.getFood() < 0)
        {
            wagon.setFood(0);
            cout << "YOU ARE OUT OF FOOD" << endl;
            return -1;
        }
        // Increment the milestone index so our new milestone is the next one
        milestoneIndex++;
        if (calculateMilesToMilestone() == -1)
        {
            return -1;
        }
        // Decrease it back to normal after calculation
        milestoneIndex--;
    }

    // If the milestone is a fort
    else if (milestones[milestoneIndex].getType() == "Fort")
    {
        // Increase the shop's prices by 25%
        shop.setBulletsPrice(shop.getBulletsPrice() + (shop.getBulletsPrice() * 0.25));
        shop.setWagonPartPrice(shop.getWagonPartPrice() + (shop.getWagonPartPrice() * 0.25));
        shop.setMedPrice(shop.getMedPrice() + (shop.getMedPrice() * 0.25));
        shop.setOxenPrice(shop.getOxenPrice() + (shop.getOxenPrice() * 0.25));
        shop.setFoodPrice(shop.getFoodPrice() + (shop.getFoodPrice() * 0.25));


        int input = 0;

        // Present the user with options and ask for input
        cout << "1. Rest" << endl;
        cout << "2. Visit the Shop" << endl;
        cout << "3. Continue" << endl;
        input = wagon.askForNumInput();
        // Do the following until the user presses Continue
        while (input != 3)
        {
            switch (input)
            {
                // User presses Rest
                case 1:
                    // Rest
                    Rest();
                    // If the food is negative, set it to zero and end the game
                    if (wagon.getFood() <= 0)
                    {
                        wagon.setFood(0);
                        cout << "YOU ARE OUT OF FOOD" << endl;
                        return -1;
                    }
                    // Display status
                    // Incrementt the milestone index (so when we display status if they rest, it'll show the next milestone)
                    milestoneIndex++;
                    displayStatusUpdate();
                    milestoneIndex--;
                    // Decrement the milestone index back to normal
                    // End the game if there's a game over (-1)
                    if (checkGameOver() == -1)
                    {
                        return -1;
                    }
                    break;
                // User presses Visit the Shop
                case 2:
                    // Set the bill to zero
                    shop.setBill(0);
                    // Display the shop to the user
                    displayShop();
                    break;
            }
            // Display the menu again, this time within the loop
            cout << "What would you like to do?" << endl;
            cout << "1. Rest" << endl;
            cout << "2. Visit the Shop" << endl;
            cout << "3. Continue" << endl;
            input = wagon.askForNumInput();
        }
        // When the user presses 3, continue
        Continue();
        // If the food is negative, set it to zero
        if (wagon.getFood() <= 0)
        {
            wagon.setFood(0);
            cout << "YOU ARE OUT OF FOOD" << endl;
            return -1;
        }
        // Increment the milestone index so we're calculating with the next milestone in mind
        milestoneIndex++;
        if (calculateMilesToMilestone() == -1)
        {
            return -1;
        }
        // Decrement it back to normal
        milestoneIndex--;
    }
    return 1;
}


/*
* This function checks to see if the game is over, and returns -1 on a game over condition
* Parameters: none
* Return: -1 (if the game is over),  1 (if the game should continue)
*/
int OT::checkGameOver()
{
    // If the user is out of food
    if (wagon.getFood() <= 0)
    {
        // Tell the user, return -1 (game over)
        cout << "YOU ARE OUT OF FOOD." << endl;
        return -1;
    }
    // If the user is out of oxen
    if (wagon.getOxen() <= 0)
    {
        // Tell the user, return -1 (game over)
        cout << "YOU ARE OUT OF OXEN." << endl;
        return -1;
    }
    // If the main player is dead
    if (wagon.getPlayer1().getIsDead())
    {
        // Tell the user, return -1 (game over)
        cout << "YOU DIED." << endl;
        return -1;
    }
    // If it's December
    if (date.getMonth() > 11)
    {
        // Tell the user they didn't reach oregon city in time, return -1 (game over)
        cout << "YOU DID NOT REACH OREGON CITY IN TIME." << endl;
        return -1;
    }
    // If the user reached Oregon City
    if (wagon.getMilesTraveled() >= 2040)
    {
        // If the user technically passed Oregon City, set their miles to 2040 (at oregon city)
        if (wagon.getMilesTraveled() > 2040)
        {
            wagon.setMilesTraveled(2040);
        }
        // Tell the user and end the game! :D
        cout << "CONGRATULATIONS! YOU REACHED OREGON CITY! YOU WIN!!!" << endl;
        return -1;
    }
    

    return 1;
}

/*
* This function takes a string, splits it at every occurrence of a delimiter, and then
populates an array of strings with the split pieces, up to the provided maximum number of pieces.
* Parameters: splitString - string we are splitting up, separator - delimeter we break the string at,
arr[] - array we are filling with split pieces, size - size of the array (maximum number of pieces)
* Return: the number of pieces the string was split into, as an integer.
*/
int OT::split(string splitString, char separator, string arr[], int size)
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
* This function reads a list of milestones and puts the information into a vector of Milestone objects.
* Parameters: none
* Return: nothing (void)
*/
void OT::readMilestones()
{
    string line = "";
    ifstream myFile;
    string mileType;
    string arr[3];
    int lineCount = 0;

    // Open "milestones.txt"
    myFile.open("milestones.txt");

    // If the file can't be opened, tell the user we encountered a error
    if (!myFile.is_open())
    {
        cout << "A FATAL ERROR OCCURRED." << endl;
    }
    // If the file opened successfully
    else
    {
        // Make a milestone object
        string milesString;
        Milestone newMilestone;
        // Read every line of the file
        while(getline(myFile,line))
        {
            // If the line isn't empty
            if (line.length() != 0)
            {
                // Increment our line count
                lineCount++;
                // If we are on an even line
                if (lineCount % 2 != 0)
                {
                    // We have a name line
                    newMilestone.setName(line);
                    // Go through the entire line
                    for (int i = 0; i < line.length(); i++)
                    {
                        // Split it by a space and put it into an array of strings
                        split(line, ' ', arr, 3);
                        // Go through the array
                        for (int i = 0; i < 3; i++)
                        {
                            // If any of the words are "Crossing"
                            if (arr[i] == "Crossing")
                            {
                                // We have a river crossing milestone
                                newMilestone.setType("River Crossing");
                            }
                            // If any of the words are "Fort"
                            else if (arr[i] == "Fort")
                            {
                                // We have a fort milestone
                                newMilestone.setType("Fort");
                            }
                            // If any of the words are "Rock", "Pass", "Springs", or "Mountains"
                            else if (arr[i] == "Rock" || arr[i] == "Pass" || arr[i] == "Springs" || arr[i] == "Mountains")
                            {
                                // We have a landmark milestone
                                newMilestone.setType("Landmark");
                            }
                        }
                    }
                }
                // If we are on an odd line
                if (lineCount % 2 == 0)
                {
                    // We have a miles line
                    milesString = "";
                    // Go through the line
                    for(int i = 0; i < line.length(); i++)
                    {
                        // If the character is a digit
                        if (isdigit(line[i]))
                        {
                            // Add it to the miles string
                            milesString += line[i];
                        }
                    }
                    // We should now have the number of miles as a string
                    // Convert it to an integer and set it as the milestone's miles
                    newMilestone.setMiles(stoi(milesString));
                    // Put the milestone object into our vector of milestones
                    milestones.push_back(newMilestone);
                }
            }
        }
    }
    return;
}

/*
* This function calculates the miles to the next milestone. If the user is at a milestone, it calls the Stop() function
* and moves onto the next milestone afterward.
* Parameters: none
* Return: -1 (if the game is over),  1 (if the game should continue)
*/
int OT::calculateMilesToMilestone()
{

    // Set our miles to milestone as the next milestone's position - our many miles we've traveled
    milesToMilestone = milestones[milestoneIndex].getMiles() - wagon.getMilesTraveled();

    // If we are at that milestone
    if (milesToMilestone <= 0)
    {
        // Stop at the milestone
        wagon.setMilesTraveled(milestones[milestoneIndex].getMiles());
        // Set our miles to milestone as the next milestone's position minus how many miles we've traveled
        milesToMilestone = milestones[milestoneIndex + 1].getMiles() - wagon.getMilesTraveled();
        // Call the Stop() function
        // If we get a game over from this, end the game (-1)
        if (Stop() == -1)
        {
            return -1;
        }
       // Go on to the next milestone 
       milestoneIndex++;
    }
    return 1;
}


/*
* This function displays options to Rest, Continue, Hunt, or Quit to the user and checks to see if we get
* a game over.
* Parameters: none
* Return: 1 (if the game should continue),  -1 (if the game is over)
*/
int OT::takeTurn()
{
    // Ask the user what they'd like to do and take input
    int menuInput;
    cout << "What would you like to do?" << endl;
    cout << "1. Rest" << endl;
    cout << "2. Continue" << endl;
    cout << "3. Hunt" << endl;
    cout << "4. Quit" << endl;
    menuInput = wagon.askForNumInput();
    cout << endl;

    switch (menuInput)
    {
        // User chooses Rest
        case 1:
            // Rest
            Rest();
            // If the user is out of food, end the game
            if (wagon.getFood() <= 0)
            {
                wagon.setFood(0);
                cout << "YOU ARE OUT OF FOOD" << endl;
                return -1;
            }
            // Display the status update
            displayStatusUpdate();
            // Call our misfortune functions to see if a misfortune happens
            // If we get a game over from any of these, end the game
            if (rollOxenDeath() == -1 || checkGameOver() == -1 || rollBreakage() == -1 || rollSick() == -1)
            {
                return -1;
            }
            break;
        // User chooses Continue
        case 2:
            // Continue
            Continue();
            // If the user is out of food, end the game
            if (wagon.getFood() <= 0)
            {
                wagon.setFood(0);
                cout << "YOU ARE OUT OF FOOD" << endl;
                return -1;
            }
            // Calculate the miles to the next milestone, see if we need to stop early, etc.
            if (calculateMilesToMilestone() == -1)
            {
                return -1;
            }
            // Display the status update
            displayStatusUpdate();
            // Call our misfortune functions to see if a misfortune happens
            // If we get a game over from any of these, end the game
            if (rollOxenDeath() == -1 || checkGameOver() == -1 || rollBreakage() == -1 || rollSick() == -1)
            {
                return -1;
            }
            break;
        // User chooses Hunt
        case 3:
            // Hunt
            Hunt();
            // If the player is out of food, end the game
            if (wagon.getFood() <= 0)
            {
                wagon.setFood(0);
                cout << "YOU ARE OUT OF FOOD" << endl;
                return -1;
            }
            // Display the status update
            displayStatusUpdate();
            // Call our misfortune functions to see if a misfortune happens
            // If we get a game over from any of these, end the game
            if (rollOxenDeath() == -1 || checkGameOver() == -1 || rollBreakage() == -1 || rollSick() == -1)
            {
                return -1;
            }
            break;
        // User chooses Quit
        case 4:
            // End the game  
            cout << "YOU HAVE CUT YOUR JOURNEY SHORT. THANK YOU FOR PLAYING!" << endl;
            return -1;
    }

    return 1;
}


/*
* This function displays the current date, miles traveled, miles to next milestone, name of the next milestone,
* remaining food, bullets, wagon parts, oxen, cash, and living family members to the user.
* Parameters: none
* Return: nothing (void)
*/
void OT::displayStatusUpdate()
{
    // Display the current date, miles traveled, miles to next milestone, the name of the next milestone,
    // remaining food, bullets, wagon parts, oxen, cash, and living family members to the user
    cout << "--------------STATUS UPDATE--------------" << endl;
    date.displayDate();
    cout << endl;
    cout << "Miles Traveled: " << wagon.getMilesTraveled() << endl;
    cout << "Miles to Next Milestone: " << milesToMilestone << endl;
    cout << "Next Milestone: " << milestones[milestoneIndex].getName() << endl;
    cout << "Food: " << wagon.getFood() << " lbs" << endl;
    cout << "Bullets: " << wagon.getBullets() << endl;
    cout << "Wagon Parts: " << wagon.getWagonParts() << endl;
    cout << "Oxen: " << wagon.getOxen() << endl;
    cout << "Cash: $" << wagon.getBalance() << endl;
    cout << "Wagon Members: ";
    
    // Display the wagon member's name if they are alive
    if (!wagon.getPlayer1().getIsDead())
    {
        cout << wagon.getPlayer1().getUsername() << " ";
    }
    if (!wagon.getFamilyMember1().getIsDead())
    {
        cout << wagon.getFamilyMember1().getUsername() << " ";
    }
    if (!wagon.getFamilyMember2().getIsDead())
    {
        cout << wagon.getFamilyMember2().getUsername() << " ";
    }
    if (!wagon.getFamilyMember3().getIsDead())
    {
        cout << wagon.getFamilyMember3().getUsername() << " ";
    }
    if (!wagon.getFamilyMember4().getIsDead())
    {
        cout << wagon.getFamilyMember4().getUsername() << " ";
    }

    cout << endl;
    cout << endl;

   

}


/*
* This function uses random numbers to determine if a person in the wagon gets sick, and makes appropriate 
* variable changes if they die.
* Parameters: none
* Return: -1 (if the main player dies - game over),  1 (if the main player doesn't die)
*/
int OT::rollSick()
{
    // Get a random number from 1 to 6
    string illness;
    srand(time(NULL));
    int randomIllness = rand() % (6 - 1 + 1) + 1;

    // Using this number, get a random illness
    switch(randomIllness)
    {
        case 1:
            illness = "TYPHOID";
            break;
        case 2:
            illness = "CHOLERA";
            break;
        case 3:
            illness = "DIARRHEA";
            break;
        case 4:
            illness = "MEASLES";
            break;
        case 5:
            illness = "DYSENTERY";
            break;
        case 6:
            illness = "FEVER";
            break;
    }

    // Get another random number from 1 to 5
    int randomNum = rand() % (5 - 1 + 1) + 1;
    // If the number is 3 or 4 (40%), a player is sick
    if (randomNum == 3 || randomNum == 4)
    {
        // Get a random number from 1 to 5
        int randomPlayer = rand() % (5 - 1 + 1) + 1;
        // This number will determine which person is sick
        switch (randomPlayer)
        {
            // Main player is sick
            case 1:
                // If they're not already dead, tell the user they are sick
                if (!wagon.getPlayer1().getIsDead())
                {
                    // Tell the user what illness they have
                    cout << "OH NO! YOU HAVE " << illness << "!" << endl;
                    // Call the sick function to determine if they recover or die
                    int returnVal = Sick(wagon.getPlayer1());
                    // If we get a game over, end the game
                    if (returnVal == 0)
                    {
                        return -1;
                    }
                    // If the player dies
                    if(returnVal == -1)
                    {
                        // Set the player to dead
                        Player temp;
                        temp.setUsername(wagon.getPlayer1().getUsername());
                        temp.setIsDead(true);
                        wagon.setPlayer1(temp);
                        // Decrease the number of people in the wagon
                        wagon.setNumFamilyMembers(wagon.getNumFamilyMembers() - 1);
                        // Return -1 (the main player is dead, game over)
                        return -1;
                    }
                }
                break;
            // Family member #1 is sick
            case 2:
                // If they're not dead already, tell the player they're sick
                if (!wagon.getFamilyMember1().getIsDead())
                {
                    // Tell the user what disease they have
                    cout << "OH NO! " << wagon.getFamilyMember1().getUsername() << " HAS " << illness << "!" << endl;
                    // Call the sick function to determine if they recover or die
                    int returnVal = Sick(wagon.getFamilyMember1());
                    // If we get a game over from this, end the game
                    if (returnVal == 0)
                    {
                        return -1;
                    }
                    // If the person dies,
                    if(returnVal == -1)
                    {
                        // Set the person to dead
                        Player temp;
                        temp.setUsername(wagon.getFamilyMember1().getUsername());
                        temp.setIsDead(true);
                        wagon.setFamilyMember1(temp);
                        // Decrease the number of people in the wagon
                        wagon.setNumFamilyMembers(wagon.getNumFamilyMembers() - 1);
                        // Return 1 (main player did not die - not a game over)
                        return 1;
                    }
                }
                break;
            // Family member #2 is sick
            case 3:
                // If the person is not already dead, tell the user they're sick
                if (!wagon.getFamilyMember2().getIsDead())
                {
                    // Tell the user what disease they have
                    cout << "OH NO! " << wagon.getFamilyMember2().getUsername() << " HAS " << illness << "!" << endl;
                    // Call the sick function to determine if they recover or die
                    int returnVal = Sick(wagon.getFamilyMember2());
                    // If we get a game over from this,
                    if (returnVal == 0)
                    {
                        return -1;
                    }
                    // If the person dies,
                    if(returnVal == -1)
                    {
                        // Set the person to dead
                        Player temp;
                        temp.setUsername(wagon.getFamilyMember2().getUsername());
                        temp.setIsDead(true);
                        wagon.setFamilyMember2(temp);
                        // Decrease the number of people in the wagon
                        wagon.setNumFamilyMembers(wagon.getNumFamilyMembers() - 1);
                        // Return 1 (the main player did not die - not a game over)
                        return 1;
                    }
                }
                break;
            // Family member #3 is sick
            case 4:
                // If the person is not dead already, tell the user they're sick
                if (!wagon.getFamilyMember3().getIsDead())
                {
                    // Tell the user what disease they have
                    cout << "OH NO! " << wagon.getFamilyMember3().getUsername() << " HAS " << illness << "!" << endl;
                    // Call the sick function to determine if they recover or die
                    int returnVal = Sick(wagon.getFamilyMember3());
                    // If we get a game over from this,
                    if (returnVal == 0)
                    {
                        return -1;
                    }
                    // If the person dies
                    if(returnVal == -1)
                    {
                        // If they die, set them to dead
                        Player temp;
                        temp.setUsername(wagon.getFamilyMember3().getUsername());
                        temp.setIsDead(true);
                        wagon.setFamilyMember3(temp);
                        // Decrease the number of people in the wagon
                        wagon.setNumFamilyMembers(wagon.getNumFamilyMembers() - 1);
                        // Return 1 (main player did not die - not a game over)
                        return 1;
                    }
                }
                break;
            // Family member #4 is sick
            case 5:
                // If the person is not already dead
                if (!wagon.getFamilyMember4().getIsDead())
                {
                    // Tell the user they're sick and what disease they have
                    cout << "OH NO! " << wagon.getFamilyMember4().getUsername() << " HAS " << illness << "!" << endl;
                    // Call the sick function to determine if they recover or die
                    // If they die,
                    int returnVal = Sick(wagon.getFamilyMember4());
                    // If we get a game over from this,
                    if (returnVal == 0)
                    {
                        return -1;
                    }
                    // If the person dies
                    if(returnVal == -1)
                    {
                        // Set the person to dead
                        Player temp;
                        temp.setUsername(wagon.getFamilyMember4().getUsername());
                        temp.setIsDead(true);
                        wagon.setFamilyMember4(temp);
                        // Decrease the number of people in the wagon
                        wagon.setNumFamilyMembers(wagon.getNumFamilyMembers() - 1);
                        // Return 1 (the main player did not die - not a game over)
                        return 1;
                    }
                }
                break;
        }

    }
    return 1;
}

/*
* This function takes a Player who is sick and determines if they die or recover based on the Player's med 
* kits and user input.
* Parameters: p - Player who is sick
* Return: 1 (if the person recovered),  -1 (if the person died), 0 (if the game is over)
*/
int OT::Sick(Player p)
{
    int randomNum;
    // If the player has a med kit to spare
    if(wagon.getMedKit() > 0)
    {
        // Use a medkit (get rid of one)
        wagon.setMedKit(wagon.getMedKit() -1 );

        // Get a random number from 1 to 2
        randomNum = rand() % (2 - 1 + 1) + 1;

        // If the number is 2, that person died
        if (randomNum == 2)
        {
            // The person is dead!
            // If it's the main player, call them "you"
            if (p.getUsername() == wagon.getPlayer1().getUsername())
            {
                cout << "YOU HAVE DIED." << endl;
            }
            // If it's not the main player, tell the user who died
            else
            {
                cout << p.getUsername() << " IS DEAD!" << endl;
            }
            return -1;
        }
        // Otherwise, if the person survived, tell the user they used a medkit and recovered
        else
        {
            // If it's the main player, call them "you"
            if (p.getUsername() == wagon.getPlayer1().getUsername())
            {
                cout << "YOU USED A MED KIT!" << endl;
                cout << "YOU RECOVERED!" << endl;
            }
            // If it's not the main player, tell the user who recovered
            else
            {
                cout << p.getUsername() << " USED A MED KIT!" << endl;
                cout << p.getUsername() << " RECOVERED!" << endl; 
            }
            return 1;
        }
    }
    // If the user doesn't have any med kits to spare
    else
    {
        int menuInput;
        // If it's the main player, call them "you"
        if (p.getUsername() == wagon.getPlayer1().getUsername())
        {
            cout << "You are sick, but you don't have any med kits. What would you like to do?" << endl;
        }
        // If it's not the main player, tell them who is sick and that they don't have any med kits
        else
        {
            cout << p.getUsername() << " is sick, but you don't have any med kits. What would you like to do?" << endl;
        }

        // Ask the user if they'd like to "Rest" or "Press On!"
        cout << "1. Rest" << endl;
        cout << "2. Press On!" << endl;
        menuInput = wagon.askForNumInput();
        switch(menuInput)
        {
            // User chooses Rest
            case 1:
                // Rest (special case - increments days by 3 days every time)
                sickRest();
                if (wagon.getFood() <= 0)
                {
                    wagon.setFood(0);
                    cout << "YOU ARE OUT OF FOOD" << endl;
                    return 0;
                }
                displayStatusUpdate();
                if (rollOxenDeath() == -1 || checkGameOver() == -1 || rollBreakage() == -1 || rollSick() == -1)
                {
                    return 0;
                }

                // Get a random number from 1 to 10
                randomNum = rand() % (10 - 1 + 1) + 1;

                // If the number is 1,2,3 (30% chance)
                if (randomNum == 1 || randomNum == 2 || randomNum == 3)
                {
                    // The person dies
                    p.setIsDead(true);
                    // If it's the main player, call them "you"
                    if (p.getUsername() == wagon.getPlayer1().getUsername())
                    {
                        cout << "YOU HAVE DIED." << endl;
                    }
                    // If it's not the main player, tell the user who died
                    else
                    {
                        cout << p.getUsername() << " IS DEAD!" << endl;
                    }
                    return -1;
                }
                // Otherwise, if the person recovered after resting
                else
                {
                    // If it's the main player, call them "you"
                    if (p.getUsername() == wagon.getPlayer1().getUsername())
                    {
                        cout << "YOU RECOVERED!" << endl;
                    }
                    // If it's not the main player, tell the user who recovered
                    else
                    {
                        cout << p.getUsername() << " RECOVERED!" << endl;
                    }
                    return 1;
                }
                break;

            // User chooses to Press On
            case 2:
                // Tell the user they've chosen to press on
                cout << "You have chosen to press on." << endl;
                // Call the Continue() function
                Continue();
                if (wagon.getFood() <= 0)
                {
                    wagon.setFood(0);
                    cout << "YOU ARE OUT OF FOOD" << endl;
                    return 0;
                }
                if (calculateMilesToMilestone() == -1)
                {
                    return 0;
                }
                displayStatusUpdate();
                if (rollOxenDeath() == -1 || checkGameOver() == -1 || rollBreakage() == -1 || rollSick() == -1)
                {
                    return 0;
                }
                // Get a random number from 1 to 10
                randomNum = rand() % (10 - 1 + 1) + 1;
                
                // If the number is 1,2,3 (30% chance), they recovered
                if (randomNum == 1 || randomNum == 2 || randomNum == 3)
                {
                    // If it's the main player, call them "you"
                    if (p.getUsername() == wagon.getPlayer1().getUsername())
                    {
                        cout << "YOU RECOVERED!" << endl;
                    }
                    // If it's not the main player, tell the user who recovered
                    else
                    {
                        cout << p.getUsername() << " RECOVERED!" << endl;
                    }
                    return 1;
                }
                // Otherwise (70% chance), they died
                else
                {
                    // The player dies
                    // If it's the main player, call them "you"
                    if (p.getUsername() == wagon.getPlayer1().getUsername())
                    {
                        cout << "YOU HAVE DIED." << endl;
                    }
                    // If it's not the main player, tell the user who died
                    else
                    {
                        cout << p.getUsername() << " IS DEAD!" << endl;
                    }
                    return -1; 
                }
                break;
        }
    }
    return 1;
}

/*
* This function determines if an oxen dies, and ends the game if the user runs out of oxen.
* Parameters: none
* Return 1 (if the game should continue),  -1 (if the game is over - out of oxen)
*/
int OT::rollOxenDeath()
{
   // Get a random number from 1 to 5
    srand(time(NULL));
    int randomNum = rand() % (5 - 1 + 1) + 1;
    // If the number is a 3 or 4 (40%)
    if (randomNum == 3 || randomNum == 4)
    {
        // An oxen dies
        // Decrease the number of oxen by 1
        wagon.setOxen(wagon.getOxen() -1);
        cout << "OH NO! ONE OF THE OXEN HAS DIED! YOU HAVE " << wagon.getOxen() << " LEFT." << endl;
    }
    // If the user is out of oxen
    if (wagon.getOxen() <= 0)
    {
        // Tell the user they can't go any further and end the game
        cout << "YOU ARE OUT OF OXEN. YOU CANNOT GO ANY FURTHER." << endl;
        // Return -1 (game over)
        return -1;
    }
    // Otherwise, if all is well,
    else
    {
        // Return 1 (the game should continue)
        return 1;
    }
}

/*
* This function determines if a wagon wheel breaks during a turn and uses a wagon part to fix it
* if there are wagon parts available.
* Parameters: none
* Return: 1 (if the game should continue),  -1 (if the game is over - cannot fix the wheel)
*/
int OT::rollBreakage()
{
    // Get a random number from 1 to 5
    srand(time(NULL));
    int randomNum = rand() % (5 - 1 + 1) + 1;
    // If the number is a 1 or a 2 (40%)
    if (randomNum == 1 || randomNum == 2)
    {
        // One of the wheels breaks
        cout << "OH NO! ONE OF YOUR WHEELS IS BROKEN!" << endl;
        // If the user has a wagon part to spare
        if(wagon.getWagonParts() > 0)
        {
            // Use one of the wagon parts
            wagon.setWagonParts(wagon.getWagonParts() - 1);
            // Tell the player how many wagon parts they have left
            cout << "YOU HAVE " << wagon.getWagonParts() << " WAGON PARTS REMAINING." << endl;
            // Return 1 (not a game over)
            return 1;
        }
        // Otherwise, if the player has no more wagon parts left
        else
        {
            // Tell the user they can't fix the wheel, and can't go any further
            cout << "ONE OF YOUR WHEELS IS BROKEN AND YOU HAVE NO WAGON PARTS TO FIX IT." << endl;
            cout << "YOU CANNOT GO ANY FURTHER." << endl;
            // Return -1 (game over)
            return -1;
        }
        
    }
    return 1;
}


/*
* This function outputs the user's final stats and writes them to the file "results.txt"
* Parameters: none
* Return: nothing (void)
*/
void OT::gameOver()
{
    // Open a file "results.txt"
    string line = "";
    ofstream myFile;
    myFile.open("results.txt");

    // Output to the user the leader name, miles traveled, food remaining, and cash remaining
    cout << "Leader name: " << wagon.getPlayer1().getUsername() << endl;
    cout << "Miles Traveled: " << wagon.getMilesTraveled() << endl;
    cout << "Food Remaining: " << wagon.getFood() << " lbs" << endl;
    cout << "Cash Remaining: $" << wagon.getBalance() << endl;

    // Write these stats to the file "results.txt"
    myFile << "Leader name: " << wagon.getPlayer1().getUsername() << endl;
    myFile << "Miles Traveled: " << wagon.getMilesTraveled() << endl;
    myFile << "Food Remaining: " << wagon.getFood() << " lbs" << endl;
    myFile << "Cash Remaining: $" << wagon.getBalance() << endl;

}




//*******UNUSED**************
void OT::rollRaiders(int milesTraveled)
{
    /*
    - Using our milesTraveled, calculate the probability and see if we encounter raiders
    - If we encounter raiders, announce it to the user
    - Present the user with the option to RUN, ATTACK, SURRENDER
    */
}

//*******UNUSED**************
void OT::Run()
{
    /*
    - The user chooses to run
    - Get rid of 1 ox, 10 food and 1 wagon part
    - If the user is out of ox or food, end the game (gameOver())
    */
   cout << "YOU NARROWLY ESCAPED THE RAIDERS, BUT YOU LOST 1 OX, 10 POUNDS OF FOOD, AND 1 WAGON PART." << endl;
   wagon.setOxen(wagon.getOxen() - 1);
   wagon.setFood(wagon.getFood() - 10);
   wagon.setWagonParts(wagon.getWagonParts() - 1);
}

//*******UNUSED**************
void OT::Attack()
{
   if (Puzzle() == 1)
   {
       if (wagon.getFood() + 50 > 1000)
       {
           int lost = wagon.getFood() + 50 - 1000;
           wagon.setFood(wagon.getFood() + 50 - lost);
       }
       else
       {
           wagon.setFood(wagon.getFood() + 50);
       }
   }
   else
   {
       wagon.setBalance(wagon.getBalance() - (wagon.getBalance() * 0.25));
       wagon.setBullets(wagon.getBullets() - 50);
   }
}

//*******UNUSED**************
void OT::Surrender()
{
    /*
    - The user chooses to surrender
    - Lose balance * 1/4
    */
   cout << "YOU SURRENDERED, BUT THE RAIDERS TOOK A QUARTER OF YOUR MONEY." << endl;
   wagon.setBalance(wagon.getBalance() - (wagon.getBalance() * (0.25)));
   cout << "YOU HAVE $" << wagon.getBalance() << " REMAINING." << endl;
}
