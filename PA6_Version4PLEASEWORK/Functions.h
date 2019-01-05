
#pragma once

typedef struct ShipLocations {
	int carrierColumns[5];
	int carrierRows[5];
	int isCarrierHorizontal;
	int battleshipColumns[8];
	int battleshipRows[8];
	int isBattleshipHorizontal;
	int cruiserColumns[6];
	int cruiserRows[6];
	int isCruiserHorizontal;
	int submarineColumns[6];
	int submarineRows[6];
	int isSubmarineHorizontal;
	int destroyerColumns[4];
	int destroyerRows[4];
	int isDestroyerHorizontal;
}ShipLocations;

void welcomeScreen();

int selectWhoStartsFirst();

void displayBoard(char board[10][10]);

char createTenByTen(char playerArray[10][10]);

void placeShips(char playerArray[10][10], ShipLocations location);
void playerInputArray(ShipLocations *ship);

void randomlyPlaceShips(char playerArray[10][10]);

void writeToFile(FILE *fp, char message[]);

void checkIfShipIsSunk(char playerArray[10][10], char playerName[8], FILE *fp, int *isGameOver);

int fireAtTarget(char playerArray[10][10], char playerName[], int shotRow, int shotColumn, int *playerHits, int *playerMisses, FILE *fp);

int doPositionsConflict(int inputArrayRows[5], int inputArrayColumns[5], int shipSize, int isArrayHorizontal, int usedArray[10][10]);