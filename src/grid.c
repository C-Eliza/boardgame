#include "grid.h"

#include <stdlib.h>
#include <time.h>
#define abs(x) ((x)>0?(x):-(x))

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
    if (valueGrid[0][0] == valueGrid[size - 1][size - 1]) retryRand(valueGrid[0][0]);
}

int updateOwned(int** valueGrid, const int size, const int ownedColor, int* ownedCordX, int* ownedCordY, int score)
{
    int newScore = score;
    do
    {
        score = newScore;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
            {
                if (valueGrid[i][j] != ownedColor) continue;
                newScore += touching(valueGrid, ownedCordX, ownedCordY, i, j, newScore);
            };
    }
    while (newScore != score);
    return newScore;
}
