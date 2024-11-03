/******************************************************
 *Name         : HESARA                               *
 *ID           : 20928386                             *
 *Date         : 28/04/2023                           *
 *Description  :COMP1000, semester 2, Assignment 1    *
 ******************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "terminal.h"

#define MIN_MAP 5

int main (int argc, char *argv[]) {

	int map_row, map_col, player_row, player_col, goal_row, goal_col;
	char **map;   /* a pointer to a pointer of char for the map*/
	int moveRow, moveColm;
	char MOVE;

	srand(time(NULL));  /*seeding the random number generator*/

	/*to accept and ask the user for the six command arguments*/
	if (argc != 7) {
		printf("usage: %s <map_row> <map_col> <player_row> <player_col> <goal_row> <goal_col>\n" , argv [0]);
		return 1;
	}


	map_row = atoi(argv[1]); /* first argument to a integer an assigning it to map_row*/
	map_col = atoi(argv[2]); /* second argument to a integer an assigning it to map_col*/
	player_row = atoi(argv[3]); /* third argument to a integer an assigning it to player_row*/
	player_col = atoi(argv[4]); /* fourth argument to a integer an assigning it to player_col*/
	goal_row =atoi(argv[5]); /* fifth argument to a integer an assigning it to goal_row*/
	goal_col = atoi(argv[6]); /* sixth argument to a integer an assigning it to goal_col*/

	while (goal_row >= map_row || goal_row >= map_col || player_row >= map_row || player_row >= map_col) { 
	     printf("the coordinates given are out of range , the coordinates should be within the map coordinates\n");
	     return 1;
                     
	}

	while (map_row < MIN_MAP || map_col < MIN_MAP) {
		printf("the smallest map must be at least 5x5 %d\n",MIN_MAP);
		return 1;
	}


        
        /* creating a map*/
	map = createmp ( map_row, map_col, player_row, player_col, goal_row, goal_col);

        /* disable the terminal buffer for inputs*/
	disableBuffer();

        /*print the intial map*/
	printf("\033[2J\033[1;1H"); 
	printmp (map,map_row,map_col);


	while (map [goal_col][goal_row] != 'B') { /*till the ball goes inside the goal the loop keeps repeating*/

		MOVE = getchar();


		moveRow = player_row;
		moveColm = player_col;

		switch (MOVE) {
			case 'w': /*moving up*/
			    moveRow--;
			    break;
			case 'a': /*moving left*/
			    moveColm--;
			    break;
			case 's': /*moving down*/
			    moveRow++;
			    break;
			case 'd': /*moving right*/
			    moveColm++;
			    break;

			default:
			    printf("wrong key entered only simplecase wasd acceptable\n");
			    continue;
		}

		if (validity(map, map_row, map_col, player_row, player_col, moveRow, moveColm)) {
                        /*update the map*/
			UpdateTheMap (map, map_row, map_col, player_row, player_col, moveRow, moveColm);


			player_row = moveRow;
			player_col = moveColm;
                        /*to check if the B is inside G*/
			if (map [goal_row] [goal_col] == 'B'){
				printf("\033[2J\033[1;1H"); /*clear the screen*/
				printmp(map, map_row, map_col);
				if (map [goal_row][goal_col] == 'B') {
					printf("congrats, you won the game!\n");
					return 0;
				}
                                
				break;
			}
                        
			printf("\033[2J\033[1;1H");/*clear the screen*/
			printmp(map, map_row, map_col);
			
		}
	}

        /*enable terminal buffering*/
	enableBuffer();
	
        /*releases the memory alloacated*/
	free_memory(map,map_row);

	return 0;
}











