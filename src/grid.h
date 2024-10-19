//checks if grid squares are touching.
int touching(int** valueGrid, int* ownedX, int* ownedY, const int x, const int y, const int score);

//initializes the game.
void init_game(int** valueGrid, const int size);

//if initialization has duplicates it retries duplicates.
int retryRand(const int i);

//Logic for updating the grid squares after each player action and updating the coordinates
int updateOwned(int** valueGrid, const int size, const int ownedColor, int* ownedCordX, int* ownedCordY, int score);