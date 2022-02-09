
#include "Player.h"
#include<iostream>
#include <fstream>
#include<vector>
#include<string>

using namespace std;



//Function for parsing input into two words at max.
//Main objective of this function is if user types "go south", imputParsing returns vector with "go" and "south"
vector<string>  inputParsing(string str)
{
    string str_word = "";
    vector<string> words;
    bool flag_value = false;
    for (short i = 0; i < str.length(); i++)
    {
        if (str[i] != ' ')
            str_word += tolower(str[i]);
        else
        {
            if(flag_value == false)
            {
                words.push_back(str_word);
                str_word = "";
                flag_value = true;
            }
            else
               str_word += tolower(str[i]); 
        }   
    }
    words.push_back(str_word);
    return words;
}


int main(int argc, char** argv)
{
   
    //name of the file i.e. map1.json or map2.json or map3.json
    string filename = argv[1];
    
    cout<<"\n Please wait few till system to start"<<endl;
    Player p(filename);
    
    //Details of the system
    //p.printDetails();
      
    
    //Playing game
    bool end = false; //This end variable will is used to know end of the game.
    string playerInput;

    //Loop breaks in following conditions
    //1.If player terminates game
    //2.player is being killed by enemy
    //3.If player won the game
    while (end == false) 
    {
        cout<<">";
	getline(cin, playerInput);
        vector<string> s = inputParsing(playerInput);
        end = p.gamePlay(s);
        
    }
    
    return 0;

}