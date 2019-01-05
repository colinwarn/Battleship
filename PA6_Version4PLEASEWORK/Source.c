/*
Colin Warn
11/02/2018
File plays game of Battleship
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include "Functions.h"

int main(void) {
	srand(time(NULL));

	char humanPlayerArray[10][10];
	char computerPlayerArray[10][10];
	char usedPlayerShotArray[10][10];

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			usedPlayerShotArray[i][j] = '-';
		}
	}
	

	//Writing to files
	FILE *fp = NULL;
	fp = fopen("Game.txt", "w+");

	char playerName[9] = "Player";
	char computerName[9] = "Computer";
	int playerTurn = 1;
	int playerHits = 0, playerMisses = 0;
	int computerHits = 0, computerMisses = 0;
	int isGameOver = 0;
	int playerWhoGoesFirst = 2;
	FILE *battleshipLog = NULL;
	ShipLocations playerShipLocations;

	welcomeScreen();

	playerWhoGoesFirst = selectWhoStartsFirst();
	
	createTenByTen(humanPlayerArray);
	createTenByTen(computerPlayerArray);

	printf("\n Do you want to (1) manually or (2) randomly place your ships? ");
	int answer = 0;
	scanf("%d", &answer);

	if (answer == 1) {
		playerInputArray(&playerShipLocations);
		placeShips(humanPlayerArray, playerShipLocations);
	}
	else if (answer == 2) {
		randomlyPlaceShips(humanPlayerArray);
	}
	
	randomlyPlaceShips(computerPlayerArray);

	printf("\n Player Ship Array: \n");
	displayBoard(humanPlayerArray);

	int internalTurn = -1;
	// If random is 0, player goes first. Else, computer
	if (playerWhoGoesFirst == 0) {
		internalTurn = 2;
	}
	else {
		internalTurn = 1;
	}
	 
	// Run game
	while (isGameOver == 0) {
		// If internal turn is even, player's turn.  Else, computer's turn.
		
		int shotRow = -1;
		int shotColumn = -1;
		

		if (internalTurn % 2 == 0) {
			while ((shotRow < 0) || (shotRow > 10) || (shotColumn < 0) || (shotColumn > 10)) {
				printf("\n Enter a row to fire at, between 0 and 9: ");
				scanf("%d", &shotRow);
				printf("\n Enter a column to fire at, between 0 and 9: ");
				scanf("%d", &shotColumn);
			}

			int oldPlayerHits = playerHits;
			while (fireAtTarget(computerPlayerArray, playerName, shotRow, shotColumn, &playerHits, &playerMisses, fp) == 0) {
				while ((shotRow < 0) || (shotRow > 10) || (shotColumn < 0) || (shotColumn > 10)) {
					printf("\n Enter a row to fire at, between 0 and 9: ");
					scanf("%d", &shotRow);
					printf("\n Enter a column to fire at, between 0 and 9: ");
					scanf("%d", &shotColumn);
				}
				
				
			}

			if (playerHits > oldPlayerHits) {
				usedPlayerShotArray[shotRow][shotColumn] = '*';
			}
			else {
				usedPlayerShotArray[shotRow][shotColumn] = 'm';
			}

		}
		else {
			shotRow = rand() % 10;
			shotColumn = rand() % 10;
			while (fireAtTarget(humanPlayerArray, computerName, shotRow, shotColumn, &computerHits, &computerMisses, fp
			) == 0) {
				shotRow = rand() % 10;
				shotColumn = rand() % 10;
			}
		}


		internalTurn++;
		playerTurn++;
		printf("\n Player Ship Array: \n");
		displayBoard(humanPlayerArray);
		printf("\n Shots Used Array: \n");
		displayBoard(usedPlayerShotArray);
		checkIfShipIsSunk(humanPlayerArray, playerName, fp, &isGameOver);
		printf("\n Hit any key to continue: ");
		getch();
		system("@cls||clear");
		
	}
	
	
	fprintf(fp, "\n Player Hits: %d Player Misses: %d \n Computer Hits: %d Computer Misses: %d", playerHits, playerMisses, computerHits, computerMisses);
	fclose(fp);

	return 0;


	//FIX: Stack corrupted
}