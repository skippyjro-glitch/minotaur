// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "game.h"

extern char * map;
extern int height;
extern int width;

int check_win(int player_y, int player_x) {
    // The player wins if they escape the map boundaries (i.e., they are in a place an outer wall tile should be).
    if (player_y>=height||player_x>=width||player_y<=0||player_x<=0) {
        return YOU_WIN;
    }
    return KEEP_GOING;
}

int check_loss(int player_y, int player_x, int minotaur_y, int minotaur_x) {
    // The player loses if they are caught by the Minotaur
    if (player_y==minotaur_y && player_x==minotaur_x) {
        return YOU_LOSE;
    }
    return KEEP_GOING;
}


