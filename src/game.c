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

//initializes the game and seed, hopefully prints grid too.
int **init_game(int size)
{
    srand(time(NULL));
    
    //Creating dynamically sized array
    int **valueGrid;
    valueGrid = malloc(size * sizeof(*valueGrid));
    for(int i = 0; i < size; i++) valueGrid[i] = malloc(size * sizeof(*valueGrid[i]));
    for(int i = 0; i < size; i++) for(int j = 0; j < size; j++) valueGrid[i][j] = rand() % 6;

    return valueGrid;
}
 
void printColorChunk(int color){
  //prints out the four lines of color given a number
  switch(color)
  {
    case 0: printf(REDBG hfsqr  RESET);
      break;
    case 1: printf(GREENBG hfsqr  RESET);
      break;
    case 2: printf(YELLOWBG hfsqr  RESET);
      break;
    case 3: printf(BLUEBG hfsqr  RESET);
      break;
    case 4: printf(MAGENTABG hfsqr  RESET);
      break;
    case 5: printf(CYANBG hfsqr  RESET);
      break;
  }
}

void drawGrid(int **valueGrid, int size){
  //printing different colors for each possible grid value
  for(int i = 0; i < size; i++)
    for(int k = 0; k < 3; k++){
      for(int j = 0; j < size; j++)
        //printColorChunk(valueGrid[i][j]);
        printf(&COLORS[valueGrid[i][j]] hfsqr  RESET);
      printf("\n");
    };
}

int main(){
  /*
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
  */
  int size = 7;
  int **valueGrid = init_game(size);
  drawGrid(valueGrid, size);

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
