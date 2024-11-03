#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "map.h"
#include "random.h"
#include "color.h"


void initialmap (char** map, int map_row, int map_col, int player_row, int player_col, int goal_row, int goal_col) {
	int i,j;
        i = 0;
        
        do {
		map[i] = malloc(map_col * sizeof(char));  /*allocates memeory for each row*/

		j = 0;

		do {
			if ( i == 0 || i == map_row -1 || j == 0 || j == map_col -1 ) {
				map[i][j] = '*';  /*if cell is on the end of the map dimensions,set it as a WALL*/
			} else if (i == player_row && j == player_col) {
				map[i][j] ='P';  /*if the cell is Player ,set it as P*/
			} else if (i == goal_row && j == goal_col) {
				map[i][j] ='G';  /*if the cell is in goal, set it as G*/
			} else {
				map[i][j] =' ';  /*empty cell*/
			}
			j++;
		} while (j < map_col);

		i++;
	} while (i < map_row);
}



char** createmp(int map_row, int map_col, int player_row, int player_col, int goal_row, int goal_col)
{
	int i;
        int Brow, Bcol;
        /*allocates memory for map*/
	char **map = malloc(map_row * sizeof(char*));

        for (i = 0; i < map_row; i++) {
           map[i] = malloc(map_col * sizeof(char));
        }


	initialmap (map, map_row, map_col, player_row, player_col, goal_row, goal_col);
        
        do {
                /*box position is randomize using randomUCP*/
                Brow = randomUCP(1, map_row -2);
		Bcol = randomUCP(1, map_col -2);
	} while ((Brow == player_row && Bcol == player_col) || (Brow == goal_row && Bcol == goal_col));
	
	/*enters the B to the map*/
	map[Brow][Bcol] = 'B';

	return map;

}

void printmp (char **map, int map_row, int map_col) {
    int i, j;

    /* Loop through each row*/
    for (i = 0; i < map_row; i++) {
        /* Loop through each column in the current row*/
        for (j = 0; j < map_col; j++) {
            char cell = map[i][j];

            /* Check if current cell is a goal*/
            if (cell == 'G') {
                /* Check if a box is on the goal*/
                if (j > 0 && map[i][j-1] == 'B' && map[i][j-1] != 'G') {
                    CELL('G', 1);  /* Green background for box on goal*/
                } else {
                    CELL(cell, 0);  /* Red background for goal without box*/
                }
            } 
            /* Check if the cell position is in the box*/
            else if (cell == 'B') {
                
                if ((j > 0 && map[i][j-1] == 'G') || (j < map_col-1 && map[i][j+1] == 'G')) {
                    CELL('G', 1);  /* Green background*/
                } else {
                    CELL(' ', 0);  /* Reset background*/
                }
            } 
            /* Reset background*/
            else {
                CELL(' ', 0);
            }

            
            printf("%c ", cell);
        }

        /* Print newline*/
        printf("\n");
    }
}

                
                


int validity(char **map, int map_row, int map_col, int player_row, int player_col, int moveRow, int moveColm) {

		
       /*check if out of bounds*/

	if(moveRow < 0 || moveRow >= map_row || moveColm < 0 || moveColm >= map_col)
	{
		return 0;
        /*check if it hits a ("*")*/
	} else if (map[moveRow][moveColm] == '*')
	{
		return 0;
	} else if (map[moveRow][moveColm] == 'B')
	{
	        /*to calculate the new position of the box*/
		int Brow = 2 * moveRow - player_row;
		int Bcol = 2 * moveColm - player_col;

                /*bound checking for box*/
		if (Brow < 0 || Brow >= map_row || Bcol < 0 || Bcol >= map_col)
		{
			return 0;
		} else if (map[Brow][Bcol] == '*' || map[Brow][Bcol] == 'B')
		{
			return 0;
		} else { /*if it is valid,the box moves*/
			return 1;
		}
	
	} else { 
	    return 1;
	}
}


		          
		      


void UpdateTheMap(char** map, int map_row, int map_col, int player_row, int player_col, int moveRow, int moveColm) {
   char MOVES, push;
   int Brow,Bcol;
   
   /*check for bounds*/
   if (moveRow < 0 || moveRow >= map_row || moveColm < 0 || moveColm >= map_col) {
       return;
   }
   
   MOVES = map[moveRow][moveColm];
   
   switch (MOVES) {
      case EMPTY: {
          /*update the map according to the player's movement*/
          map[player_row][player_col] = EMPTY;
          player_row = moveRow;
          player_col = moveColm;
          map[player_row][player_col] = PLAYER;
          break;
      }
      case BOX: {
          Brow = moveRow + ( moveRow - player_row);
          Bcol = moveColm + ( moveColm - player_col);
          
          push = map[Brow][Bcol];
          
          if ( Brow < 0 || Brow >= map_row || Bcol < 0 || Bcol >=map_col) {
             return;
          }
                    
          
          if (push == EMPTY || push == GOAL) {
              map[player_row][player_col] = EMPTY;
              /*check if box is in goal*/
              if (push == GOAL) {
                 map[moveRow][moveColm] = INGOAL;
              
              } else {
                 map[moveRow][moveColm] = EMPTY;
              }
              
              map[Brow][Bcol] = BOX;
              player_row = moveRow;
              player_col = moveColm;
              map[player_row][player_col] = PLAYER;
	  
	  }
          break;
		} 
      default: {
		       return;
	       }
   
   }
}

#ifdef PULL
/*to handle the pull logic*/

        
#endif

void free_memory(char **map, int map_row)
{
	int i;
	
	do {
		free(map[i]);
	} while (((i = 0 ) && i < map_row) && (i++));
	/*free the memory allocated for map*/
	free(map);
}


				
