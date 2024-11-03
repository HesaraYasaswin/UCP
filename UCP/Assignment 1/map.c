#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "color.h"

char** intializeMap(int row, int col, int player_row, int player_col, int goal_row, int goal_col) 
{  /* function to create the map*/
    char** map = (char**)malloc(row * sizeof(char*));/* allocate memory*/
    int** colorMap = (int**)malloc(row * sizeof(int*)); /* Allocate memory for colorMap */
    int i, j;

    for (i = 0; i < row; i++) 
    {
        map[i] = (char*)malloc(col * sizeof(char));
        colorMap[i] = (int*)malloc(col * sizeof(int)); 

        for (j = 0; j < col; j++) 
        {
            if (i == player_row && j == player_col) {
                map[i][j] = 'P';
            } else if (i == goal_row && j == goal_col) {
                map[i][j] = 'G';
            } else {
                map[i][j] = ' ';
            }
            colorMap[i][j] = 0; /* Set initial color to 0*/
        }
    }
    return map;
}

void printmp(char** map, int** colorMap, int row, int col) 
{ /* to print the map*/
    int i, j;
    for (j = 0; j < col + 2; j++) {
        printf("*"); /* border lines*/
    }
    printf("\n");

    for (i = 0; i < row; i++) {
        printf("*");             
        for (j = 0; j < col; j++) {
            if (map[i][j] == 'B') {
                if (colorMap[i][j] == 4) {
                    setBackground("blue");
                }
                setCellBackground(map[i][j], colorMap[i][j]);/* cell color*/
                printf("%c", map[i][j]);
                setBackground("reset");
            } else {
                setCellBackground(map[i][j], colorMap[i][j]);/* cell color*/
                printf("%c", map[i][j]);
                setBackground("reset");
            }
        }
        printf("*\n");
    }

    for (j = 0; j < col + 2; j++) {
        printf("*");
    }
    printf("\n");
}

void UpdateTheMap(char** map, int** colorMap, int row, int col, int old_row, int old_col, int n_row, int n_col) 
{  /* function to update the map after every move*/
    if (map[n_row][n_col] == ' ' || map[n_row][n_col] == 'G') 
    {
        map[n_row][n_col] = 'P';
        map[old_row][old_col] = ' ';
        colorMap[n_row][n_col] = 3;  /* player's new position = blue */
        colorMap[old_row][old_col] = 0;  /* player's old position = reset */
    } else if (map[n_row][n_col] == 'B') {
        int push_row = n_row + (n_row - old_row);
        int push_col = n_col + (n_col - old_col);
        if (map[push_row][push_col] == ' ' || map[push_row][push_col] == 'G') {
            if (map[push_row][push_col] == 'G') {
                colorMap[push_row][push_col] = 2; /* Set green color*/
            } else {
                colorMap[push_row][push_col] = 4; /* Set blue color */
            }
            map[push_row][push_col] = 'B';  /* Update box position */
            map[n_row][n_col] = 'P';
            map[old_row][old_col] = ' ';
            colorMap[n_row][n_col] = 3;  /* player's new position = blue */
            colorMap[old_row][old_col] = 0;  /* player's old position = reset */
        } else {
            
            map[n_row][n_col] = 'B';
            map[old_row][old_col] = 'P';
            colorMap[n_row][n_col] = 4;  /* box's new position is set to blue*/
            colorMap[old_row][old_col] = 3;  /* player's new position is set to blue*/
        }
    }

    /* color trial left by B */
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (map[i][j] == 'B') {
                if (colorMap[i][j] > 0) {
                    colorMap[i][j]--; 
                } else {
                    colorMap[i][j] = 4; /* blue color */
                }
            }
        }
    }
}

int validity(char** map, int row, int col, int player_row, int player_col, int move_row, int move_col) 
{   /* function to check if the move is valid*/
    if (move_row < 0 || move_row >= row || move_col < 0 || move_col >= col) {
        return 0;
    }
    if (map[move_row][move_col] == 'O') {
        return 0;
    }
    if (map[move_row][move_col] == ' ' || map[move_row][move_col] == 'G') {
        return 1;
    }
    if (map[move_row][move_col] == 'B') {
        int push_row = move_row + (move_row - player_row);
        int push_col = move_col + (move_col - player_col);
        if (push_row < 0 || push_row >= row || push_col < 0 || push_col >= col) {
            return 0;
        }
        if (map[push_row][push_col] == ' ' || map[push_row][push_col] == 'G') {
            return 1;
        }
    }
   
    if (map[move_row][move_col] == 'P') {
        return 1;
    }
    return 0;
}

void free_map(char** map, int row) 
{  /* to free allocated memory*/
    int i;
    for (i = 0; i < row; i++) 
    {
        free(map[i]);
    }
    free(map);
}

char** loadMap(const char* filename, int* row, int* col, int* player_row, int* player_col) 
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) 
    {
        printf("Failed to open the file.\n");
        return NULL;
    }
    if (fscanf(file, "%d %d", row, col) != 2) 
    {
        printf("Invalid file format.\n");
        fclose(file);
        return NULL;
    }
    char** map = (char**)malloc((*row) * sizeof(char*));
    int i, j;
    for (i = 0; i < *row; i++) 
    {
        map[i] = (char*)malloc((*col) * sizeof(char));
        for (j = 0; j < *col; j++) 
        {
            map[i][j] = ' ';
        }
    }
    int row_idx, col_idx;
    char object;
    while (fscanf(file, "%d %d %c", &row_idx, &col_idx, &object) == 3) {
        if (row_idx >= 0 && row_idx < *row && col_idx >= 0 && col_idx < *col) {
            if (object == 'P') 
            {
                *player_row = row_idx;
                *player_col = col_idx;
            }
            map[row_idx][col_idx] = object;
        }
    }
    fclose(file);
    return map;
}

int** create_colorMap(int row, int col) 
{
    int** colorMap = (int**)malloc(row * sizeof(int*));
    int i, j;
    for (i = 0; i < row; i++) {
        colorMap[i] = (int*)malloc(col * sizeof(int));
        for (j = 0; j < col; j++) {
            colorMap[i][j] = 0; 
        }
    }
    return colorMap;
}

void free_colorMap(int** colorMap, int row) 
{
    int i;
    for (i = 0; i < row; i++) {
        free(colorMap[i]);
    }
    free(colorMap);
}









