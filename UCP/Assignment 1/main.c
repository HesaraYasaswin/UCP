/******************************************************
 *Name         : HESARA                               *
 *ID           : 20928386                             *
 *Date         : 31/05/2023                           *
 *Description  :COMP1000, semester 1, Assignment 2    *
 ******************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "terminal.h"
#include "linkedlist.h"
#include "color.h"

LinkedList* storemove; /*linked list to store moves*/


int main(int argc, char* argv[]) 
{
    int map_row, map_col, player_row, player_col, box_row, box_col;
    int goal_row, goal_col;
    char** map;  /* 2D array to store the map*/
    int** colorMap; /* for storing cell colors*/
    char move;
    int previous_playerrow, previous_playercol; /*to store previous player position */
    int previous_boxrow, previous_boxcol;
    int previous_pushrow = -1, previous_pushcol = -1; /*to store previous push position */
    int undo = 1; /* to indicate whether UNDO is enabled */
    srand(time(NULL));

    if (argc != 2) 
    {   /* command line argumnet*/
        printf("Usage: %s <map_file_name>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r"); /* open the map file*/
    if (file == NULL) 
    {
        printf("Error: Could not open file\n");
        return 1;
    }

    fscanf(file, "%d %d\n", &map_row, &map_col); /* read the file*/
    map = loadMap(argv[1], &map_row, &map_col, &player_row, &player_col);
    colorMap = create_colorMap(map_row, map_col); /* create color map*/
    fclose(file);

    disableBuffer();/* disable buffering*/
    printf("\033[2J\033[1;1H");/* clear terminal screen*/
    printmp(map, colorMap, map_row, map_col);
    storemove = createLinkedList(); 

    
    int i, j;
    for (i = 0; i < map_row; i++) 
    {  /* to find the initial position of B and G*/
        for (j = 0; j < map_col; j++) 
        {
            if (map[i][j] == 'B') 
            {
                box_row = i;
                box_col = j;
            } else if (map[i][j] == 'G') 
            {
                goal_row = i;
                goal_col = j;
            }
        }
    }

    Move* initMove = (Move*)malloc(sizeof(Move));
    initMove->player_row = player_row;
    initMove->player_col = player_col;
    initMove->box_row = box_row;
    initMove->box_col = box_col;
    initMove->previous_pushrow = -1;
    initMove->previous_pushcol = -1;
    insertFirst(storemove, initMove); /* Insert initial move into the linked list */

    while (!(box_row == goal_row && box_col == goal_col)) 
    {
        move = getchar();

        if (move == 'u' && undo) { /* undo feature is implemented here*/
            if (!isEmpty(storemove)) {
                Move* prevMove = (Move*)getFirst(storemove);
                previous_playerrow = prevMove->player_row;
                previous_playercol = prevMove->player_col;
                previous_boxrow = prevMove->box_row;
                previous_boxcol = prevMove->box_col;
                previous_pushrow = prevMove->previous_pushrow;
                previous_pushcol = prevMove->previous_pushcol;

                map[player_row][player_col] = ' ';
                map[box_row][box_col] = ' ';

                player_row = previous_playerrow;
                player_col = previous_playercol;
                box_row = previous_boxrow;
                box_col = previous_boxcol;

                map[player_row][player_col] = 'P';
                map[box_row][box_col] = 'B';

                if (previous_pushrow != -1 && previous_pushcol != -1) {
                    map[previous_pushrow][previous_pushcol] = 'P';
                }

                deleteFirst(storemove);
            }

            printf("\033[2J\033[1;1H");
            printmp(map, colorMap, map_row, map_col); 
            continue;
        }

        previous_playerrow = player_row;
        previous_playercol = player_col;
        previous_boxrow = box_row;
        previous_boxcol = box_col;

        switch (move) 
        {
            case 'w': 
                if (map[player_row - 1][player_col] != '#' && map[player_row - 1][player_col] != 'O') {
                    if (player_row - 1 == box_row && player_col == box_col) {
                        if (map[box_row - 1][box_col] == ' ' || map[box_row - 1][box_col] == '.' || map[box_row - 1][box_col] == 'G') {
                            map[player_row][player_col] = ' ';
                            if (map[box_row - 1][box_col] == 'G') {
                                map[box_row][box_col] = 'G';
                            } else {
                                map[box_row][box_col] = ' ';
                            }
                            player_row--;
                            box_row--;
                            map[player_row][player_col] = 'P';
                            map[box_row][box_col] = 'B';
                            previous_pushrow = box_row + 1;
                            previous_pushcol = box_col;
                        }
                    } else {
                        map[player_row][player_col] = ' ';
                        player_row--;
                        map[player_row][player_col] = 'P';
                        previous_pushrow = -1;
                        previous_pushcol = -1;
                    }
                }
                break;

            case 's': 
                if (map[player_row + 1][player_col] != '#' && map[player_row + 1][player_col] != 'O') {
                    if (player_row + 1 == box_row && player_col == box_col) {
                        if (map[box_row + 1][box_col] == ' ' || map[box_row + 1][box_col] == '.' || map[box_row + 1][box_col] == 'G') {
                            map[player_row][player_col] = ' ';
                            if (map[box_row + 1][box_col] == 'G') {
                                map[box_row][box_col] = 'G';
                            } else {
                                map[box_row][box_col] = ' ';
                            }
                            player_row++;
                            box_row++;
                            map[player_row][player_col] = 'P';
                            map[box_row][box_col] = 'B';
                            previous_pushrow = box_row - 1;
                            previous_pushcol = box_col;
                        }
                    } else {
                        map[player_row][player_col] = ' ';
                        player_row++;
                        map[player_row][player_col] = 'P';
                        previous_pushrow = -1;
                        previous_pushcol = -1;
                    }
                }
                break;

            case 'a':
                if (map[player_row][player_col - 1] != '#' && map[player_row][player_col - 1] != 'O') {
                    if (player_row == box_row && player_col - 1 == box_col) {
                        if (map[box_row][box_col - 1] == ' ' || map[box_row][box_col - 1] == '.' || map[box_row][box_col - 1] == 'G') {
                            map[player_row][player_col] = ' ';
                            if (map[box_row][box_col - 1] == 'G') {
                                map[box_row][box_col] = 'G';
                            } else {
                                map[box_row][box_col] = ' ';
                            }
                            player_col--;
                            box_col--;
                            map[player_row][player_col] = 'P';
                            map[box_row][box_col] = 'B';
                            previous_pushrow = box_row;
                            previous_pushcol = box_col + 1;
                        }
                    } else {
                        map[player_row][player_col] = ' ';
                        player_col--;
                        map[player_row][player_col] = 'P';
                        previous_pushrow = -1;
                        previous_pushcol = -1;
                    }
                }
                break;

            case 'd': 
                if (map[player_row][player_col + 1] != '#' && map[player_row][player_col + 1] != 'O') {
                    if (player_row == box_row && player_col + 1 == box_col) {
                        if (map[box_row][box_col + 1] == ' ' || map[box_row][box_col + 1] == '.' || map[box_row][box_col + 1] == 'G') {
                            map[player_row][player_col] = ' ';
                            if (map[box_row][box_col + 1] == 'G') {
                                map[box_row][box_col] = 'G';
                            } else {
                                map[box_row][box_col] = ' ';
                            }
                            player_col++;
                            box_col++;
                            map[player_row][player_col] = 'P';
                            map[box_row][box_col] = 'B';
                            previous_pushrow = box_row;
                            previous_pushcol = box_col - 1;
                        }
                    } else {
                        map[player_row][player_col] = ' ';
                        player_col++;
                        map[player_row][player_col] = 'P';
                        previous_pushrow = -1;
                        previous_pushcol = -1;
                    }
                }
                break;
        }

        if (previous_playerrow != player_row || previous_playercol != player_col || previous_pushrow != -1 || previous_pushcol != -1) 
        {
            Move* currentMove = (Move*)malloc(sizeof(Move));
            currentMove->player_row = player_row;
            currentMove->player_col = player_col;
            currentMove->box_row = box_row;
            currentMove->box_col = box_col;
            currentMove->previous_pushrow = previous_pushrow;
            currentMove->previous_pushcol = previous_pushcol;
            insertFirst(storemove, currentMove);
        }

        printf("\033[2J\033[1;1H");
        printmp(map, colorMap, map_row, map_col); 
    }

    enableBuffer(); /* enable buffering*/
    printf("\nCongratulations! You won the game.\n");

    free_map(map, map_row); /* Free memory for map */
    free_colorMap(colorMap, map_row); /* Free memory for color map */
    freeLinkedList(storemove); /* Free memory for movement history linked list */

    return 0;
}

