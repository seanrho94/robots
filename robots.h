#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8
#define MAX_ROBOT 10
#define GETCHAR while (getchar() != '\n')

typedef enum {	
	None = 32, // white space in ASCII
	isHuman = 72, // H in ASCII
	isRobot = 82, // R in ASCII
	isDestroyed = 68, // D in ASCII
	isExit = 69 // E in Ascii
	
}CellState;

typedef enum {
	Empty,
	Human,
	Robot,
	Destroy,
	Exit
}Objects;

typedef struct {
	CellState cellState;
	Objects object;
}Board;

typedef struct {
	int x;
	int y;
	int prevX;
	int prevY;
}Human1;

typedef struct {
	int x;
	int y;
	int destroyed;
}Robot1;

void printBoard(Board board[BOARD_HEIGHT][BOARD_WIDTH]);

void initialiseBoard(Board board[BOARD_HEIGHT][BOARD_WIDTH]);

int checkCoordinates(int y, int x);

int checkNumberOfRobots(int numberOfRobots);

int checkHumanExitCollision(Board board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x);

int checkRobotCollision(Board board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x);

int checkRobotExitCollision(Board board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x);

int checkRobotDistance(Board board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, Human1 *human);

void placeExit(Board board[BOARD_HEIGHT][BOARD_WIDTH], int seedY, int seedX);

void placeHuman(Board board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, Human1 *human);

void placeRobot(Board board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, Human1 *human);

void addRobotList(int y, int x, int numberOfRobots, int cursor, Robot1 robot[MAX_ROBOT]);

void moveNT(Board board[BOARD_HEIGHT][BOARD_WIDTH], Human1 *human, int *playerWon);

void moveST(Board board[BOARD_HEIGHT][BOARD_WIDTH], Human1 *human, int *playerWon);

void moveWT(Board board[BOARD_HEIGHT][BOARD_WIDTH], Human1 *human, int *playerWon);

void moveET(Board board[BOARD_HEIGHT][BOARD_WIDTH], Human1 *human, int *playerWon);

void moveRobot(Board board[BOARD_HEIGHT][BOARD_WIDTH], Human1 *human, Robot1 robot[MAX_ROBOT], int numberOfRobots, int *playerWon);

void playerConfiguration(Board board[BOARD_HEIGHT][BOARD_WIDTH], int seed);