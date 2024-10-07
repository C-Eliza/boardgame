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

int abs(int n){
  if(n>0) return n;
  else return -n;
}

int retryRand(int i){
  int try = -1;
  do{
    try = rand() % 6;
  } while(try==i);
  return try;
}

int touching(int** valueGrid, int* ownedX, int* ownedY, int x, int y, int score)
{
  //If x,y is in contact with any element ownedX, ownedY, append x,y to each array
  for(int index = 0; index < score; index++)
    if(ownedX[index]==x && ownedY[index]==y) return 0;
  
  for(int index = 0; index < score; index++)
    if( (ownedX[index] == x && abs(ownedY[index] - y) == 1) || (ownedY[index]==y && abs(ownedX[index] - x) == 1) )
    {
      ownedX[score] = x;
      ownedY[score] = y;
      return 1;
    };
  return 0;
}

int updateOwned(int** valueGrid, const int size, int ownedColor, int* ownedX, int* ownedY, int score)
{
  int newscore = score;
  do{
    score = newscore;
    for(int i = 0; i < size; i++) for(int j = 0; j < size; j++) 
    {
      if(valueGrid[i][j] != ownedColor) continue;
      newscore += touching(valueGrid, ownedX, ownedY, i, j, newscore);
    };
  } while (newscore != score);
  return newscore;
}

void changeGridColor(int** valueGrid, int ownedColor, int* ownedX, int* ownedY, int score)
{
  for(int i = 0; i < score; i++) valueGrid[ownedX[i]][ownedY[i]] = ownedColor;
}

//initializes the game and seed, hopefully prints grid too.
void init_game(int** valueGrid, const int size)
{
    for(int i = 0; i < size; i++)
      for(int j = 0; j < size; j++){
        valueGrid[i][j] = rand() % 6;
        if(i) if(valueGrid[i][j] == valueGrid[i-1][j]) valueGrid[i][j] = retryRand(valueGrid[i-1][j]);
        if(j) if(valueGrid[i][j] == valueGrid[i][j-1]) j--;
    };
}

void drawGrid(int **valueGrid, int size){
  //printing different colors for each possible grid value
  for(int i = 0; i < size; i++)
    for(int k = 0; k < 3; k++){
      for(int j = 0; j < size; j++)
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
    int color = 0;
    int ownedX[size * size];
    int ownedY[size * size];
    ownedX[0] = 0;
    ownedY[0] = 0;
    int score = 1;
    while (*statePtr==2||1)
    {
      sleep(1);
      color = (color + 1) % 6;
      changeGridColor(valueGrid, color, ownedX, ownedY, score);
      score = updateOwned(valueGrid, size, color, ownedX, ownedY, score);
      drawGrid(valueGrid, size);
      printf("\033[0;0H\033[2J");
    }
    free(valueGrid);
    for(int i = 0; i < size; i++) free(valueGrid[i]);
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
