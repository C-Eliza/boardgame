#include <stdio.h>
#include <unistd.h>
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

//initializes the game and seed, hopefully prints grid too.
void init_game(int** valueGrid, const int size)
{
    for(int i = 0; i < size; i++) for(int j = 0; j < size; j++) valueGrid[i][j] = rand() % 6;
}

void drawGrid(int **valueGrid, int size){
  //printing different colors for each possible grid value
  for(int i = 0; i < size; i++)
    for(int k = 0; k < 3; k++){
      for(int j = 0; j < size; j++)
        //printColorChunk(valueGrid[i][j]);
        printf("%s" hfsqr  RESET,COLORS[valueGrid[i][j]]);
      printf("\n");
    };
}

int main(){

    GameState state = DEAD_STATE;
    GameState *statePtr=&state;
    //Creating dynamically sized array
    const int size = 7;
    int** valueGrid = malloc(size * sizeof(*valueGrid));
    for(int i = 0; i < size; i++) valueGrid[i] = malloc(size * sizeof(*valueGrid[i]));
    srand(time(NULL));
    init_game(valueGrid, size);
    while (*statePtr==2||1)
    {
      sleep(1);
      init_game(valueGrid, size);
      drawGrid(valueGrid, size);
      printf("\033[0;0H\033[2J");
    }
    free(valueGrid);
    return 0;
}

void updateState(GameState *stateptr)
{

}


//Takes in a string with a color modifier and changes the modifier to be of a target color
void changeColor(char *gridSqr, unsigned int targetColor)
{
    //validates length of string so no overflow

    //changes the first n characters to be a different element of COLORS[]

}
