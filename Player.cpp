// Author: Tristan English
// Recitation: 225 – Connor Thompson
// Project 3

#include "Player.h"

// Default constructor
Player::Player()
{
    username = "Player1";
    isDead = false;
}

// Parameterized constructor
Player::Player(string u, bool b)
{
    username = u;
    isDead = b;
}

string Player::getUsername() const
{
    return username;
}

void Player::setUsername(string u)
{
    username = u;
}

bool Player::getIsDead()
{
    return isDead;
}
void Player::setIsDead(bool b)
{
    isDead = b;
}
