#ifndef PLAYER_H_
#define PLAYER_H_

#include "Room.h"
#include "Enemy.h"
#include<vector>
#include<string>
#include<map>

using namespace std;


class Player:public Room,public Enemy
{
    protected:
        map<string,Room* > room_parameters; //room name as key and details as parameter
        map<string,Enemy* > enemy_parameters; // Initialization room as key and details of enemy as parameters;
        map<string,bool> killed;//Incase of multiple enemies we have to check everyone is killed so as to win;
        string initialroom;
        string currentroom;
        vector<string> availableweapons;
    
    private:
        void systemReady(string filename);
        bool direction(string direct);
        bool isAllKilled();
        
    public:
        Player(string filename)
        {
            this->systemReady(filename);
        }
        
        bool gamePlay(vector<string> commands);
};

#endif