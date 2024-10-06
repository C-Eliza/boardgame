OBJS = src/game.c src/color.h

#Change compiler here if required
CC = gcc
CXXFLAGS = -Wall -g
OBJ_NAME = colorgrid

all :
	$(CC) $(OBJS) -o $(OBJ_NAME) -lm
debug :
	$(CC) -g $(OBJS) -o $(OBJ_NAME) -lm
clean:
	\rm colorgrid

verbose:
	$(CC) $(CXXFLAGS) $(OBJS) -o $(OBJ_NAME) -lm
