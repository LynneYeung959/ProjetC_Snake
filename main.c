/*
* ------------------------ *
|                          |
|   -= main =-             |
|                          |
| based on                 |
| Coding Game Server       |
|                          |
* ------------------------ *

Authors: Liyun YANG
Licence: GPL

File: main.c
	Contains the client API for the Snake game
	-> based on clientAPI.h snakeAPI.h mur.h

Copyright 2019 Liyun YANG
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "snakeAPI.h"
#include "clientAPI.h"
#include "ret_type.h"
#include "movement.h"


int main(int argc, char* argv[]){



  while (1){
    /* 
    *Connection avec le serveur
    *
    *
    *
    *
    *
    */
    int port = strtol(argv[2],NULL,10);
    connectToServer("li2051-215.members.linode.com",port,"Lynne");

    char gameType[]= "RANDOM_PLAYER difficulty=2 timeout=100 seed=123 start=0";
    char gameName[]= "SNAKE";
    int sizeL = 50;
    int sizeH = 120;
    int nbWalls = 100;
    waitForSnakeGame(gameType, gameName, &sizeL, &sizeH, &nbWalls);

    int* walls;
    walls = (int*) malloc (4*(nbWalls*sizeof(int)));

    int player;
    player = getSnakeArena(walls);   /* si player = 0, c'est moi; 1 sinon*/

    printArena();
    int x,y;
    for (int l = 0; (l+1) < 4*nbWalls; l=l+2){
      x = walls[l];   // occuper la coordonnée x de mur
      y = walls[l+1];  // occuper la coordonnée y de mur
      printf(" (%d %d) ", x, y );
      if (x == 11) printf("\n %d \n", walls[l]);
    }


    /* 3 parties
    * 
    *
    *
    *
    *
    */
    int t=0;
    while (t<3){


      /*

      initialisation le tableau de serpent


      */
      int sizeL = 50;
      int sizeH = 120;
      int nbElement =2;
      int snake0[nbElement];
      for (int i = 0; (i + 1)<nbElement; i=i+2){
        snake0[i] = 2;
        snake0[i+1] = (sizeH/2);
      }
      int snake0L = snake0[0]; // la coordonnée horizontale de la tête serpent du player0
      int snake0H = snake0[1]; // la coordonnée verticale de la tête du sepent du player0

      printf("la position initiale de player0 est : (%d,%d)\n",snake0L,snake0H); // affichage de la position initiale du serpent0



      t_return_code bouge0 = NORMAL_MOVE; // le movement de player0; NORMAL_MOVE = 0, WINNING_MOVE = 1, LOOSING_MOVE = -1
      t_return_code bouge1 = NORMAL_MOVE; // le movement de player1
      t_move move = move;// NORTH=0; EAST=1*; SOUTH=2; WEST=3 
      int tour = 0;


      while ((bouge0 == NORMAL_MOVE) && (bouge1 == NORMAL_MOVE)){ // bouge = 0, je commence; bouge = 1, l'autre commence
        
        if (player == 0) {//je commence
          printf("\n Your turn (0: NORTH, 1: EAST, 2:SOUTH, 3:WEST):");
          move = movementSnake(snake0, nbElement, snake0L, snake0H, walls, nbWalls);

          bouge0 = sendMove(move);

          switch(move){
            case NORTH: 
              --snake0H;
              snake0[0] = snake0L;
              snake0[1] = snake0H;
              break;
            case EAST: 
              ++snake0L;
              snake0[0] = snake0L;
              snake0[1] = snake0H;
              break;
            case SOUTH: 
              ++snake0H;
              snake0[0] = snake0L;
              snake0[1] = snake0H;
              break;
            case WEST: 
              --snake0L;
              snake0[0] = snake0L;
              snake0[1] = snake0H;
              break;
          }
          printf("%d %d \n", snake0[0],snake0[1] );
          tour ++ ;

        }
        else if (player == 1){
          printf("\nRandomPlayer's turn");
          bouge1 = getMove(&move);
        }

        if (tour == 10){
          nbElement = nbElement+2;   // ajouter la position de la queue dans le tableau de serpent
          for (int i = 0; i+1 < nbElement ; i++){
            if (snake0[i] == '\0'){
              snake0[i] = snake0H;
              snake0[i-1] = snake0L; 
            }
          }
          tour = 0;
        }



        if (bouge1 == LOOSING_MOVE){
          printf("YOU WIN\n");
          waitForSnakeGame(gameType, gameName, &sizeL, &sizeH, &nbWalls);
          player = getSnakeArena(walls);
          printArena();
          bouge0 = NORMAL_MOVE;
          bouge1 = NORMAL_MOVE;
          t++;
        }
        else if (bouge0 == LOOSING_MOVE){
          printf("YOU LOSE\n");
          waitForSnakeGame(gameType, gameName, &sizeL, &sizeH, &nbWalls);
          player = getSnakeArena(walls);
          printArena();
          bouge0 = NORMAL_MOVE;
          bouge1 = NORMAL_MOVE;
          t++;
        }

        if (t<2){
          printArena();
        }
        player =! player;
      }
      t++;
    }
  free(walls);
  break;
  }
  
  closeConnection();
  return 1;

}
