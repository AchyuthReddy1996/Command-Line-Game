#include "Room.h"

#include<iostream>
#include<string>
#include<vector>


using namespace std;

Room::Room(string desc,string north,string east,string west,string south,vector<string> objects)
{
    this->desc = desc;
    this->north = north;
    this->east = east;
    this->south = south;
    this->west = west;
    this->objects = objects;
}

string Room::desc_()
{
    return this->desc;
}
        
 string Room::north_()
{
    return this->north;
}
        
string Room::east_()
{
    return this->east;
}
        
string Room::west_()
{
    return this->west;
}
        
string Room::south_()
{
    return this->south;
}
        
 vector<string> Room::objects_()
{
    return this->objects;
}

