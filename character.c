// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2026

#include "defines.h"
#include "character.h"

int check_direction(char direction);
int calculate_newX(int x, char direction);
int calculate_newY(int y, char direction);
int check_wall_collision(int newX, int newY);
int calculate_index(int x,  int y);
int check_x_boundary(int x, int width);
int check_y_boundary(int y, int height);
int attempt_charge_step(int * p, int * x, char charge_direction);
void break_wall_and_move(int * p, int * x, char charge_direction);
int aligned(int player_y, int player_x, int minotaur_y, int minotaur_x);
char determine_direction(int player_y, int player_x, int minotaur_y, int minotaur_x);
int path_clear(int player_y, int player_x, int minotaur_y, int minotaur_x, char direction);


extern char * map;
extern int height;
extern int width;

char sees_player(int player_y, int player_x, int minotaur_y, int minotaur_x) {
    // check to see if the Minotaur has caught the player
    if(player_x==minotaur_x && player_y==minotaur_y) {
        return CAUGHT_PLAYER;
    }
    // check if neither the x nor y coordinate is the same as the player
    if(!aligned(player_y, player_x, minotaur_y, minotaur_x)) {
        return SEES_NOTHING;
    }
    // if there's a wall in between, they can't see
    char direction = determine_direction(player_y, player_x, minotaur_y, minotaur_x);
    // if one of them is the same, check if the path in between is clear
    if (path_clear(player_y, player_x, minotaur_y, minotaur_x, direction)) {
        return direction;
    }
    return SEES_NOTHING;
}

int aligned(int player_y, int player_x, int minotaur_y, int minotaur_x) {
    return (player_x==minotaur_x)||(player_y==minotaur_y);
}

char determine_direction(int player_y, int player_x, int minotaur_y, int minotaur_x) {
    if (player_x==minotaur_x) {
        if (player_y<minotaur_y) {
            return UP;
        } else {
            return DOWN;
        }
    }
    if (player_y==minotaur_y) {
        if (player_x<minotaur_x) {
            return LEFT;
        } else {
            return RIGHT;
        }
    }
    return SEES_NOTHING;
}

int path_clear(int player_y, int player_x, int minotaur_y, int minotaur_x, char direction) {
    int checkX=minotaur_x;
    int checkY=minotaur_y;

    while (1) {
        checkX=calculate_newX(checkX, direction);
        checkY=calculate_newY(checkY, direction);
        if (checkX==player_x&&checkY==player_y) {
            return 1;
        }
        if (check_wall_collision(checkX, checkY)) {
            return 0;
        }
        if (check_x_boundary(checkX, width)||check_y_boundary(checkY, height)) {
            return 0;
        }
    }
}

int move_character(int * y, int * x, char direction, char character) {
    int currentX = *x;
    int currentY = *y;
    int newX=0;
    int newY=0;

    // check for an invalid direction (not LEFT, RIGHT, UP, or DOWN)
    if (check_direction(direction)==0){
        return MOVED_INVALID_DIRECTION;
    }

    // calculate the new coordinates to use on success (store in local variables)
    newX=calculate_newX(currentX, direction);
    newY=calculate_newY(currentY, direction);

    // check if the new coordinates point to a wall
    if (check_x_boundary(newX,width) || check_y_boundary(newY, height)||check_wall_collision(newX, newY)==1) {
        return MOVED_WALL;
    } else {
        // at this point, the move is known to be valid (OK direction and not a wall)
        // remove character from the old position and replace with EMPTY
        map[calculate_index(*x,*y)] = EMPTY;
        // set character in the new position in map
        map[calculate_index(newX,newY)] = character;
        // update the x/y coordinate pointers
        *x=newX;
        *y=newY;
        return MOVED_OKAY;
    }
}

int calculate_index(int x,  int y){
    int index = y*width+x;
    return index;
}

int check_direction(char direction) {
    if(direction==UP||direction==DOWN||direction==LEFT||direction==RIGHT){
        return 1;
    } else {
        return 0;
    }
}

int calculate_newX(int x, char direction){
    if(direction==LEFT){
        return x-1;
    }
    if(direction==RIGHT){
        return x+1;
    }
    return x;
}

int calculate_newY(int y, char direction){
    if(direction==DOWN){
        return y+1;
    }
    if(direction==UP){
        return y-1;
    }
    return y;
}

int check_x_boundary(int x, int width) {
    if (x<0 || x>=width) {
        return 1;
    } return 0;
}

int check_y_boundary(int y, int height) {
    if (y<0 || y>=height) {
        return 1;
    } return 0;
}

int check_wall_collision(int newX, int newY){
    if(map[calculate_index(newX, newY)]==WALL){
        return 1;
    } else {
        return 0;
    }
}

int charge_minotaur(int *y, int *x, int player_y, int player_x, char charge_direction) {
    // call move_character twice or until a wall is hit
    if (check_direction(charge_direction)==0){
        return MOVED_INVALID_DIRECTION;
    }
    // when the wall is hit, move the Minotaur into the wall in the direction it is charging
    for(int i=0;i<2;i++) {
        int result = attempt_charge_step(y,x,charge_direction);

        if(result==MOVED_WALL) {
            break_wall_and_move(y,x,charge_direction);
            return MOVED_WALL;
        }

        if(result==MOVED_INVALID_DIRECTION) {
            return MOVED_INVALID_DIRECTION;
        }
        if (*x==player_x&&*y==player_y) {
            return CAUGHT_PLAYER;
        }
    }
    // calculate the new coordinates
    return MOVED_OKAY;
}

int attempt_charge_step(int *y, int *x, char direction) {
    return move_character(y,x,direction, MINOTAUR);
}

void break_wall_and_move(int *y, int *x, char direction) {
    int newY=calculate_newY(*y,direction);
    int newX=calculate_newX(*x,direction);

    map[calculate_index(*x, *y)]=EMPTY;
    map[calculate_index(newX, newY)]=MINOTAUR;

    *y=newY;
    *x=newX;
}
