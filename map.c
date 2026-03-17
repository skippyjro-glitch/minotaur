// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "colours.h"
#include "map.h"

#define BUFFER_SIZE 10


extern char *map;
extern int width, height;

int open_file(char *filename);
char* create_map_array(int size);
int update_map_height(int *map_height);
int update_map_width(int *map_width, int count);
int update_map_array(char **map, int *allocated, int *used, char *row, int width);

/**
 * You should use this function to print out individual characters
 * in the colours used in the demo.
 * @param c
 */
static void printc(char c) {
    switch (c) {
        case WALL:
            change_text_colour(BLUE);
            break;
        case MINOTAUR:
            change_text_colour(MAGENTA);
            break;
        case PLAYER:
            change_text_colour(YELLOW);
            break;
        default:
            change_text_colour(WHITE);
    }
    printf("%c", c);
}

void print_map(void) {
    // Print the map given in the global map variable
    for (int y = 0; y<height; y++) {
        for (int x=0; x<width; x++) {
            printc(map[y*width+x]); //converts 2D coordinate to 1D
            if (x<width-1) {
                printf(" ");
            }
        }
        printf("\n");
    }
    change_text_colour(WHITE);
}

void print_revealed_map(int player_y, int player_x) {
    // Only the map within PLAYER_VISION_DISTANCE of the player (including diagonals) should be printed
    for (int y=0; y<height;y++) {
        for (int x=0; x<width; x++) {
            int dy = y-player_y; //position - player location in y
            int dx = x-player_x; //position - player location in x
            //check if location is within vision bounds
            if ((dy*dy+dx*dx)<=PLAYER_VISION_DISTANCE*PLAYER_VISION_DISTANCE) {
                printc(map[y*width+x]);
            } else {
                change_text_colour(WHITE); //WHITE shows empty space
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int locate_character(char character, int* character_y, int* character_x) {
    // Attempt to find the character in the map and return a status code indicating
    // if they were present
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            //checks if there's a character in the map
            if (map[y*width+x]==character) {
                *character_y=y;
                *character_x=x;
                return FOUND_CHARACTER;
            }
        }
    }
    return CHARACTER_NOT_FOUND;
}


char *load_map(char *filename, int *map_height, int *map_width) {
    FILE*fp=fopen(filename,"r");
    if(!fp){
        return NULL;
    }
    char *map=NULL;
    int width=0;
    int height=0;

    char maze[64];

    while(fgets(maze,sizeof(maze),fp)){
        if(maze[0]=='\n' || maze[0] =='\0'){
            continue;
        }    
        int maze_width=0;

        for(int i=0;maze[i]!='\0';i+=3){
            char temp = maze[i];

            if(temp=='\n' || temp=='\0'){
                break;
            }

            if(temp!=PLAYER && temp!=MINOTAUR && temp!=WALL && temp!=EMPTY){
                free(map);
                fclose(fp);
                return NULL;
            }

            char *new_map=realloc(map,(height*width+maze_width+1)*sizeof(char));
            if(!new_map){
                free(map);
                fclose(fp);
                return NULL;
            }
            map=new_map;
            map[height*width+maze_width]=temp;
            maze_width++;
        }
        if(height==0){
            width=maze_width;
        } else if(maze_width!=width){
            free(map);
            fclose(fp);
            return NULL;
        }
        height++;
    }
    fclose(fp);
    if(height==0 || width==0){
        free(map);
        return NULL;
    }
    *map_height=height;
    *map_width=width;
    return map;
}

/*int open_file(char *filename){
    FILE *fp=fopen(filename,"r");
    if (!fp){
        return -1;
    } fclose(fp);
    return 0;
}

char* create_map_array(int size){
    char *maze = malloc(size);
    if(maze==NULL) return NULL;
    return maze;
}

int update_map_height(int *map_height){
    (*map_height)++;
    return *map_height;
}

int update_map_width(int *map_width, int count){
    if(*map_width==-1){
        *map_width=count;
    }
    return *map_width;
}

int update_map_array(char **map, int *allocated, int *used, char *row, int width){
    if(*allocated==0){
        *allocated=64;
        *map=malloc(*allocated);
        if(!*map) return 0;
    }

    if(*used
    return 0;
}*/
