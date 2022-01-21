all:prog

prog: main.o movement.o snakeAPI.o clientAPI.o
	gcc -o prog movement.o snakeAPI.o clientAPI.o main.o

movement.o: movement.c
	gcc -c -Wall movement.c
	
snakeAPI.o: snakeAPI.c
	gcc -c -Wall snakeAPI.c

clientAPI.o: clientAPI.c
	gcc -c -Wall clientAPI.c

main.o: main.c
	gcc -c -Wall main.c

clean:
	-rm prog *.o