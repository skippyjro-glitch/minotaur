// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "colours.h"
#include "map.h"

#define BUFFER_SIZE 256


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
        }
        printf("\n");
    }
    change_text_colour(WHITE);
}

void print_revealed_map(int player_y, int player_x) {
    // Only the map within PLAYER_VISION_DISTANCE of the player (including diagonals) should be printed
    for (int y=0; y<height; y++) {
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

            if (x<width-1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int locate_character(char character, int* character_y, int* character_x) {
    // Attempt to find the character in the map and return a status code indicating
    for (int i = 0; i < height * width; i++) {
        if (map[i] == character) {
            *character_x = i % width;
            *character_y = i / width;
            return FOUND_CHARACTER;
        }
    }
    return CHARACTER_NOT_FOUND;

}

char *load_map(char *filename, int *map_height, int *map_width) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    int width = -1;
    int height = 0;
    int current_width = 0;
    int c;

    // 🔹 First pass: determine width & height
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            if (width == -1) {
                width = current_width;
            } else if (current_width != width) {
                fclose(file);
                return NULL; // ❗ inconsistent row length
            }
            height++;
            current_width = 0;
        } else if (c != '\r') {
            current_width++; // count EVERYTHING (including spaces)
        }
    }

    // Handle last line
    if (current_width > 0) {
        if (width == -1) {
            width = current_width;
        } else if (current_width != width) {
            fclose(file);
            return NULL;
        }
        height++;
    }

    if (width <= 0 || height <= 0) {
        fclose(file);
        return NULL;
    }

    char *map = malloc(width * height);
    if (!map) {
        fclose(file);
        return NULL;
    }

    // 🔹 Second pass: fill map row-by-row
    rewind(file);

    int x = 0, y = 0;

    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            if (x != width) {
                free(map);
                fclose(file);
                return NULL;
            }
            y++;
            x = 0;
        } else if (c != '\r') {
            if (x < width && y < height) {
                map[y * width + x] = (char)c;
                x++;
            }
        }
    }

    // Handle last line
    if (x > 0) {
        if (x != width) {
            free(map);
            fclose(file);
            return NULL;
        }
    }

    fclose(file);

    *map_width = width;
    *map_height = height;
    return map;
}
