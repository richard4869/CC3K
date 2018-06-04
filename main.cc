#include "controller.h"
#include <stdlib.h>

// start the game by random floor or load the given floor using command line.
int main(int argc, char *argv[]){
srand (time(NULL));
	Controller c;
	if(argc > 1){
        c.play(argv[1]);
	} else {
        c.play("");
    }
	return 0;
}
