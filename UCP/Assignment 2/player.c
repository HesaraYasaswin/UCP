#include <stdio.h>
#include <stdlib.h>
#include "player.h"

Player* createPlayer(int row, int col)
{
	Player* player = malloc(sizeof(player));
	if(player == NULL)
	{
		printf("cant alloacte memeory for the player\n");
		exit(1);
	}
	player -> row =row;
	player -> col =col;
	return player;
}


void moveP (Player* player,int row,int col)
{
	player->row = row;
	player->col = col;
}

void deleteP (Player* player)
{
	free(player);
}

void displayP (Player* player)
{
	printf("P at (%d, %d)\n", player->row, player->col);
}
