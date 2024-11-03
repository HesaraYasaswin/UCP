#ifndef MAP_H
#define MAP_H

#define MIN_MAP 5
#define GOAL 'G'
#define BOX 'B'
#define PLAYER 'P'
#define WALL '*'
#define EMPTY ' '
#define INGOAL 'B'
#define PULL 1

void initialmap (char** map, int map_row, int map_col, int player_row, int player_col, int goal_row, int goal_col);

char** createmp(int map_row, int map_col, int player_row, int player_col, int goal_row, int goal_col);

void printmp (char **map,int map_row, int map_col);

int validity(char **map, int map_row, int map_col, int player_row, int player_col, int moveRow, int moveColm);

void UpdateTheMap (char** map, int map_row, int map_col, int player_row, int player_col, int moveRow, int moveColm);

void free_memory(char **map, int map_row);

#endif
