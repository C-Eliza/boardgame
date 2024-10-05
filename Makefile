OBJS = src/game.c

#Change compiler here if required
CC = gcc

OBJ_NAME = mine.out

all :
	$(CC) $(OBJS) -o $(OBJ_NAME) -lm
