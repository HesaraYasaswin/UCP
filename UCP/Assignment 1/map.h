#ifndef MAP_H
#define MAP_H



char** intializeMap(int row, int col, int player_row, int player_col, int goal_row, int goal_col);
void printmp(char** map, int** colorMap, int row, int col);
void UpdateTheMap(char** map, int** colorMap, int row, int col, int old_row, int old_col, int n_row, int n_col);
int validity(char** map, int row, int col, int player_row, int player_col, int move_row, int move_col);
void free_map(char** map, int row);
char** loadMap(const char* filename, int* row, int* col, int* player_row, int* player_col);
int** create_colorMap(int row, int col);
void free_colorMap(int** colorMap, int row);

#endif /* MAP_H */

