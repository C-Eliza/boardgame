#include <stdio.h>
#include <stdlib.h>
#include "color.h"
#include "grid.h"
//defines hfsqr so spaces are uniform
#define hfsqr "      "
//defines min macro
#define MIN(a,b) (((a)<(b))?(a):(b))
typedef struct
{
    int ownedX[49];
    int ownedY[49];
    int score;
    int color;
}player;
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

void changeGridColor(int** valueGrid, const int ownedColor, const int* ownedX, const int* ownedY, const int score)
{
    for (int i = 0; i < score; i++) valueGrid[ownedX[i]][ownedY[i]] = ownedColor;
}

void drawGrid(const int** valueGrid, const int size, const int turn)
{
    //print player turn
    printf(hfsqr hfsqr hfsqr hfsqr hfsqr MAGENTA BOLD UNDERLINE"Player %d Turn"RESET"\n\n",(turn-1)%2+1);
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

int main()
{
    printf("\x1b[0;0H\x1b[2J");
    printf("\t\t"RED " "ti_1"\n\t\t"YELLOW ti_2"\n\t\t"GREEN ti_3"\n\t\t"BLUE ti_4"\n\t\t"MAGENTA ti_5 RESET"\n\n");
    printf("\n"tut"\n");
    printf("\t\t    "BOLD UNDERLINE "Would you like to play a game?\n"RESET);
    printf("\t\t\t"GREEN BOLD"[y]:Yes\t\t"RED"[n]:No"RESET"\n");
    char b = fgetc(stdin);
    while (b != 'y' && b != 'Y' && b != 'N' && b != 'n')
    {
        printf("\t\t    "BOLD UNDERLINE "Not a valid option, please try again: "RESET);
        //mitigates the buffering of the enter key
        //breaks if user does something like "l    h" which makes stream misaligned.
        fgetc(stdin);
        b = fgetc(stdin);
    }
    //The last bit for 'y' is 1, while for 'n' it's 0 so check if b is y or n by checking the last bit. "Even or Odd"
    *statePtr = b & 1;
    const int size = 7;
    //Creating dynamically sized array
    int** valueGrid = malloc(size * sizeof(*valueGrid));
    for (int i = 0; i < size; i++) valueGrid[i] = malloc(size * sizeof(*valueGrid[i]));
    init_game(valueGrid, size);
    player players[2];
    int turn = 0;
    int input_color = 0;
    players[0].ownedX[0] = 0;
    players[0].ownedY[0] = 0;
    players[1].ownedX[0] = size-1;
    players[1].ownedY[0] = size-1;
    players[0].color = valueGrid[players[0].ownedX[0]][players[0].ownedY[0]];
    players[1].color = valueGrid[players[1].ownedX[0]][players[1].ownedY[0]];
    players[0].score = 1;
    players[1].score = 1;
    while (*statePtr == 1)
    {
        turn++;
        drawGrid(valueGrid, size, turn);
        //not a string, but a char pointer.
        printf("\n\t\t");
        //prints the available options for play
        for (int i = 0; i < 6; i++){if (players[0].color != i && players[1].color != i) printf("%d: %s " RESET"\t", i, COLORS[i]);}
        printf("\n");
        do
        {
            //makes sure the input is valid, retries if not
            scanf("%d", &input_color);
        }
        while (
            players[0].color == input_color ||
            players[1].color == input_color ||
            input_color > 5 ||
            input_color < 0
        );
        players[(turn+1)%2].color=input_color;
        changeGridColor(valueGrid, input_color, players[(turn+1)%2].ownedX, players[(turn+1)%2].ownedY, players[(turn+1)%2].score);
        players[(turn+1)%2].score = updateOwned(valueGrid, size, input_color, players[(turn+1)%2].ownedX, players[(turn+1)%2].ownedY, players[(turn+1)%2].score);
        if (players[0].score + players[1].score == size * size)
        {
            if (players[0].score > players[1].score) *statePtr = 2;
            else if (players[0].score < players[1].score) *statePtr = -1;
            else *statePtr = 3;
        };
    }
    switch (*statePtr)
    {
    case 2: printf(UNDERLINE GREEN BOLD"PLAYER 1 WINS!!!"RESET"\n");
        break;
    case -1: printf(UNDERLINE RED BOLD"PLAYER 2 WINS!!!"RESET"\n");
        break;
    case 3: printf(UNDERLINE YELLOW BOLD"DRAW"RESET"\n");
        break;
    };
    for (int i = 0; i < size; i++) free(valueGrid[i]);
    free(valueGrid);
    return 0;
}
