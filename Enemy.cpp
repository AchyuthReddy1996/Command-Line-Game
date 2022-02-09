
#include "Enemy.h"
#include<iostream>
#include<vector>
#include<string>

using namespace std;


Enemy::Enemy(string enemy_name,vector<string>  weapons)
{
    this->enemy_name = enemy_name;
    this->weapons = weapons;
}
        
        
string Enemy::enemyName()
{
    return this->enemy_name;
}
        
vector<string> Enemy::weapons_()
{
    return this->weapons;
}
        
int Enemy::weapons_size()
{
    return this->weapons.size();
}