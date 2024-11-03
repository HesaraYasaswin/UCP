#ifndef PLAYER_H
#define PLAYER_H


typedef struct {
	int row;
	int col;
} Player;

Player* createPlayer(int row,int col);

void moveP (Player* player, int row, int col);
void deleteP (Player* player);
void displayP (Player* player);

#endif 
