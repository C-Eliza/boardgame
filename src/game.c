#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "color.h"
//defines hfsqr so spaces are uniform
#define hfsqr "      "
//Defines a state type.
typedef enum{
    DEAD_STATE =0,
    PLAYER_WIN=1,
    PLAYER_LOSE=-1,
    RUNNING_STATE = 2} GameState;

void drawGrid();
int main(){
    //initial state is dead
    GameState gameState=0;
    printf(BLUEBG hfsqr  RESET);
    printf(REDBG hfsqr   RESET);
    printf(GREENBG hfsqr RESET"\n");
    //Since a square is 2 hfsqr vertically, we print them again on a new line.
    printf(BLUEBG hfsqr  RESET);
    printf(REDBG hfsqr   RESET);
    printf(GREENBG hfsqr RESET"\n");
    return 0;
}

//initializes the game and seed, hopefully prints grid too.
int init_game()
{
    srand(time(NULL));
    drawGrid();
    return 0;
}


void updateState(GameState *state)
{

}


//Takes in a string with a color modifier and changes the modifier to be of a target color
void changeColor(char *gridSqr, unsigned int targetColor)
{
    //validates length of string so no overflow

    //changes the first n characters to be a different element of COLORS[]

}