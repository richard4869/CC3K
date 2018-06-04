#include "floor.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
// constructor with empty floor and the stair's position.
Floor::Floor(){
    chambers = NULL;
    cell = NULL;
    x = 0;
    y = 0;
}
// load the floor from a given filename. Set the floor map into cells.
void Floor::initload(std::string name){
    std::ifstream file(name.c_str());
    int i = 0;
    cell = new Cell*[25];
    std::string s;
    std::stringstream is(s);
    char c;
    while(i < 25 && getline(file,s)){
        cell[i]= new Cell[79];
        std::istringstream iss(s);
		int j = 0;
        while((c = iss.get()), iss){
            if(c == ' '){
                j++;
            } else if(c == '-' || c == '|' || c == '#' || c == '+') {
                cell[i][j].init(i,j,c);
                j++;
            } else {
                cell[i][j].init(i,j,'.'); // Everything that are not wall , door and passage are tiles.
                j++;
            }
        }
        i++;
    }
}
// initial a new floor with random generation.
void Floor::initnew(std::string name){
    std::ifstream file(name.c_str());
    int i = 0;
    int n;
    chambers = new Chamber*[5];
    cell = new Cell*[25];
    std::string s;
    getline(file,s);
    std::stringstream is(s);
    for(int k = 0; k < 5; k++){ // load the first line of the file in the map bank to set the capacity of each chambers.
        is >> n;
        chambers[k] = new Chamber(n);
    }
    char c;
    while(getline(file,s)){
        cell[i]= new Cell[79];
        std::istringstream iss(s);
		int j = 0;
        while((c = iss.get()), iss){
            if(c == ' '){
                j++;
            } else if(c == '-' || c == '|' || c == '#' || c == '+') {
                cell[i][j].init(i,j,c);
                j++;
            } else if(c >= '1' && c <= '5'){ // load and set the cells of tails into its chamber.
                cell[i][j].init(i,j,'.');
                int index = c - '1';
                int length = chambers[index]->length;
                chambers[index]->cell[length] = &(cell[i][j]);
                chambers[index]->length++;
                j++;
            }
        }
        i++;
    }
}
// destructor. Deep delete the cells and the chambers.
Floor::~Floor(){
int i=0;
while (i<25){
    delete [] cell[i];
    i++;
}
delete []cell;
if(chambers != NULL){
for(int i = 0; i < 5; i++){
    delete chambers[i];
}
delete []chambers;
}}

// return an array with length 8 of positions as 2 int array referring to adjacent tiles of the position given.
int** Floor::getadj(int i, int j){
    int ** adj = new int*[8];
    int index = 0;
    for(int a = 0; a < 8; a++){
        adj[a] = NULL;
    }

    if((i + 1 >= 0 && i + 1 <= 25 && j >= 0 && j <= 79) &&(cell[i+1][j].gettype() == '.')){
        adj[index] = new int[2];
        adj[index][0] = i + 1;
        adj[index++][1] = j;
    }
    if((i + 1 >= 0 && i + 1 <= 25 && j - 1 >= 0 && j - 1 <= 79) &&(cell[i+1][j-1].gettype() == '.')){
       adj[index] = new int[2];
        adj[index][0] = i + 1;
        adj[index++][1] = j - 1;
    }
    if((i + 1 >= 0 && i + 1 <= 25 && j + 1 >= 0 && j + 1 <= 79) &&(cell[i+1][j+1].gettype() == '.')){
       adj[index] = new int[2];
        adj[index][0] = i + 1;
        adj[index++][1] = j + 1;
    }
    if((i - 1 >= 0 && i - 1 <= 25 && j + 1 >= 0 && j + 1 <= 79) &&(cell[i-1][j+1].gettype() == '.')){
        adj[index] = new int[2];
        adj[index][0] = i - 1;
        adj[index++][1] = j + 1;
    }
    if((i - 1 >= 0 && i - 1 <= 25 && j - 1 >= 0 && j - 1 <= 79) &&(cell[i-1][j-1].gettype() == '.')){
        adj[index] = new int[2];
        adj[index][0] = i - 1;
        adj[index++][1] = j - 1;
    }
    if((i - 1 >= 0 && i - 1 <= 25 && j >= 0 && j <= 79) &&(cell[i-1][j].gettype() == '.')){
        adj[index] = new int[2];
        adj[index][0] = i - 1;
        adj[index++][1] = j;
    }
    if((i >= 0 && i <= 25 && j - 1 >= 0 && j - 1 <= 79) &&(cell[i][j-1].gettype() == '.')){
        adj[index] = new int[2];
        adj[index][0] = i;
        adj[index++][1] = j - 1;
    }
    if((i>= 0 && i<= 25 && j + 1 >= 0 && j + 1 <= 79) &&(cell[i][j+1].gettype() == '.')){
        adj[index] = new int[2];
        adj[index][0] = i;
        adj[index++][1] = j + 1;
    }
    return adj;
}
// return an array of 2 int to a position. If the cell in the given direction is occupied then return the original position.
int* Floor::getcell(int x, int y, std::string s){
    int * next = new int[2];
    next[0] = x;
    next[1] = y;
    if(s == "no"){
        if(cell[x - 1][y].gettype() == '.' || cell[x - 1][y].gettype() == '+' || cell[x - 1][y].gettype() == '#'){
            next[0] = x - 1;
            next[1] = y;
        }
    } else if (s == "so"){
        if(cell[x + 1][y].gettype() == '.' || cell[x + 1][y].gettype() == '+' || cell[x + 1][y].gettype() == '#'){
            next[0] = x + 1;
            next[1] = y;
        }
    } else if (s == "ea"){
        if(cell[x][y + 1].gettype() == '.' || cell[x][y + 1].gettype() == '+' || cell[x][y + 1].gettype() == '#'){
            next[0] = x;
            next[1] = y + 1;
        }
    } else if (s == "we"){
        if(cell[x][y - 1].gettype() == '.' || cell[x][y - 1].gettype() == '+' || cell[x][y - 1].gettype() == '#'){
            next[0] = x;
            next[1] = y - 1;
        }
    } else if (s == "ne"){
        if(cell[x - 1][y + 1].gettype() == '.' || cell[x - 1][y + 1].gettype() == '+' || cell[x - 1][y + 1].gettype() == '#'){
            next[0] = x - 1;
            next[1] = y + 1;
        }
    } else if (s == "nw"){
        if(cell[x - 1][y - 1].gettype() == '.' || cell[x - 1][y - 1].gettype() == '+' || cell[x - 1][y - 1].gettype() == '#'){
            next[0] = x - 1;
            next[1] = y - 1;
        }
    } else if (s == "se"){
        if(cell[x + 1][y + 1].gettype() == '.' || cell[x + 1][y + 1].gettype() == '+' || cell[x + 1][y + 1].gettype() == '#'){
            next[0] = x + 1;
            next[1] = y + 1;
        }
    } else if (s == "sw"){
        if(cell[x + 1][y - 1].gettype() == '.' || cell[x + 1][y - 1].gettype() == '+' || cell[x + 1][y - 1].gettype() == '#'){
            next[0] = x + 1;
            next[1] = y - 1;
        }
    } else {
    }
    return next;
}
// randomly choose a chamber and call the random-choose function..
void Floor::choosechamb (char c, Game* game){
    int i = rand() % 5;
    chambers[i]->randomchoose(c,game);
}
// return the x-posn of the stair.
int Floor::getx(){
    return x;
}
// return the y-posn of the stair.
int Floor::gety(){
    return y;
}

void Floor::setx(int i){
    x = i;
}

void Floor::sety(int i){
    y = i;
}

void Floor::setpcstair(Game* game){
    int i = rand() % 5;
    int j = rand() % 5;
    while(j == i) j = rand() % 5;
    chambers[i]->randomchoose('@', game);
    chambers[j]->randomchoose('\\', game);
}
