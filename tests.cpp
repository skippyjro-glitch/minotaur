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

// tests for sees_player

// tests for move_character
    TEST_CASE("check moving in viable direction"){
        CHECK(check_direction('w')==1);
    }
    TEST_CASE("check 'a' makes new x-direction one less than original"){
        int x=10;
        CHECK(calculate_newX(10, 'a')==9);
    }
// tests for charge_minotaur
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
        CHECK(check_win(11,10)==0);
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
