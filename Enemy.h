#ifndef ENEMY_H_
#define ENEMY_H_

#include<vector>
#include<string>

using namespace std;

class Enemy
{
    protected:
        string enemy_name; //name of the enemy
        vector<string>  weapons; //vector with weapons.
    public:
	//Constructor
        Enemy()
        {
            
        }
	
	//Constructor with parameters enemy name and weapons used to kill it.
        Enemy(string enemy_name,vector<string>  weapons);
        
        
        //Getter for returning name of enemy.
        string enemyName();
        
        //Getter for returning name of weapons. 
        vector<string> weapons_();
        
        //Returning number of weapons used for killing enemy.
        int weapons_size();
        
};

#endif