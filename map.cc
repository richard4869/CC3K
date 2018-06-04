#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "map.h"
#include "game.h"
#include "pc.h"
#include "monster.h"

// constructor with the name of the file given. If the name is "" then choose a map from map bank.
Map::Map(std::string name){
    action = "";
    std::ifstream file(name.c_str());
    int i = 0;
    display = new char*[25];
    std::string s;
    char c;
    if(name.substr(0,7) == "mapbank"){  // Do not read the first map if the map is from the map bank.
            getline(file,s);
    }
    while(i < 25 && getline(file,s)){
        display[i]= new char[79];
        std::istringstream iss(s);
		int j = 0;
        while((c = iss.get()), iss){  // read the floor char one by one and set the special characters as floor tile.
            if((c <= '5' && c >= '1') || (c >= 'A' && c <= 'Z') || c == '@' || c == '\\') c = '.';
            display[i][j] = c;
            j++;
        }
        i++;
    }
}
// destructor. Deep delete the display.
Map::~Map(){
    int i = 0;
    for(i = 0; i < 25; i++){
        delete[] display[i];
    }
    delete[] display;
}

// Consume the game's pointer. Display char one by one in the line by line method.
// When display a char, check if it is pc, floor stair, monsters ,potions and golds, and display it if true.
// Otherwise print the char at that position in the floor map. Then print the 5 lines of PC situation and the
// sentences notified by the action.
void Map::print(Game* game){
    Floor * f = game->getfloor();
    PC * p = game->getpc();
    int px = p->getx();
    int py = p->gety();
    int fx = f->getx();
    int fy = f->gety();
    for(int i = 0; i < 25; i++){
        for(int j = 0; j < 79; j++){
            char m = display[i][j];
            if(i == px && j == py){
                std::cout << '@';
            } else if(i == fx && j == fy){
                std::cout << '\\';
            } else if (m == '-' || m == '|' || m == '#' || m == '+'){
                std::cout << m;
            } else if(game->extra[i][j] >= '0' && game->extra[i][j] <= '9'){
                switch(game->extra[i][j]){
                    case '0' :
                    case '1' :
                    case '2' :
                    case '3' :
                    case '4' :
                    case '5' :
                        std::cout << 'P';
                        break;
                    case '6' :
                    case '7' :
                    case '8' :
                    case '9' :
                        std::cout << 'G';
                        break;
                    default:
                        break;
                }
            } else if(game->extra[i][j] != ' '){
                std::cout << game->extra[i][j];
            } else {
                std::cout << m;
            }
        }
        std::cout << std::endl;
    }
        std::string race;
        if(p->gettype() == 'd'){
            race = "Drow";
        } else if(p->gettype() == 'v'){
            race = "Vampire";
        } else if(p->gettype() == 't'){
            race = "Troll";
        } else if(p->gettype() == 'g'){
            race = "Goblin";
        #ifdef DLC
        } else if(p->gettype() == 'r'){
            race = "Robot";
        #endif // ROBOT
        } else {
            race = "Shade";
        }
        int fl = game->getlevel() + 1;
        if(fl >5) fl = 5;
        std::cout << "Race: " << race << " Gold: " << p->getgold() << "                                               Floor " << fl << std::endl;
        std::cout << "HP: " << p->getHP() <<   std::endl;
        std::cout << "Atk: " << p->getATT() <<   std::endl;
        std::cout << "Def: " << p->getDEF() <<   std::endl;
        std::cout << "Action: " << action << std::endl;
        action = "";
}

// Append the string to the action string.
void Map::notify(std::string s){
    action = action + s;
}
