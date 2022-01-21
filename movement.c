/*
* --------------------------- *
|                             |
|   -= movement de snack =-   |
|                             |
| based on                    |
| Coding Game Server          |
|                             |
* --------------------------- *

Authors: Liyun YANG
Licence: GPL

File: movement.c
	Contains the client API for the Snake game
	-> based on clientAPI.h snakeAPI.h ret_type£.h movment.h

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

t_move movementSnake(int snake[], int nbElement, int positionX, int positionY, int muur[], int nbDeMur){
    int x = positionX;
    int y = positionY/10;
    printf("%d\n",nbDeMur );
    printf("%d\n",muur[109*4-1 ] );

    t_moveSnake moveSnake[4] = { nord, //la direction est le nord
                              est,// la direction est l'est 
                              sud,// la direction est le sud
                              ouest// la direction est l'ouest
                              };
 int t = 0;
 while (t < 4){
   t_moveSnake move = moveSnake[t];
   int oui = 0;

   switch (move){
     case(nord):  // si la direction est nord
        --y;
        if ((x > -1) && (x <= 28) && (y > -1) && (y < 13)){  // si le serpent ne vas pas au bord de fenêtre
            int l = 0;
            while (l+1 < (4*nbDeMur-1)){   // vérifier si le serpent entre au mur ou pas
                if (( x == muur[l]) && (y == muur[l+1])){
                    if ((y+1)!= muur[l+3] && ((y+1)!= muur[l-1])){
                        l+=2;
                    }else {
                        t++; break;
                    }  // il va entre au mur, changer la direction suivante
                }else{
                    l+=2;
                }
            }
            if (t == 0){   // si la vérification de mur est bonne 
                oui = 1;   
                int u = 0;
                while( (u +1) < nbElement && (oui==1)){  // vérifier si serpent va craser à lui-même ou pas 
                    if ((x != snake[u]) || (y!= snake[u+1])){
                        u = u + 2;
                    }
                    else {t++; break;}  // serpent va craser à lui-même, changer la direction suivante et sort de switch
                }
                return NORTH; break;  // si la vérification est bonne il vas au nord
            } 
            else break; // si la verification de mur n'est pas bonne, changer la direction suivante
        }else{
            t++; break;
        } // si la serpent va entrer au mur , changer la direction suivante sort la boucle switch


       // même principe que le cas nord
      case (est):
        ++x;
        if ((x > -1) && (x <= 28) && (y > -1) && (y < 13)){
          for (int l = 0; l < (4*nbDeMur-1); l=l+2){
            int murx= muur[l];
            int mury= muur[l+1];
            if ((x== murx) && ( y == mury)){
              if (( x-1 == muur[l-2]) && (x-1 == muur[l+2])){  
                t++; break;
              }
            }
           }
           if (t == 1){
              oui = 1;
                if ( oui == 1){     
                    int u = 0;
                    while( (u +1)< nbElement && ( oui == 1)){
                        if ((x != snake[u]) || (y != snake[u+1])){
                            u = u + 2;
                        }else t++; break;
                    }
                    if (t==1) {return EAST; break;
                    }
                    else {t++; break;}
                }
                else {t++;break;}
            }
            break;
        } else {t++; break;}


       // même principe que le cas nord
      case (sud):
          ++y;
          if ((x > -1) && (x <= 28) && (y > -1) && (y < 13)){
            int l = 0;
            while (l +1 <4*nbDeMur-1){
              if ( x == muur[l] && (y == muur[l+1])){
                if (( y== muur[l-1]) && (y == muur[l+3])){
                  t++; break;
                }
               }
               l = l+2;
            }
            if (t==2) {
              oui = 1;
              if ( oui == 1){
                int u = 0;
                while( (u+1 < nbElement ) && ( oui == 1)){
                    if ((x != snake[u]) || (y != snake[u+1])){
                        u+=2;
                    }else{t++; break;}
                }
               }
               return SOUTH; break;
            }else break;
          }else{t++; break;}



       // même principe que le cas nord
        case(ouest):
            --x;
            if ((x > -1) && (x < 28) && (y > -1) && (y < 13)){
                int l = 0;
                while (l + 1<4*nbDeMur-1){ 
                    if ( (x == muur[l]) && (y == muur[l+1])){
                        if ( (x-1 == muur[l+2]) && (x-1 == muur[l-2])){
                            t=0; break;
                        }
                    }
                    l = l +2;
                }
                if (t==3){
                    oui = 1;
                    int u = 0;
                    while( (u+1 < nbElement) && (oui == 1) ){
                        if ((x != snake[u]) || (y != snake[u+1])){
                            u+=2;
                        }else t=0; break;
                    }
                    return WEST; break;
                }else break;
            }
            t=0; break;
        }

    if (t==3){ // reinitialiser la valeur t pour recommencer d'examiner à partir du cas sud
        t=1;
    }
  }
  t++;
 return EAST;
}
 