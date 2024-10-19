// ReSharper disable CppDFANullDereference
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "color.h"
//defines hfsqr so spaces are uniform
#define hfsqr "      "
//defines min macro
#define MIN(a,b) (((a)<(b))?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
//Defines a state type.
typedef enum
{
    DEAD_STATE = 0,
    PLAYER_WIN = 2,
    PLAYER_LOSE = -1,
    PLAYER_DRAW = 3,
    RUNNING_STATE = 1
} GameState;

GameState state = DEAD_STATE;
static GameState* statePtr = &state;

void updateStatus(GameState* statePtr);

int getScore(const int *arr,int ln)
{
    int x = 0;
    for(int i=0;i<ln;i++)
    {
        x+=MIN(arr[i],1);
    }
    return x;
}
int retryRand(const int i)
{
    int try = -1;
    do
    {
        try = rand() % 6;
    }
    while (try == i);
    return try;
}

int touching(int** valueGrid, int* ownedX, int* ownedY, const int x, const int y, const int score)
{
    //If x,y is in contact with any element ownedX, ownedY, append x,y to each array
    for (int index = 0; index < score; index++)
        if (ownedX[index] == x && ownedY[index] == y) return 0;

    for (int index = 0; index < score; index++)
        if ((ownedX[index] == x && abs(ownedY[index] - y) == 1) || (ownedY[index] == y && abs(ownedX[index] - x) == 1))
        {
            ownedX[score] = x;
            ownedY[score] = y;
            return 1;
        };
    return 0;
}

int updateOwned(int** valueGrid, const int size, const int ownedColor, int* ownedX, int* ownedY, int score)
{
    int newScore = score;
    do
    {
        score = newScore;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
            {
                if (valueGrid[i][j] != ownedColor) continue;
                newScore += touching(valueGrid, ownedX, ownedY, i, j, newScore);
            };
        //add call for Update Status Here
        //updateStatus(statePtr);
    }
    while (newScore != score);
    return newScore;
}

void changeGridColor(int** valueGrid, const int ownedColor, const int* ownedX, const int* ownedY, const int score)
{
    for (int i = 0; i < score; i++) valueGrid[ownedX[i]][ownedY[i]] = ownedColor;
}

//initializes the game and seed.
void init_game(int** valueGrid, const int size)
{
    srand(time(NULL));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            valueGrid[i][j] = rand() % 6;
            if (i) if (valueGrid[i][j] == valueGrid[i - 1][j]) valueGrid[i][j] = retryRand(valueGrid[i - 1][j]);
            if (j) if (valueGrid[i][j] == valueGrid[i][j - 1]) j--;
        };
    //makes sure corners are not matching colors
    if(valueGrid[0][0]==valueGrid[size-1][size-1]) retryRand(valueGrid[0][0]);
}

void drawGrid(const int** valueGrid, const int size)
{
    //printing different colors for each possible grid value
    for (int i = 0; i < size; i++)
        for (int k = 0; k < 3; k++)
        {
            //indents the entire grid, need to figure out appropriate value to center
            printf(hfsqr hfsqr hfsqr);
            for (int j = 0; j < size; j++)
                printf("%s" hfsqr RESET, COLORS[valueGrid[i][j]]);
            printf("\n");
        };
}

//get available colors for play by copying colors from src into destination whose size is src-2.

//define half a second in micro seconds.
#define hSECu 500000

int main()
{
    //setbuf(stdout, 0);
    printf("\x1b[0;0H\x1b[2J");
    printf("\t\t"RED " "ti_1"\n\t\t"YELLOW ti_2"\n\t\t"GREEN ti_3"\n\t\t"BLUE ti_4"\n\t\t"MAGENTA ti_5 RESET"\n\n");
    printf("\t\t    "BOLD UNDERLINE "Would you like to play a game?\n"RESET);
    printf("\t\t\t"GREEN BOLD"[y]:Yes\t\t"RED"[n]:No"RESET"\n");
    char b=fgetc(stdin);
    while (b!='y'&&b!='Y'&&b!='N'&&b!='n'){
        printf("\t\t    "BOLD UNDERLINE "Not a valid option, please try again: "RESET);
        //mitigates the buffering of the enter key
        //breaks if user does something like "l    h" which makes stream misaligned.
        fgetc(stdin);
        b=fgetc(stdin);
    }
    //The last bit for 'y' is 1, while for 'n' it's 0 so check if b is y or n by checking the last bit. "Even or Odd"
    *statePtr = b&1;
    const int size = 7;
    //Creating dynamically sized array
    int** valueGrid = malloc(size * sizeof(*valueGrid));
    for (int i = 0; i < size; i++) valueGrid[i] = malloc(size * sizeof(*valueGrid[i]));
    init_game(valueGrid, size);
    int turn = 0;
    int input_color = 0;
    int p1_ownedX[size * size];
    int p1_ownedY[size * size];
    int p2_ownedX[size * size];
    int p2_ownedY[size * size];
    p1_ownedX[0] = 0;
    p1_ownedY[0] = 0;
    p2_ownedX[0] = size-1;
    p2_ownedY[0] = size-1;
    int p1_color = valueGrid[p1_ownedX[0]][p1_ownedY[0]];
    int p2_color = valueGrid[p2_ownedX[0]][p2_ownedY[0]];
    int p1_score = 1;
    int p2_score = 1;
    char availableColors[4];
    while (*statePtr == 1)
    {
        turn++;
        drawGrid(valueGrid, size);
        //not a string, but a char pointer.
        printf("\n\t\t");
        //prints the available options for play
        for(int i = 0; i < 6; i++)
        {
            if(p1_color != i && p2_color != i) printf("%d: %s " RESET"\t", i, COLORS[i]);
        }
        printf("\n");
        do{
          //makes sure the input is valid, retries if not
          scanf("%d",&input_color);
        } while( 
          p1_color == input_color ||
          p2_color == input_color ||
          input_color > 5 ||
          input_color < 0
        );
        if(turn % 2) {
          p1_color = input_color;
          changeGridColor(valueGrid, input_color, p1_ownedX, p1_ownedY, p1_score);
          p1_score = updateOwned(valueGrid, size, input_color, p1_ownedX, p1_ownedY, p1_score);
        }
        else {
          p2_color = input_color;
          changeGridColor(valueGrid, input_color, p2_ownedX, p2_ownedY, p2_score);
          p2_score = updateOwned(valueGrid, size, input_color, p2_ownedX, p2_ownedY, p2_score);
        };
        printf("\x1b[0;0H\x1b[2J");
        if(p1_score+p2_score == size * size) {
          if(p1_score>p2_score) *statePtr = 2;
          else if(p1_score>p2_score) *statePtr = -1;
          else *statePtr = 3;
        };
    }
    switch(*statePtr)
    {
    case 2: printf("PLAYER 1 WINS!!!\n");
    break;
    case -1: printf("PLAYER 2 WINS!!!\n");
    break;
    case 3: printf("ITS A DRAW!!!\n");
    break;
    };
    for (int i = 0; i < size; i++) free(valueGrid[i]);
    free(valueGrid);
    return 0;
}

void updateState(GameState* statePtr,int scoreX,int scoreY)
{

}
