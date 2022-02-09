#ifndef ROOM_H_
#define ROOM_H_

#include<vector>
#include<string>

using namespace std;

class Room
{
    protected:
        string desc;
        string north;
        string south;
        string east;
        string west;
        vector<string>  objects;
    public:
	//constructor
        Room()
        {
            
        }
	
	//Constructor
        Room(string desc,string north,string east,string west,string south,vector<string> objects);
        
        //Getters 
        string desc_();
        string north_();
        string east_(); 
        string west_();
        string south_(); 
        vector<string> objects_();
        
};
#endif
