
#include "Player.h"
#include "Room.h"
#include "Enemy.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<map>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;


//This method setup system
void Player::systemReady(string filename)
{
    
    //Reading Json file 
	ifstream fin(filename);
	json j; // object that represents the json data
	fin >> j; // read from file into j

    cout<<endl;
	
    //Stroing details of all rooms;
    int numRooms = j["rooms"].size();
    //cout <<"Number of rooms:"<<numRooms << endl;
    
    for(int i = 0;i < numRooms;i++)
    {
        string desc = j["rooms"][i]["desc"].get<string>();
        string north = j["rooms"][i]["n"].get<string>();
        string south = j["rooms"][i]["s"].get<string>();
        string east = j["rooms"][i]["e"].get<string>();
        string west = j["rooms"][i]["w"].get<string>();
        vector<string> v = j["rooms"][i]["obj"].get<vector<string>>();
        
        Room *room = new Room(desc,north,east,west,south,v);
        string id = j["rooms"][i]["id"].get<string>();
        this->room_parameters[id] = room;
    }
    
    
    //Enemy
    int numEnemies = j["enemies"].size();
    
    for(int i = 0;i < numEnemies;i++)
    {
       string enemy_name = j["enemies"][i]["id"].get<string>(); 
       vector<string> weapons = j["enemies"][i]["killedby"].get<vector<string>>();
       
       Enemy * enemy = new Enemy(enemy_name,weapons);
       string id = j["enemies"][i]["initialroom"].get<string>();
       this->enemy_parameters[id] = enemy;  
       this->killed[enemy_name] = false;
    }
    
    //Initialize game
    this->initialroom = j["player"]["initialroom"].get<string>();
    this->currentroom = j["player"]["initialroom"].get<string>();
    
    //Game Started
    cout<<endl<<"***************************************Game Starts********************************************\n\n"<<endl;
    
    //Displaying Contents of first room
    vector<string> v{"look"};
    bool b = this->gamePlay(v);
}

//Checking whether all enemies are killed
bool Player::isAllKilled()
{
    for(auto it = killed.begin();it != killed.end();++it)
    {
        if(it->second == false)
        {
            return false;
        }
    }
    return true;
}


//Playing Game 
bool Player::gamePlay(vector<string> commands)
{
    bool end = false;
    int size_commands = commands.size();
    if(commands.at(0) == "end" || commands.at(0) == "quit" || commands.at(0) == "exit")
    {
            cout<<"Game has terminated"<<endl;
            end = true;
            return end;
    }
    else if(commands.at(0) == "look")
    {
        cout<<this->room_parameters.at(currentroom)->desc_()<<endl;
    }
    else if(size_commands == 2)
    {
	//For moving to direction specified by player.
        if(commands.at(0) == "move" || commands.at(0) == "go")
        {
	    //If the player moving to other room without killing enemy,then enemy attacks him.
            if(this->enemy_parameters.count(currentroom) != 0 && killed.at(this->enemy_parameters.at(currentroom)->enemyName()) != true )
            {
                cout<< this->enemy_parameters.at(currentroom)->enemyName()<<" Killed YOU "<<endl;
                end = true;
                return end;
          
            }
            else
            {
		//If their is room in that direction, description of room is displayed.
                if(this->direction(commands.at(1)) == true)
                {
                    cout<<this->room_parameters.at(currentroom)->desc_()<<endl;  
                }
            }
        }
	//taking objects in the room
        else if(commands.at(0) == "take" || commands.at(0) == "get")
        {
            vector<string> objects_room = this->room_parameters.at(currentroom)->objects_();
            if ((std::find(objects_room.begin(), objects_room.end(),commands.at(1) ) != objects_room.end()) && (std::find(availableweapons.begin(), availableweapons.end(),commands.at(1) ) == availableweapons.end()))
            {
                availableweapons.push_back(commands.at(1));
            }
            else
            {
                cout<<"No such Objects found"<<endl;
            }
        }
        
        else if(commands.at(0) == "kill")
        {
	    //Checks whether their are enemies with in room
            if(this->enemy_parameters.count(currentroom) != 0)
            {
                if(commands.at(1) == this->enemy_parameters.at(currentroom)->enemyName() && killed.at(this->enemy_parameters.at(currentroom)->enemyName()) != true)
                {
                    int count = 0; // for counting weapons player has so far for killing enemy
                    int weapon_size = this->enemy_parameters.at(currentroom)-> weapons_size(); //Number of weapons needed to kill enemy
                    vector<string> weapons_needed = this->enemy_parameters.at(currentroom)->weapons_(); // objects need to kill
     
                    for(auto weapon:availableweapons)
                    {
                        for(auto sofarobjects: weapons_needed)
                        {
                            if(weapon == sofarobjects)
                            {
                                count += 1;
                            }
                        }
    
                    }
                    //if the count is not equal actual weapons required to kill, then enemy kills player
                    if(count == weapon_size)
                    {
                        killed[this->enemy_parameters.at(currentroom)->enemyName()] = true;
			//if all enemies are killed then player own the game if not just present enemy will be killed
                        if(this->isAllKilled() == true)
                        {
                            cout<<"YOU HAVE WON THE GAME"<<endl;
                            end = true;
                        }
                        else
                        {
                            cout<<"Enemy in room is KILLED"<<endl;
                        }
                    }
                    else
                    {
                        cout<<"Power to kill enemy was limited"<<endl;
                        cout<<" ---------------**************GAME ENDED *********************-------------------"<<endl;
                        end = true;
                    }
                }
                else if(killed.at(this->enemy_parameters.at(currentroom)->enemyName()) == true)
                {
                    cout<<"No enemy left to kill"<<endl;
                }
                else
                {
                    cout<<"No enemy with that Name: "<<commands.at(1)<<" Instead,You have to kill: "<<this->enemy_parameters.at(currentroom)->enemyName()<<endl;
                }
            }
            else
            {
                cout<<"No Enemy in this room"<<endl;
            }
        
        }
        else
        {
            cout<<"Sorry, the command is inappropriate"<<endl;
        }
    
            
    }   
    else
    {
        cout<<"Sorry, the command is inappropriate"<<endl;
    }
    return end;
}



//returns true if their is a room in that direction
bool Player::direction(string direct)
{
    if(direct == "north")
    {
        if(!this->room_parameters.at(currentroom)->north_().empty())
        {
            this->currentroom = this->room_parameters.at(currentroom)->north_();
            return true;
        }
        else
        {
            cout<<"No room exists in the dirction of  "<<direct<<endl;
        }
    }
    else if(direct == "south")
    {
        if(!this->room_parameters.at(currentroom)->south_().empty())
        {
            this->currentroom = this->room_parameters.at(currentroom)->south_();
            return true;
        }
        else
        {
            cout<<"No room exists in the dirction of  "<<direct<<endl;
        }
    }
    else if(direct == "east")
    {
        if(!this->room_parameters.at(currentroom)->east_().empty())
        {
            this->currentroom = this->room_parameters.at(currentroom)->east_();
            return true;
        }
        else
        {
            cout<<"No room exists in the dirction of  "<<direct<<endl;
        }
    }
    else if(direct == "west")
    {
        if(!this->room_parameters.at(currentroom)->west_().empty())
        {
            this->currentroom = this->room_parameters.at(currentroom)->west_();
            return true;
        }
        else
        {
            cout<<"No room exists in the dirction of  "<<direct<<endl;
        }
    }
    else 
    {   
        cout<<"Sorry, Try another command"<<endl;  
    }
    return false;
    
}

