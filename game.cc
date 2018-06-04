#include "game.h"
#include <fstream>
#include <string>
#include <stdlib.h>
#include "monster.h"
#include "pc.h"
#include "floor.h"
#include "controller.h"
#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include "potion.h"
#include "gold.h"
#include "monster.h"
#include "human.h"
#include "elf.h"
#include "dwarf.h"
#include "dragon.h"
#include "halfling.h"
#include "orc.h"
#include "merchant.h"
#include <time.h>
#include "robot.h"

using namespace std;
// constructor with controller it in and nothing else.
Game::Game(Controller * ctr):
    controller(ctr),
    floor(NULL),
    pc(NULL),
    level(0),
    mertile(false),
    ifload(false),
    filename(""){
    extra = new char*[25];
    for(int i = 0; i < 25; i++){
     extra[i] = new char[79];
    for(int j = 0; j < 79; j++){
        extra[i][j] = ' ';
    }
}
//add monsters
    monsters=new Monster *[30];
int i=0;
while (i<30){
    monsters[i]=NULL;
    i++;
}
//add golds
golds=new Gold *[10];
i=0;
while(i<10){
    golds[i]=NULL;
    i++;
}
//add potions
potions=new Potion *[10];
i=0;
while(i<10){
    potions[i]=NULL;
    i++;
}}

//destructor.
Game::~Game(){
delete floor;
delete pc;
int i=0;
while(i<30){
    delete monsters[i];
    i++;
}
delete[] monsters;
i=0;
while(i<10){
delete golds[i];
i++;
}
delete[] golds;
i=0;
while(i<10){
    delete potions [i];
    i++;
}
delete []potions;
for(int i = 0; i < 25; i++){
    delete[] extra[i];
}
delete[] extra;
}

// return the pointer of the floor.
Floor *Game::getfloor(){
    return floor;
}

// return the pointer of the pc.
PC* Game::getpc(){
    return pc;
}

// return the floor level of the pc.
int Game::getlevel(){
return level;
}

// new a pc with given char as the race.
void Game::setpc(char r){
    int i = 0;
    int j = 0;
    switch(r){
        case 's':
            pc=new Shade(i,j,this);
            extra[i][j]='@';
            break;
        case 'd':
            pc = new Drow(i,j,this);
            extra[i][j]='@';
            break;
        case 't':
            pc=new Troll(i,j,this);
            extra[i][j]='@';
            break;
        case 'v':
            pc=new Vampire(i,j,this);
            extra[i][j]='@';
            break;
        case 'g':
            pc=new Goblin(i,j,this);
            extra[i][j]='@';
            break;
        #ifdef DLC
        case 'r':
            pc=new Robot(i,j,this);
            extra[i][j]='@';
            break;
        #endif // ROBOT
    }
}

// initfloor with randomly generation method and the given filename.
void Game::initfloor(string name){
srand (time(NULL));
floor = new Floor();
floor->initnew(name);
floor->setpcstair(this);
int numm=0;
int numg=0;
int nump=0;
int i;
//golds
while(numg<10){
    i=rand() % 8;
    switch (i){
    case 0:
    floor->choosechamb('9',this);
    numg++;
    break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    floor->choosechamb('6',this);
    numg++;
    break;
    case 6:
    case 7:
    floor->choosechamb('7',this);
    numg++;
    break;
    }}
//monsters
while (numm<20){
    i=rand() % 18;
    switch (i){
        case 1:
        case 2:
        case 3:
        case 0:
            floor->choosechamb('H',this);
            numm++;
            break;
        case 5:
        case 6:
        case 4:
            floor->choosechamb('W',this);
            numm++;
            break;
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            floor->choosechamb('L',this);
            numm++;
            break;
        case 12:
        case 13:
            floor->choosechamb('E',this);
            numm++;
            break;
        case 14:
        case 15:
            floor->choosechamb('O',this);
            numm++;
            break;
        case 16:
        case 17:
            floor->choosechamb('M',this);
            numm++;
            break;
    }}
//potions
while (nump<10){
    i=rand() % 6;
    switch (i){
    case 0:
    floor->choosechamb('0',this);
    nump++;
    break;
    case 1:
    floor->choosechamb('1',this);
    nump++;
    break;
    case 2:
    floor->choosechamb('2',this);
    nump++;
    break;
    case 3:
    floor->choosechamb('3',this);
    nump++;
    break;
    case 4:
    floor->choosechamb('4',this);
    nump++;
    break;
    case 5:
    floor->choosechamb('5',this);
    nump++;
    break;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//link the rest dragon to their hoards
//visit dragon to call match dragon
int di=0;
while (di<30){
    if(monsters[di]!=NULL && monsters[di]->gettype()=='D'){
        monsters[di]->returndragon();
    }
    di++;
}
}

// move PC to the given direction.
void Game::movepc(string s){
if(pc->gettype() == 't') pc->addHP(5); // Troll get 5 hp every round .
string dir;
if(s == "no") dir="North";
if(s == "ea") dir="East";
if(s == "we") dir="West";
if(s == "so") dir="South";
if(s == "ne") dir="Northeast";
if(s == "nw") dir="Northwest";
if(s == "se") dir="Southeast";
if(s == "sw") dir="Southwest";
int x=pc->getx();
int y=pc->gety();
int *a=floor->getcell(x,y,s);
int nx=a[0];
int ny=a[1];
delete[] a;
if(extra[nx][ny]=='\\'){ // go downstairs if stairs reached.
    go_downstairs();
    return;
}else
if((nx== x &&ny== y) || ((extra[nx][ny]>'9'|| extra[nx][ny]<'6')&& extra[nx][ny]!=' ')){ //  notify invalid if the move is invalid.
notify("what are you doing? Stupid!! ");
}else{
if(extra[nx][ny]=='6'||extra[nx][ny]=='7'||extra[nx][ny]=='8'||extra[nx][ny]=='9'){ // get the gold if gold exists at that direction.
string sa="PC moves "+dir + ". ";
string ss;
notify(sa);
int di=0;
while (di<10){
    if(golds[di]!=NULL){
    if(nx==golds[di]->getx()&&ny==golds[di]->gety()){
        break;
    }}
    di++;
}
if(extra[nx][ny]=='9'&&golds[di]->linked==true){ // Cannot got the dragon hoard if its dragon is still alive.
    notify("dragon is guarding the treasure. ");
}else{
takegold(s);
pc->chamove(nx,ny);
int i=-1;
while (i<2){ // Check if there are potion around the new position.
    int j=-1;
    while(j<2){
        char t=extra[nx+i][ny+j];
        string ty;
            switch (t){
            case '0':
                if(pc->eaten(0)){
                    ty="a RH potion";
                }else{
                    ty="an unknown potion";
                }
                ss=" and sees "+ty;
                    notify(ss);
                break;
            case '1':
                if(pc->eaten(1)){
                    ty="a BA potion";
                }else{
                    ty="an unknown potion";
                }
                ss=" and sees "+ty;
                    notify(ss);
                break;
            case '2':
                if(pc->eaten(2)){
                    ty="a BD potion";
                }else{
                    ty="an unknown potion";
                }
                ss=" and sees "+ty;
                    notify(ss);
                break;
            case '3':
                if(pc->eaten(3)){
                    ty="a PH potion";
                }else{
                    ty="an unknown potion";
                }
                ss=" and sees "+ty;
                    notify(ss);
                break;
            case '4':
                if(pc->eaten(4)){
                    ty="a WA potion";
                }else{
                    ty="an unknown potion";
                }
                ss=" and sees "+ty;
                    notify(ss);
                break;
            case '5':
                if(pc->eaten(5)){
                    ty="a WD potion";
                }else{
                    ty="an unknown potion";
                }
                ss=" and sees "+ty;
                    notify(ss);
            default:
                break;
            }
            j++;
        }
        i++;
    }
    notify(". ");
}}else {  // move the pc to that direction.
pc->chamove(nx,ny);
string s="PC moves "+dir;
string ss;
notify(s);
int i=-1;
while (i<2){
    int j=-1;
    while(j<2){
        char t=extra[nx+i][ny+j];
        string ty;
            switch (t){
            case '0':
                if(pc->eaten(0)){
                    ty="a RH potion";
                }else{
                    ty="an unknown potion";
                }
                ss=" and sees "+ty;
                    notify(ss);
                break;
            case '1':
                if(pc->eaten(1)){
                    ty="a BA potion";
                }else{
                    ty="an unknown potion";
                }
                ss=" and sees "+ty;
                    notify(ss);
                break;
            case '2':
                if(pc->eaten(2)){
                    ty="a BD potion";
                }else{
                    ty="an unknown potion";
                }
                ss=" and sees "+ty;
                    notify(ss);
                break;
            case '3':
                if(pc->eaten(3)){
                    ty="a PH potion";
                }else{
                    ty="an unknown potion";
                }
                ss=" and sees "+ty;
                    notify(ss);
                break;
            case '4':
                if(pc->eaten(4)){
                    ty="a WA potion";
                }else{
                    ty="an unknown potion";
                }
                ss=" and sees "+ty;
                    notify(ss);
                break;
            case '5':
                if(pc->eaten(5)){
                    ty="a WD potion";
                }else{
                    ty="an unknown potion";
                }
                ss=" and sees "+ty;
                    notify(ss);
            default:
                break;
            }
            j++;
        }
        i++;
    }
    notify(". ");
}}}

// notify the sentences to the controller.
void Game::notify(string s){
controller->notify(s);
}

// Called when monsters got their turn.
void Game::monster_turn(){
int i=0;
int px = pc->getx();
int py = pc->gety();
while (i<30){ // loop every alive monster.
    if(monsters[i]!=NULL){
        if(monsters[i]->gettype()=='D'){
            //if the monster is dragon
                monsters[i]->dragonmove(pc);
            }else {
//delete unwalkable area
        int len=0;
        int x=monsters[i]->getx();
        int y=monsters[i]->gety();
        int **a=floor->getadj(x,y);
        int j=0;
        while (j<8&&a[j]!=NULL){
                int m=a[j][0];
                int n=a[j][1];
            if(extra[m][n] != ' '){
                delete[] a[j];
                a[j]=NULL;
            } else {
                len++;
            }
            j++;
        }
//condition when monster attack pc
        if(px - x <= 1 && px - x >= -1 && py - y <= 1 && py - y >= -1){
            monsters[i]->attack(pc);
        } else {
//monsters' random walk
            if(monsters[i]->gettype() != 'D'){
            if(len!=0){
                int k=rand() % len+1;
                int t=0;
                while (k>0&&t<8){
                    if(a[t]!=NULL){
                        k--;
                    if(k==0) break;
                    }
                t++;
                }
                int mx=monsters[i]->getx();
                int my = monsters[i]->gety();
                char mt = monsters[i]->gettype();
                extra[mx][my] = ' ';
                monsters[i]->chamove(a[t][0],a[t][1]);
                extra[a[t][0]][a[t][1]] = mt;
            }}
        }
        j=0;
        while(j<8){
            if(a[j]!=NULL){
            delete [] a[j];
            }
            j++;
        }
        delete []a;
    }}
    i++;
}
}

// Called when pc moves to a stair.
void Game::go_downstairs(){
level++;
if(level == 5) { // end the game if pc is going sown to the sixth floor.
    controller->ifend = 2;
    notify("PC is going down to the sixth floor. ");
} else { // reset the floor and go downstairs.
    delete floor;
for(int i = 0; i < 25; i++){
    for(int j = 0; j < 79; j++){
        extra[i][j] = ' ';
    }
}
int i=0;
while(i<30){
    delete monsters[i];
    monsters[i] = NULL;
    i++;
}
i=0;
while(i<10){
delete golds[i];
    golds[i] = NULL;
i++;
}
i=0;
while(i<10){
    delete potions [i];
    potions [i] = NULL;
    i++;
}
pc->resetboost(); // reset the boost attack and defenses.
if(ifload){  // initial floor according to whether the game is loaded or not.
    load(filename);
} else {
initfloor(filename);
}
}}

// Called when pc is using potion at given direction.
void Game::usepotion(string s){
if(pc->gettype() == 't') pc->addHP(5);
if(pc->gettype() == 'r'){
    notify("Hey! You are a robot!!");
}else {
int x=pc->getx();
int y=pc->gety();
int *a=floor->getcell(x,y,s);
int nx=a[0];
int ny=a[1];
delete []a;
if((x == nx && y == ny) || extra[nx][ny] >'5' || extra[nx][ny] <'0'){
    notify("No potion there.");
} else {
int i=0;
while (i<10){
         if(potions[i] != NULL){
        int px = potions[i]->getx();
        int py = potions[i]->gety();
    if(px==nx&&py==ny){
            int pt = potions[i]->gettype();
            pc->takepotion(potions[i]);
        if(pc->eaten(pt)){
            int p=potions[i]->gettype();
            switch(p){
            case 0:
                notify("PC uses RH. ");
            break;
            case 1:
                notify("PC used BA. ");
                break;
            case 2:
                notify("PC uses BD. ");
                break;
            case 3:
                notify("PC uses PH. ");
                break;
            case 4:
                notify("PC uses WA. ");
                break;
            case 5:
                notify("PC uses WD. ");
                break;
            }}
        extra[px][py] = ' ';
        delete potions[i];
        potions[i]=NULL;
        break;
    }}
    i++;
}
}
}
}

// Called when pc is taking the gold at given direction.
void Game::takegold(string s){
int x=pc->getx();
int y=pc->gety();
int *a=floor->getcell(x,y,s);
x=a[0];
y=a[1];
delete []a;
int i=0;
while (i<10){
        if(golds[i] != NULL){
        int gx = golds[i]->getx();
        int gy = golds[i]->gety();
        if(gx == x && gy == y){
            int m=golds[i]->getvalue();
            cout << m << endl;
            switch(m){
            case 1:
                notify("PC get small piles");
                break;
            case 2:
                notify("PC get normal piles");
                break;
            case 4:
                notify("PC get merchant piles");
                break;
            case 6:
                notify("PC get dragon piles");
                break;
        }
        pc->getmoney(m);
        extra[gx][gy] = ' ';
        delete golds[i];
        golds[i]=NULL;
        break;
        }
        }
        i++;
}}

// Called when the monster consumed is dead.
void Game::monsterdead(Monster * mostr){
    int i=0;
if(pc->gettype() == 'g') pc->getmoney(5); // goblin get 5 more gold when killing an enemy.
if(mostr->gettype() == 'M'){ // merchant is dead and drop a merchant hoard.
    pc->getmoney(4);
} else if(mostr->gettype() == 'H'){ // Human is dead and drop 2 piles of normal gold.
    pc->getmoney(4);
} else { // 50% chance randomly choosing between get a small or normal pile of gold.
    int m = rand() % 2;
    if(m == 0){
        pc->getmoney(1);
    } else {
        pc->getmoney(2);
    }
}
    stringstream ss;
    string s;
    ss << mostr->gettype();
    ss >> s;
    s = s + " is dead. ";
    notify(s);
    while(i<30){ // delete that dead monster.
        if(monsters[i]!= NULL && mostr==monsters[i]){
            int mx = mostr->getx();
            int my = mostr->gety();
            extra[mx][my] = ' ';
            delete monsters[i];
            monsters[i]=NULL;
        }
    i++;
    }
}

// return the score the player got. got 1.5 times score if pc is shade.
int Game::getscore(){
int i=pc->getgold();
if(pc->gettype()=='s'){
    i=i*1.5;
}
return i;
}

// Called when pc is dead.
void Game::PCdead(){
controller->ifend = 1;
}

// Called when pc attacks the enemy at the given direction.
void Game::pcattack(string s){
    if(pc->gettype() == 't') pc->addHP(5);
    int x = pc->getx();
    int y = pc->gety();
    int *a=floor->getcell(x,y,s);
    int nx=a[0];
    int ny=a[1];
    delete []a;
    if ((x == nx && y == ny) || (extra[nx][ny] != 'H' &&
        extra[nx][ny] != 'D' &&
        extra[nx][ny] != 'L' &&
        extra[nx][ny] != 'O' &&
        extra[nx][ny] != 'E' &&
        extra[nx][ny] != 'M' &&
        extra[nx][ny] != 'W')){
            notify("Monster does not exist at that direction. ");
    } else {
        for(int i = 0; i < 30; i++){
            if(monsters[i] != NULL && monsters[i]->getx() == nx && monsters[i]->gety() == ny){
                pc->attack(monsters[i]);
                break;
            }
        }
    }

}

// set the hostile of the merchant to active.
void Game::matt(){
mertile=true;
}

// return the hostile of the merchant.
bool Game::mattla(){
return mertile;
}

// Consumes a type and add a monster, gold and potion to the game or reset the position of pc and stairs.
void Game::addthings(int i,int j,char type){
switch (type){
case '0':
case '1':
case '2':
case '3':
case '4':
case '5':
    if(extra[i][j]!=' '){
        floor->choosechamb(type,this);
    }else{
        int n=0;
        while(n<10){
            if(potions[n]==NULL){
                potions[n]=new Potion(i,j,type-'0');
                extra[i][j]=type;
            break;
            }
        n++;
        }
    }
    break;
case '6':
case '7':
case '8':
case '9':
    if(extra[i][j]!=' '){
        floor->choosechamb(type,this);
    }else{
    int n=0;
    while(n<10){
    if(golds[n]==NULL){
        if(type=='6'){
        golds[n]=new Gold(i,j,1);
        extra[i][j]=type;
        break;
        }else if(type=='7'){
        golds[n]=new Gold(i,j,2);
        extra[i][j]=type;
        break;
        }else if(type=='8'){
        golds[n]=new Gold(i,j,4);
        extra[i][j]=type;
        break;
        }else if(type=='9'){
        golds[n]=new Gold(i,j,6);
        extra[i][j]=type;
        if(!ifload){
        int **a=floor->getadj(i,j);
        int k=0;
        while(k < 8 && a[k]!=NULL){
            int x=a[k][0];
            int y=a[k][1];
            if(extra[x][y]!=' '){
                delete[] a[k];
                a[k]=NULL;
            }
            k++;
        }
        k=0;
        while (k<8){
            if(a[k]!=NULL){
                addthings(a[k][0],a[k][1],'D');
                break;
            }
            k++;
        }
        k=0;
        while (k<8){
            delete [] a[k++];
        }
        delete [] a;
        break;
        }}
        }
    n++;
    }}
    break;
case 'H':
    if(extra[i][j]!=' '){
        floor->choosechamb(type,this);
    }else{
    int n=0;
    while(n<30){
    if(monsters[n]==NULL){
        monsters[n]=new Human(i,j,this);
        extra[i][j]=type;
        break;
    }
    n++;
    }}
    break;
case 'E':
    if(extra[i][j]!=' '){
        floor->choosechamb(type,this);
    }else{
    int n=0;
    while(n<30){
    if(monsters[n]==NULL){
        monsters[n]=new Elf(i,j,this);
        extra[i][j]=type;
        break;
    }
    n++;
    }}
    break;
case 'W':
    if(extra[i][j]!=' '){
        floor->choosechamb(type,this);
    }else{
    int n=0;
    while(n<30){
    if(monsters[n]==NULL){
        monsters[n]=new Dwarf(i,j,this);
        extra[i][j]=type;
        break;
    }
    n++;
    }}
    break;
case 'L':
    if(extra[i][j]!=' '){
        floor->choosechamb(type,this);
    }else{
    int n=0;
    while(n<30){
    if(monsters[n]==NULL){
        monsters[n]=new Halfling(i,j,this);
        extra[i][j]=type;
        break;
    }
    n++;
    }}
    break;
case 'M':
    if(extra[i][j]!=' '){
        floor->choosechamb(type,this);
    }else{
    int n=0;
    while(n<30){
    if(monsters[n]==NULL){
        monsters[n]=new Merchant(i,j,this);
        extra[i][j]=type;
        break;
    }
    n++;
    }}
    break;
case 'D':
    if(extra[i][j]!=' '){
        floor->choosechamb(type,this);
    }else{
    int n=0;
    while(n<30){
    if(monsters[n]==NULL){
        Dragon *dra=new Dragon(i,j,this);
        monsters[n]=dra;
        //link a dragon to a adjacent dragon hoard;
        int **da =floor->getadj(i,j);
        int di=0;
        int cot=0;
        int theonex;
        int theoney;
        while (di<8){
            if(da[di]!=NULL){
            int dx=da[di][0];
            int dy=da[di][1];
            if(extra[dx][dy]=='9'){
                cot++;
                theonex=dx;
                theoney=dy;
            }}
            di++;
        }
        if(cot==1){
            int dj=0;
        while (dj<10){
            if(golds[dj]!=NULL){
            if(golds[dj]->getx()==theonex && golds[dj]->gety()==theoney){
                dra->dragonhoard=golds[dj];
                golds[dj]->linked=true;
                break;
            }}
            dj++;
        }
        }
        int dk=0;
        while(dk<8){
            delete[] da[dk];
            dk++;
        }
        delete[] da;
//////////////////////////////////////////////////////////
        extra[i][j]=type;
        break;
    }
    n++;
    }}
    break;
case 'O':
    if(extra[i][j]!=' '){
        floor->choosechamb(type,this);
    }else{
    int n=0;
    while(n<30){
    if(monsters[n]==NULL){
        monsters[n]=new Orc(i,j,this);
        extra[i][j]=type;
        break;
    }
    n++;
    }}
    break;
case '\\':
    floor->setx(i);
    floor->sety(j);
    extra[i][j]=type;
    break;
case '@':
    pc->setxy(i,j);
    break;
}
}

// load the game with given filename.
void Game::load(string name){
    ifload = true;
    floor = new Floor();
    floor->initload(name);
    ifstream file(name.c_str());
    int i = 25 * level;
    string s;
    char c;
    for(int l = 0; l < i; l++){
        getline(file,s);
    }
    int ni = 0;
    while(ni < 25){
        getline(file,s);
        istringstream iss(s);
		int j = 0;
        while((c = iss.get()), iss){
            if(c != '.' && c != '+' && c != '-' && c != '#' && c != '|' && c != ' '){
                if(c == '@'){
                     addthings(ni,j,c);
                     extra[ni][j] = ' ';
                } else {
                    addthings(ni,j,c);
                    extra[ni][j] = c;
                }
            }
            j++;
        }
        ni++;
    }
/////////////////////////////////////////////////////////////////////////////////////////////////
//link the rest dragon to their hoards
//visit dragon to call match dragon
int di=0;
while (di<30){
    if(monsters[di]!=NULL && monsters[di]->gettype()=='D'){
        monsters[di]->returndragon();
    }
    di++;
}
}

// match dragon to the dragon hoard.
//use visitor pattern
void Game::matchdragon(Dragon* d){
/////////////////////////////////////////////////////////////////////////////////////////////////
//link the rest dragon to their hoards
        int dx=d->getx();
        int dy=d->gety();
        if(d->dragonhoard==NULL){
            int ** da=floor->getadj(dx,dy);
            int dj=0;
            while(dj<8){
                if(da[dj]!=NULL){
                    int gx=da[dj][0];
                    int gy=da[dj][1];
                    if(extra[gx][gy]=='9'){
                    int dk=0;
                    while(dk<10){
                        if(golds[dk]!=NULL){
                            if(golds[dk]->getx()==gx && golds[dk]->gety()==gy && golds[dk]->linked==false){
                                d->dragonhoard=golds[dk];
                                golds[dk]->linked=true;
                                break;
                            }
                        }
                        dk++;
                    }
                }}
            dj++;
            }
        int dii=0;
        while (dii<8){
            delete []da[dii];
            dii++;
        }
        delete []da;
}}
