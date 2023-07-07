// Author: Tristan English
// Recitation: 225 – Connor Thompson
// Project 3

#include <string>
#ifndef PLAYER_H
#define PLAYER_H

using namespace std;


class Player
{
    public:
        Player();
        Player(string u, bool b);
        string getUsername() const;
        void setUsername(string u);
        bool getIsDead();
        void setIsDead(bool b);
    private:
        string username;
        bool isDead;

};
#endif
