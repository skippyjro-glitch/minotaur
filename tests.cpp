// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <stdio.h>

// make sure not to modify anything in this extern block
extern "C"{
#include "defines.h"
#include "map.h"
#include "character.h"
#include "game.h"
char *map = NULL;
int width, height;
}

/**
 * This file is where you should put your tests for your code.
 * Your code must have tests that execute at least 85% of the code in
 * required functions for you to get full marks for the project.
 * Make sure to check out the course videos on automated testing for
 * more information about how to write tests.
 */

/* Tests for map.c */
TEST_SUITE_BEGIN("Map tests");

// Tests for load_map
TEST_CASE("A test for load_map") {
    CHECK(0 == 0);
}

// Tests for is_wall

TEST_SUITE_END();

/* tests for character.c */
TEST_SUITE_BEGIN("Character tests");

// Tests for sees_player
    TEST_CASE("Minotaur sees player to the right") {
        height=3;
        width=5;
        char test_map[]={
            ' ', ' ', ' ', ' ', ' ',
            'M', ' ', ' ', 'P', ' ',
            ' ', ' ', ' ', ' ', ' '
        };
        map=test_map;
        CHECK(sees_player(1,3,1,0)==RIGHT);
    }
    TEST_CASE("wall blocks line of sight") {
        height=3;
        width=5;
        char test_map[]={
            ' ', ' ', ' ', ' ', ' ',
            'M', 'W', ' ', 'P', ' ',
            ' ', ' ', ' ', ' ', ' '
        };
        map=test_map;
        CHECK(sees_player(1,3,1,0)==SEES_NOTHING);
    }
    TEST_CASE("minotaur sees player above") {
        height=3;
        width=5;
        char test_map[]={
            ' ', ' ', 'P', ' ', ' ',
            ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', 'M', ' ', ' '
        };
        map=test_map;
        CHECK(sees_player(0,1,3,1)==UP);
    }
    TEST_CASE("minotaur and player are on same spot") {
        height=3;
        width=5;
        char test_map[]={
            ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', 'M', ' ', ' ',
            ' ', ' ', ' ', ' ', ' '
        };
        map=test_map;
        CHECK(sees_player(1,1,1,1)==CAUGHT_PLAYER);
    }

// Tests for locate_character
    TEST_CASE("does locate character find PLAYER?") {
        height=3;
        width=3;
        char test_map[]={
            ' ', 'P', ' ',
            ' ', ' ', ' ',
            ' ', ' ', ' '
        };
        map=test_map;
        int y=-1,x=-1;
        CHECK(locate_character('P',&y,&x) == FOUND_CHARACTER);
    }

    TEST_CASE("does locate character find MINOTAUR") {
        height=3;
        width=3;
        char test_map[]={
            'M', ' ', ' ',
            ' ', ' ', ' ',
            ' ', ' ', ' '
        };
        map=test_map;
        int y=-1,x=-1;
        CHECK(locate_character('M',&y,&x) == FOUND_CHARACTER);
    }

    TEST_CASE("does locate character find PLAYER?") {
        height=3;
        width=3;
        char test_map[]={
            ' ', ' ', ' ',
            ' ', ' ', ' ',
            ' ', ' ', ' '
        };
        map=test_map;
        int y=5,x=5;
        CHECK(locate_character('z',&y,&x) == CHARACTER_NOT_FOUND);
    }

// Tests for move_character
    TEST_CASE("check calculate index"){
    width=11;
        CHECK(calculate_index(3,4)==(4*width+3));
    }
    TEST_CASE("check moving in viable direction"){
        CHECK(check_direction('w')==1);
        CHECK(check_direction('s')==1);
        CHECK(check_direction('a')==1);
        CHECK(check_direction('d')==1);
        CHECK(check_direction('z')==0);
    }
    TEST_CASE("check 'a' makes new x-direction one less than original"){
        CHECK(calculate_newX(10, 'a')==9);
    }
    TEST_CASE("check 'd' makes new x-direction one more than original"){
        CHECK(calculate_newX(10, 'd')==11);
    }
    TEST_CASE("check 'w' makes new y-direction one more than original"){
        CHECK(calculate_newY(10, 'w')==9);
    }
    TEST_CASE("check 's' makes new y-direction one less than original"){
        CHECK(calculate_newY(10, 's')==11);
    }
    TEST_CASE("check within wall boundaries") {
    height=12;
    width=11;
        CHECK(check_x_boundary(-1,width)==1);
        CHECK(check_x_boundary(11,width)==1);
        CHECK(check_x_boundary(2,width)==0);

        CHECK(check_y_boundary(-1,height)==1);
        CHECK(check_y_boundary(12,height)==1);
        CHECK(check_y_boundary(2,height)==0);
    }
    TEST_CASE("move_character moves into empty spaces") {
    height=12;
    width=11;
    char cell = EMPTY;
    map=&cell;
    int x=1, y=1;
        CHECK(move_character(&y, &x, 'w', PLAYER)==MOVED_OKAY);
    }
    TEST_CASE("move_character hits wall") {
    height=12;
    width=11;
    char cell= WALL;
    map=&cell;
    int x=0, y=1;
        CHECK(move_character(&y, &x, 'w', PLAYER)==MOVED_WALL);
    }
// tests for charge_minotaur
    TEST_CASE("minotaur moves two spaces") {
        height=3;
        width=5;
        char test_map[]={
            ' ', ' ', ' ', ' ', ' ',
            ' ', 'M', ' ', ' ', ' ',
            ' ', ' ', ' ', ' ', ' '
        };
        map=test_map;
        int y=1,x=1;
        int result=charge_minotaur(&y,&x,-1,-1,RIGHT);
        CHECK(result==MOVED_OKAY);
        CHECK(y==1);
        CHECK(x==3);
        CHECK(map[calculate_index(3,1)]==MINOTAUR);
    }
    TEST_CASE("minotaur moves into a wall") {
        height=3;
        width=5;
        char test_map[]={
            ' ', ' ', ' ', ' ', ' ',
            ' ', 'M', 'W', ' ', ' ',
            ' ', ' ', ' ', ' ', ' '
        };
        map=test_map;
        int y=1,x=1;
        int result=charge_minotaur(&y,&x,-1,-1,RIGHT);
        CHECK(result==MOVED_WALL);
        CHECK(y==1);
        CHECK(x==2);
        CHECK(map[calculate_index(2,1)]==MINOTAUR);
    }
    TEST_CASE("minotaur catches player") {
        height=3;
        width=5;
        char test_map[]={
            ' ', ' ', ' ', ' ', ' ',
            ' ', 'M', ' ', ' ', ' ',
            ' ', ' ', ' ', ' ', ' '
        };
        map=test_map;
        int y=1,x=1;
        int result=charge_minotaur(&y,&x,1,2,RIGHT);
        CHECK(result==CAUGHT_PLAYER);
        CHECK(y==1);
        CHECK(x==2);
    }
    TEST_CASE("minotaur moves in an invalid direction") {
        height=3;
        width=5;
        char test_map[]={
            ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', 'M', ' ', ' ',
            ' ', ' ', ' ', ' ', ' '
        };
        map=test_map;
        int y=1,x=1;
        CHECK(charge_minotaur(&y,&x,-1,-1,'z')==MOVED_INVALID_DIRECTION);
        CHECK(y==1);
        CHECK(x==1);
    }

TEST_SUITE_END();

/* tests for game.c */
TEST_SUITE_BEGIN("Game tests");
// tests for check_win
    TEST_CASE("Check for win") {
    height=12;
    width=11;
        CHECK(check_win(12, 11)==1);
        CHECK(check_win(13, 12)==1);
        CHECK(check_win(0,0)==1);
        CHECK(check_win(0,1)==1);
        CHECK(check_win(1,0)==1);
        CHECK(check_win(12,10)==1);
        CHECK(check_win(11, 11)==1);
        CHECK(check_win(10,9)==0);
        CHECK(check_win(1,1)==0);
    }
// test for check_loss
    TEST_CASE("Check for loss") {
        CHECK(check_loss(1, 1, 1, 1)==1);
        CHECK(check_loss(0,0,0,0)==1);
        CHECK(check_loss(1,0,0,0)==0);
        CHECK(check_loss(0, 1,0,0)==0);
        CHECK(check_loss(0,0,1,0)==0);
        CHECK(check_loss(0,0,0,1)==0);
    }
TEST_SUITE_END();
