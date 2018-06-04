#include "controller.h"
#include <iostream>
#include "cell.h"
#include "map.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>

using namespace std;
// constructor a new controller with nothing.
Controller::Controller(){
    game = NULL;
    themap = NULL;
    ifend = 0;
}
// destructor.
Controller::~Controller(){
}
// notify the sentences to the map-print.
void Controller::notify(string s){
    themap->notify(s);
}
// set a game with the given filename. If the filename is empty, then randomly choose a map from map bank and set the game.
void Controller::setgame(string s){
srand (time(NULL));
    string cmd;
    bool pc_init = false;
    string name;
    game = new Game(this);
    if(s != "" && s.substr(0,7) != "mapbank"){ // choosing the race and load the file.
            #if defined (DLC)
        cout << "Please select a race of your character in: Shade, Drow, Vampire, Goblin, Troll and Robot.(s, d, v, g, t, r) " << endl;
        while(!pc_init && cin >> cmd){
            if (cmd == "s" || cmd == "d" || cmd == "v" || cmd == "g" || cmd == "t"||cmd =="r"){
            #else
        cout << "Please select a race of your character in: Shade, Drow, Vampire, Goblin and Troll.(s, d, v, g, t) " << endl;
        while(!pc_init && cin >> cmd){
            if (cmd == "s" || cmd == "d" || cmd == "v" || cmd == "g" || cmd == "t"){
            #endif // ROBOT
                stringstream sss;
                char r;
                sss << cmd;
                sss >> r;
                game->filename = s;
                themap = new Map(s);
                game->setpc(r);
                game->load(s);
                pc_init = true;
            } else {
            cout << "Invalid race. Try again." << endl;
            #ifdef ROBOT
            cout << "Please select a race of your character in: Shade, Drow, Vampire, Goblin, Troll and Robot.(s, d, v, g, t, r) " << endl;
            #else
            cout << "Please select a race of your character in: Shade, Drow, Vampire, Goblin and Troll.(s, d, v, g, t) " << endl;
            #endif // ROBOT
    }
        }
    } else {
        #ifdef DLC
        cout << "Please select a race of your character in: Shade, Drow, Vampire, Goblin, Troll and Robot.(s, d, v, g, t, r) " << endl;
        #else
        cout << "Please select a race of your character in: Shade, Drow, Vampire, Goblin and Troll.(s, d, v, g, t) " << endl;
        #endif // ROBOT
        while(!pc_init && cin >> cmd){  // choosing the race and choose the map from the map bank.
            int i = rand() % 5 + 1;
            stringstream ss;
            ss << i;
            string str = ss.str();
            name = "mapbank" + str + ".txt";
        #ifdef DLC
        if (cmd == "s" || cmd == "d" || cmd == "v" || cmd == "g" || cmd == "t" || cmd == "r"){
        #else
        if (cmd == "s" || cmd == "d" || cmd == "v" || cmd == "g" || cmd == "t"){
        #endif // ROBOT
                stringstream sss;
                char r;
                sss << cmd;
                sss >> r;
                game->filename = name;
                themap = new Map(name);
                game->setpc(r);
                game->initfloor(name);
                pc_init = true;
            } else {
            cout << "Invalid race. Try again." << endl;
            #ifdef ROBOT
            cout << "Please select a race of your character in: Shade, Drow, Vampire, Goblin, Troll and Robot.(s, d, v, g, t, r) " << endl;
            #else
            cout << "Please select a race of your character in: Shade, Drow, Vampire, Goblin and Troll.(s, d, v, g, t) " << endl;
            #endif // ROBOT
            }
        }
    }
}
// play the game with given filename and controller the game with input command.
void Controller::play(string s){
    setgame(s);
    string cmd;
    notify("PC has been spawned.");// spawn the pc and print the initial floor.
    themap->print(game);
    while(cin >> cmd){
        if(cmd == "u"){
            string dir;
            if(cin >> dir && (dir == "no" ||dir == "so" ||dir == "ne" ||dir == "we" ||dir == "nw" ||dir == "sw" ||dir == "se" ||dir == "ea" )){
                game->usepotion(dir);
                if(checkwin()) break; // check if the game is end by pc taking PH potion.
                game->monster_turn();
                if(checkwin()) break;// check if the game is end by being attacked.
                themap->print(game);
            } else {
                cout << "Invalid input. Try again." << endl;
                cmd = "";
            }
        } else if(cmd == "a"){
            string dir;
            if(cin >> dir && (dir == "no" ||dir == "so" ||dir == "ne" ||dir == "we" ||dir == "nw" ||dir == "sw" ||dir == "se" ||dir == "ea")){
                game->pcattack(dir);
                if(checkwin()) break;// check if the game is end by special effects.
                game->monster_turn();
                if(checkwin()) break;// check if the game is end by being attacked.
                themap->print(game);
            } else {
                cout << "Invalid input. Try again." << endl;
                cmd = "";
            }
        } else if(cmd == "no" ||cmd == "so" ||cmd == "ne" ||cmd == "we" ||cmd == "nw" ||cmd == "sw" ||cmd == "se" ||cmd == "ea" ){
            int f = game->getlevel(); // record the floor level before pc moved.
            game->movepc(cmd);
            if(checkwin()) break;
            int nf = game->getlevel();
            if(nf == f){               // compare the floor level before and after the pc moving.
                game->monster_turn(); //  If different then go downstairs has been called, and call monster_turn othersiwe.
            } else {
                string s = "";
                switch(nf){
                case 1:
                    s = "second";
                    break;
                case 2:
                    s = "third";
                    break;
                case 3:
                    s = "fourth";
                    break;
                case 4:
                    s = "fifth";
                    break;
                }
                s = "PC has reached the " + s + " floor. ";
                notify(s);
            }
                themap->print(game);
            if(checkwin()) break;// check if the pc reached the sixth floor.
        } else if(cmd == "r"){ // restart the game.
            delete game;
            delete themap;
            ifend = 0;
			play(s);
			break;
        } else if(cmd == "q"){ // quit and end the game immediately.
            int i = game->getscore();
            cout<<"you lose. Score "<<i<<endl; // print the score the player got.
            delete game;
            delete themap;
            break;
        } else {
            cout << "Unknown command. Try again." << endl;
            cmd = "";
        }
    }
}
// check if the game is end.
bool Controller::checkwin(){
    if(ifend == 1){
    int i = game->getscore();
        lose(i);
        return true;
    } else if(ifend == 2){
        int i = game->getscore();
        win(i);
        return true;
    } else {
        return false;
    }
}
// Called when game is end and the player loses.
void Controller::lose(int i){
    themap->print(game);
    cout<<"you lose. Score "<<i<<endl;
    cout<<"Quit or restart(q, r)" <<endl;
    char cmd;
    while(cin >> cmd){
    if(cmd == 'q') { // quit the game.
        cout << "Quiting the game." << endl;
        delete game;
        delete themap;
        break;
    } else if(cmd == 'r') { // restart the game.
        cout << "Restarting the game." << endl;
        string s = game->filename;
        delete game;
        delete themap;
        ifend = 0;
        play(s);
        break;
    } else {
        cout << "Invalid input. Try again." << endl;
        cout<<"Quit or restart(q, r)" <<endl;
    }
    }
}
// Called when game is end and the player wins.
void Controller::win(int i){
    themap->print(game);
    cout<<"you win. Score "<<i<<endl;
    cout<<"Quit or restart(q, r)" <<endl;
    char cmd;
    while(cin >> cmd){
    if(cmd == 'q') {
        cout << "Quiting the game." << endl;
        delete game;
        delete themap;
    } else if(cmd == 'r') {
        cout << "Restarting the game." << endl;
        string s = game->filename;
        delete game;
        delete themap;
        ifend = 0;
        play(s);
    } else {
        cout << "Invalid input. Try again." << endl;
        cout<<"Quit or restart(q, r)" <<endl;
    }
    }
}
