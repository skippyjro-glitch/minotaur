// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2026

#include "defines.h"
#include "character.h"

int check_direction(char direction);
int calculate_newX(*x);
int calculate_newY(*y);

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
    int newX=0;
    int newY=0;
    
    // check for an invalid direction (not LEFT, RIGHT, UP, or DOWN)
    if (check_direction(direction)==0){
        return MOVED_INVALID_DIRECTION;
    }
    
    // calculate the new coordinates to use on success (store in local variables)
    newX=calculate_newX(*x);
    newY=calculate_newY(*y);
    
    // check if the new coordinates point to a wall
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

int calculate_newX(*x){
    return 0;
}

int calculate_newY(*y){
    return 0;
}


int charge_minotaur(int *y, int *x, int player_y, int player_x, char charge_direction) {
    // call move_character twice or until a wall is hit
    // when the wall is hit, move the Minotaur into the wall in the direction it is charging
    // calculate the new coordinates
    return MOVED_OKAY;
}

