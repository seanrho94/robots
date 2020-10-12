#include "robots.h"

void printBoard(Board board[BOARD_HEIGHT][BOARD_WIDTH]){	
	for(int i =0; i < BOARD_HEIGHT; i++){
			printf("|");
		for(int j =0; j < BOARD_WIDTH; j++){
			printf("%c|", board[i][j].cellState);
		}
		printf("\n");
	}
}

void initialiseBoard(Board board[BOARD_HEIGHT][BOARD_WIDTH]){
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			board[i][j].cellState = None;
		}
	}
}

int checkCoordinates(int y, int x){
	int isValidCoordinates;
	if((x>= 0 && x< 8) && (y>= 0 && y< 8)){ // Check inputs [1-7][1-7].
		isValidCoordinates = 1;
	} else {
		isValidCoordinates = 0;
	}
	
	return isValidCoordinates;
}

int checkNumberOfRobots(int numberOfRobots){ //check the input for number of robots during the setup.
	int isValidNumber;
	numberOfRobots-= 48; // Convert Char into Int ('1' = 49).
	if(numberOfRobots >= 1 && numberOfRobots <= 7){
		isValidNumber = 1;
	} else {
		isValidNumber = 0;
	}
	
	return isValidNumber;
}

int checkHumanExitCollision(Board board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x){ // checks if there is a collision between human and exit during the placement setup.
	int checkCollision = 1;
	if(board[y][x].cellState == isExit){
		checkCollision = 0;
	}
	return checkCollision;
}

int checkRobotCollision(Board board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x){ // checks if there is a collision between robot and robot during the placement setup.
	int checkRobotCollision = 1;
	if(board[y][x].cellState == isRobot){
		checkRobotCollision = 0;
	}
	return checkRobotCollision;
}

int checkRobotExitCollision(Board board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x){ // checks if there is a collision between robot and exit during the placement setup.
	int checkRobotExitCollision = 1;
	if(board[y][x].cellState == isExit){
		checkRobotExitCollision = 0;
	}
	return checkRobotExitCollision;
}

int checkRobotDistance(Board board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, Human1 *human){ // check again. work from here.
	int isValidDistance = 0; // 1 if valid to locate robot
	int xTemp = abs((x) - (human->x));
	int yTemp = abs((y) - (human->y));
	int total = xTemp + yTemp;
	
	if(yTemp > 2 || xTemp > 2){
		isValidDistance = 1;
	}else if(total >= 4){
		if(xTemp == yTemp){
			isValidDistance = 1;
		}
	}else {
		isValidDistance = 0;
	} 
	
	return isValidDistance;
}

void placeExit(Board board[BOARD_HEIGHT][BOARD_WIDTH], int seedY, int seedX){
	board[seedY][seedX].cellState = isExit;
	board[seedY][seedX].object = Exit;
}

void placeHuman(Board board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, Human1 *human){
	int isValidCoordinates = checkCoordinates(y, x);
	int checkCollisionExit = checkHumanExitCollision(board, y ,x);
	if(isValidCoordinates == 1 && checkCollisionExit == 1 ){
		board[y][x].cellState = isHuman;
		human->x = x;
		human->y = y;
		board[y][x].object = Human;
	}else{
		printf("Invalid Coordinates, Try again\n");
	}
}

void placeRobot(Board board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, Human1 *human){
	int isValidCoordinates = checkCoordinates(y, x);
	int testRobotCollision = checkRobotCollision(board, y, x);
	int testRobotExitCollision = checkRobotExitCollision(board, y,x);
	int isValidDistance = checkRobotDistance(board, y, x, human);

	if(isValidCoordinates == 1 && testRobotCollision == 1 && testRobotExitCollision == 1 && isValidDistance == 1){
		board[y][x].cellState = isRobot;
		board[y][x].object = Robot;
	}
	
	if(isValidCoordinates == 0 || testRobotCollision == 0 || testRobotExitCollision == 0 || isValidDistance == 0){
		printf("Invalid Coordinates, Try again\n");
	}
}

void addRobotList(int y, int x, int numberOfRobots, int cursor, Robot1 robot[MAX_ROBOT]){
	numberOfRobots-= 48; // Convert Char into Int ('1' = 49)
	cursor -= 1;
	robot[cursor].x = x;
	robot[cursor].y = y;
	robot[cursor].destroyed = 0;
}


void moveNT(Board board[BOARD_HEIGHT][BOARD_WIDTH], Human1 *human, int *playerWon){
	if(human->y - 1 >=0 ){ // if it is in bound.
		board[human->y][human->x].cellState = None;
		board[human->y][human->x].object = Empty;
		human->prevX = human->x;
		human->prevY = human->y;
		human->y -= 1;
		if(board[human->y][human->x].object == Exit){
			printf("Well done! You survived, but it isn't over!\n");
			printf("\n");
			printf("\n");
			*playerWon = 1;
		}else{
			board[human->y][human->x].cellState = isHuman;
			board[human->y][human->x].object = Human;
		}
	}else{
		printf("Invalid\n");
	}
}

void moveST(Board board[BOARD_HEIGHT][BOARD_WIDTH], Human1 *human, int *playerWon){
	if(human->y + 1 <= 7 ){ // if it is in bound.
		board[human->y][human->x].cellState = None;
		board[human->y][human->x].object = Empty;
		human->prevX = human->x;
		human->prevY = human->y;
		human->y += 1;
		if(board[human->y][human->x].object == Exit){
			printf("Well done! You survived, but it isn't over!\n");
			printf("\n");
			printf("\n");
			*playerWon = 1;
		}else{
			board[human->y][human->x].cellState = isHuman;
			board[human->y][human->x].object = Human;
		}
	}else{
		printf("Invalid\n");
	}
}

void moveWT(Board board[BOARD_HEIGHT][BOARD_WIDTH], Human1 *human, int *playerWon){
	if(human->x - 1 >=0 ){ // if it is in bound.
		board[human->y][human->x].cellState = None;
		board[human->y][human->x].object = Empty;
		human->prevX = human->x;
		human->prevY = human->y;
		human->x -= 1;
		if(board[human->y][human->x].object == Exit){
			printf("Well done! You survived, but it isn't over!\n");
			printf("\n");
			printf("\n");
			*playerWon = 1;
		}else{
			board[human->y][human->x].cellState = isHuman;
			board[human->y][human->x].object = Human;
		}
	}else{
		printf("Invalid\n");
	}
}

void moveET(Board board[BOARD_HEIGHT][BOARD_WIDTH], Human1 *human, int *playerWon){
	if(human->x + 1 <= 7 ){ // if it is in bound.
		board[human->y][human->x].cellState = None;
		board[human->y][human->x].object = Empty;
		human->prevX = human->x;
		human->prevY = human->y;
		human->x += 1;
		if(board[human->y][human->x].object == Exit){
			printf("Well done! You survived, but it isn't over!\n");
			printf("\n");
			printf("\n");
			*playerWon = 1;
		}else{
			board[human->y][human->x].cellState = isHuman;
			board[human->y][human->x].object = Human;
		}
	}else{
		printf("Invalid\n");
	}
}

void moveRobot(Board board[BOARD_HEIGHT][BOARD_WIDTH], Human1 *human, Robot1 robot[MAX_ROBOT], int numberOfRobots, int *playerWon){
	numberOfRobots-= 48; // Convert Char into Int ('1' = 49)
	int xTemp;
	int yTemp;
	int diffX;
	int diffY;
	
	for(int i = 0; i < numberOfRobots; i++){
		xTemp = abs((human->x) - (robot[i].x));
		yTemp = abs((human->y) - (robot[i].y));
		diffX = human->x - robot[i].x;
		diffY = human->y - robot[i].y;
		
		if(xTemp > yTemp && diffX < 0 && robot[i].destroyed == 0){
			board[robot[i].y][robot[i].x].cellState = None;
			board[robot[i].y][robot[i].x].object = Empty;
			if(board[robot[i].y][robot[i].x-1].object == Human){
				printf("The robots got you! We are doomed!\n");
				printf("\n");
				*playerWon = 1;
			}
			if(board[robot[i].y][robot[i].x-1].object == Robot){
				board[robot[i].y][robot[i].x-1].object = Destroy;
				board[robot[i].y][robot[i].x-1].cellState = isDestroyed;
				robot[i].destroyed = 1;
			}else{
				board[robot[i].y][robot[i].x-1].cellState = isRobot;
				board[robot[i].y][robot[i].x-1].object = Robot;
				robot[i].x -= 1;
			}
		}
		if(xTemp > yTemp && diffX >= 0 && robot[i].destroyed == 0){
			board[robot[i].y][robot[i].x].cellState = None;
			board[robot[i].y][robot[i].x].object = Empty;
			if(board[robot[i].y][robot[i].x+1].object == Human){
				printf("The robots got you! We are doomed!\n");
				printf("\n");
				*playerWon = 1;
			}
			if(board[robot[i].y][robot[i].x+1].object == Robot){
				board[robot[i].y][robot[i].x+1].object = Destroy;
				board[robot[i].y][robot[i].x+1].cellState = isDestroyed;
				robot[i].destroyed = 1;
			}else{
				board[robot[i].y][robot[i].x+1].cellState = isRobot;
				board[robot[i].y][robot[i].x+1].object = Robot;
				robot[i].x += 1;
			}
		}
		if(xTemp < yTemp && diffY < 0 && robot[i].destroyed == 0){
			board[robot[i].y][robot[i].x].cellState = None;
			board[robot[i].y][robot[i].x].object = Empty;
			if(board[robot[i].y-1][robot[i].x].object == Human){
				printf("The robots got you! We are doomed!\n");
				printf("\n");
				*playerWon = 1;
			}
			if(board[robot[i].y-1][robot[i].x].object == Robot){
				board[robot[i].y-1][robot[i].x].object = Destroy;
				board[robot[i].y-1][robot[i].x].cellState = isDestroyed;
				robot[i].destroyed = 1;
			}else{
				board[robot[i].y-1][robot[i].x].cellState = isRobot;
				board[robot[i].y-1][robot[i].x].object = Robot;
				robot[i].y -= 1;
			}
		}
		if(xTemp < yTemp && diffY >=0 && robot[i].destroyed == 0){
			board[robot[i].y][robot[i].x].cellState = None;
			board[robot[i].y][robot[i].x].object = Empty;
			if(board[robot[i].y+1][robot[i].x].object == Human){
				printf("The robots got you! We are doomed!\n");
				printf("\n");
				*playerWon = 1;
			}
			if(board[robot[i].y+1][robot[i].x].object == Robot){
				board[robot[i].y+1][robot[i].x].object = Destroy;
				board[robot[i].y+1][robot[i].x].cellState = isDestroyed;
				robot[i].destroyed = 1;
			}else{
				board[robot[i].y+1][robot[i].x].cellState = isRobot;
				board[robot[i].y+1][robot[i].x].object = Robot;
				robot[i].y += 1;
			}
		}
	}
}


void playerConfiguration(Board board[BOARD_HEIGHT][BOARD_WIDTH], int seed){
	int exit = 0;
	srand((unsigned)seed);
	while(exit != 1){
	int seedX = rand() % 8;	// order of seed X and Y matters
	int seedY = rand() % 8;	// order of seed X and Y matters
	initialiseBoard(board);
	int cont = 0;
	int cursor = 0;
	int y = 8; // Initial value is 8 to ignore every char value as coordinates. Too see the difference, leave it as uninitialised.
	int x = 8; // Initial value is 8 to ignore every char value as coordinates. Too see the difference, leave it as uninitialised.
	char numberOfRobots;
	int isValidCoordinates, checkCollisionExit, isNoOfRobotsValid, testRobotCollision, testRobotExitCollision, isValidDistance;

	
	char command[20];
    char firstCommand[9];
	char secondCommand[4];
    int displayCommand, exitCommand, moveCommand, northCommand, southCommand, westCommand, eastCommand, totalRead;
	
	Human1 human;
	Robot1 robot[MAX_ROBOT];
	placeExit(board, seedY, seedX); // place exit first.
	
	while(cont != 1){
		printf("Human starting point: ");
		scanf("%d %d", &x, &y);
		GETCHAR; // A defined macro that fixes the issue(prints error meesage twice after using scanf).
		isValidCoordinates = checkCoordinates(y,x);
		checkCollisionExit = checkHumanExitCollision(board, y, x);
		
		if(isValidCoordinates == 1 && checkCollisionExit == 1){
			cont = 1;
		}
		placeHuman(board, y, x, &human);
		
	}
	cont = 0;
	
	while(cont!= 1){
		printf("Number of robots: ");
		scanf("%c", &numberOfRobots);
		GETCHAR;
		isNoOfRobotsValid = checkNumberOfRobots(numberOfRobots);
		if(isNoOfRobotsValid == 1){ // Input must be 1~62. Characters are not allowed. Negatvie values are not allowed. 0 is not allowed. Currently only checks 1~9.
			cont = 1;
		}else {
			printf("Invalid number, Try again\n");
		}
	}
	cont = 0;
	while(cont!= 1){
		for(cursor; cursor <=numberOfRobots-49;){
			y = 8; // Initial value is 8 to ignore every char value as coordinates. Too see the difference, leave it as uninitialised.
			x = 8; // Initial value is 8 to ignore every char value as coordinates. Too see the difference, leave it as uninitialised.
			printf("Robot %d: ", cursor+1);
			scanf("%d %d", &x, &y);
			GETCHAR; // A defined macro that fixes the issue(prints error meesage twice after using scanf).
			isValidCoordinates = 0;
			testRobotCollision = 0;
			testRobotExitCollision = 0;
			isValidDistance = 0;
			isValidCoordinates = checkCoordinates(y, x);
			testRobotCollision = checkRobotCollision(board, y, x);
			testRobotExitCollision = checkRobotExitCollision(board, y,x);
			isValidDistance = checkRobotDistance(board, y, x, &human);
			placeRobot(board, y, x, &human); // if inputs are negative or  out of 0-7, then ask user input again. Before the IF statement to print error message first. 
			if(isValidCoordinates == 1 && testRobotCollision == 1 && testRobotExitCollision == 1 && isValidDistance == 1){
				cursor++; //move the cursor to next if the program successfully read the input. Otherwise, ask input again (since the cursor will not move).
				addRobotList(y, x, numberOfRobots, cursor, robot);
			} 
		}
		cont = 1;
	}
	cont = 0;
	cursor = 0;
	
	printf("\n");
	
	int playerWon = 0;
	
	while(playerWon != 1){
        fgets(command, 20, stdin);
        totalRead = sscanf(command, "%s %s", firstCommand, secondCommand);
		displayCommand=strcmp(firstCommand, "display");
		exitCommand=strcmp(firstCommand, "exit");
		moveCommand=strcmp(firstCommand, "move");
		northCommand=strcmp(secondCommand, "NT");
		southCommand=strcmp(secondCommand, "ST");
		westCommand=strcmp(secondCommand, "WT");
		eastCommand=strcmp(secondCommand, "ET");
			
		if(displayCommand == 0 && totalRead == 1){
			printf("\n");
			printBoard(board);
			printf("\n");
		}
        if(exitCommand == 0 && totalRead == 1){
        	exit = 1;
			break;
		}
		if(moveCommand == 0 && northCommand == 0 && totalRead == 2){
			printf("\n");
			moveNT(board, &human, &playerWon);
			moveRobot(board, &human, robot, numberOfRobots, &playerWon);
		}
		if(moveCommand == 0 && southCommand == 0 && totalRead == 2){
			printf("\n");
			moveST(board, &human, &playerWon);
			moveRobot(board, &human, robot, numberOfRobots, &playerWon);
		}
		if(moveCommand == 0 && westCommand == 0 && totalRead == 2){
			printf("\n");
			moveWT(board, &human, &playerWon);
			moveRobot(board, &human, robot, numberOfRobots, &playerWon);
		}
		if(moveCommand == 0 && eastCommand == 0 && totalRead == 2){
			printf("\n");
			moveET(board, &human, &playerWon);
			moveRobot(board, &human, robot, numberOfRobots, &playerWon);
		}
		if(exitCommand != 0 && (displayCommand !=0 || (displayCommand == 0 && totalRead > 1)) && (moveCommand !=0 || (moveCommand == 0 && totalRead < 2))){
			printf("Invalid\n");
		}else if((moveCommand == 0 && northCommand !=0) && (moveCommand == 0 && southCommand !=0) && (moveCommand == 0 && westCommand !=0) && (moveCommand == 0 && eastCommand !=0)){
			printf("Invalid\n");
		}
	}
	playerWon = 0;
	}
}

int main(int argc, char **argv){
	Board playerBoard[BOARD_HEIGHT][BOARD_WIDTH];
	int seed;
	char *seedPtr;
	seed = strtol(argv[1], &seedPtr, 10); // get a number from command line and change to string to int.

	
	playerConfiguration(playerBoard, seed);

}