// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2026

#include "defines.h"
#include "character.h"

int check_direction(char direction);

extern char * map;
extern int height;
extern int width;

char sees_player(int player_y, int player_x, int minotaur_y, int minotaur_x) {
    // check to see if the Minotaur has caught the player
    // check if neither the x nor y coordinate is the same as the player
    // if there's a wall in between, they can't see
    // if one of them is the same, check if the path in between is clear
    return SEES_NOTHING;
}

int move_character(int * y, int * x, char direction, char character) {
    int invalid_direction;
    
    // check for an invalid direction (not LEFT, RIGHT, UP, or DOWN)
    invalid_direction = check_direction(direction);
    
    // calculate the new coordinates to use on success (store in local variables)
    int newY=*y;
    int newX=*x;
    switch(direction){
        case 'w':
            newY-=1;
            break;
        case 's':
            newY+=1;
            break;
        case 'a':
            newX-=1;
            break;
        case 'd':
            newX+=1;
            break
        default:
            return MOVED_INVALID_DIRECTION; 
    }
    // check if the new coordinates point to a wallg
    // at this point, the move is known to be valid (OK direction and not a wall)
    // remove character from the old position and replace with EMPTY
    // set character in the new position in map
    // update the x/y coordinate pointers
    return MOVED_OKAY;
}

int check_direction(char direction) {
    if(direction=='w'||direction=='s'||direction=='a'||direction=='d'){
        return 1;
    } else {
        return 0;
    }
}


int charge_minotaur(int *y, int *x, int player_y, int player_x, char charge_direction) {
    // call move_character twice or until a wall is hit
    // when the wall is hit, move the Minotaur into the wall in the direction it is charging
    // calculate the new coordinates
    return MOVED_OKAY;
}

