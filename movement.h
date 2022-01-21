#ifndef __MOVEMENT__
#define __MOVEMENT__
#include "ret_type.h"

typedef enum 
{
	nord=0,
	est=1,
	sud=2,
	ouest=3,
}t_moveSnake;



t_move movementSnake(int snake[],int nbElement, int positionX, int positionY,int muur[],int nbDeMur);

#endif