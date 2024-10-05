OBJS = src/game.c

#Change compiler here if required
CC = gcc
CXXFLAGS = -Wall -g
OBJ_NAME = mine.out

all :
	$(CC) $(OBJS) -o $(OBJ_NAME) -lm
debug :
	$(CC) -g $(OBJS) -o $(OBJ_NAME) -lm
clean:
	\rm mine.out verbose.txt
verbose:
	$(CC) $(CXXFLAGS) $(OBJS) -o $(OBJ_NAME) -lm >> verbose.txt
