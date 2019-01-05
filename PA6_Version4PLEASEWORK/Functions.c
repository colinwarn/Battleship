#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
// Ship Locations Struct
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


/*
Function: Welcome Screen
Date Created: 11/02/18
Date Last Modified: 11/02/18
Description: Prints game rules
Input Parameters: None
Returns: None
*/

void welcomeScreen() {
	printf("Battleship is a two player Navy game. \n The objective of the game is to sink all ships in your enemy's fleet before yours are sunk. \n The Player to sink his/her enemy's fleet first wins. \n Both players' fleets consist of 5 ships that are hidden from the enemy. \n Each ship may be differentiated by its size (besides the Cruiser and Submarine) \n or number of cells it expands on the game board. \n The Carrier has 5 cells, Battleship has 4 cells, Cruiser has 3 cells, \n Submarine has 3 cells, and the Destroyer has 2 cells.");
	printf("\n Hit any key to continue: ");
	getch();
	
}

/*
Function: Create Ten By Ten
Date Created: 11/02/18
Date Last Modified: 11/02/18
Description: Prints game rules
Input Parameters: Array
Returns: Array of '-'
*/

char createTenByTen(char playerArray[10][10]) {
	printf("\n");

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			playerArray[i][j] = '-';
		}	
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			//printf("%c", playerArray[i][j]);
		}
		//printf("\n");
	}

}

/*
Function: Select Who Starts First
Date Created: 11/02/18
Date Last Modified: 11/02/18
Description: Selects which player starts first
Input Parameters: 
Returns: Person going first
*/

int selectWhoStartsFirst() {
	int player = rand() % 2;
	if (player == 0) {
		printf("\n Player goes first. ");
	}
	else {
		printf("\n Computer goes first.");
	}
	return player;
}

/*
Function: Display Board
Date Created: 11/02/18
Date Last Modified: 11/02/18
Description: Displays Players Board
Input Parameters: Array
Returns: Player's board
*/
void displayBoard(char playerArray[10][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			printf("%c", playerArray[i][j]);
			//printf("x");
		}
		printf("\n");
	}
}

/*
Function: Randomly Place Ships
Date Created: 11/02/18
Date Last Modified: 11/02/18
Description: Randomly places ships onto board
Input Parameters: Player Array
Returns: Nothing
*/

void randomlyPlaceShips(char playerArray[10][10]) {
	int shipSizes[5] = {5, 4, 3, 3, 2};
	char shipChar[5] = { 'c','b','k','s','d' };
	int usedRows[10] = {-1};
	int usedRowsCount = 0;

	// Do this five times
	for (int i = 0; i < 5; i++) {
		// Select a column number size-less than ship
		int ranNumber = 10 - shipSizes[i];
		// Battleship
		int startColumn = rand() % ranNumber;
		
		int startRow = rand() % 10;
		// Create function to check if the startRow is in usedRow
		while (checkIfRowIsUsed(startRow, usedRows) == 1) {
			startRow = rand() % 10;
		}

		//Keep track of used rows
		usedRows[usedRowsCount] = startRow;
		usedRowsCount++;

		
		/*for (int l = 0; l < usedRowsCount; l++) {
			printf("%d", usedRows[l]);
		}*/
		
		for (int j = 0; j < shipSizes[i]; j++) {
			playerArray[startRow][j] = shipChar[i];
			//printf("%c", shipChar[i]);
		}
		

		

	}
	printf("\n \n");
	
}

/*
Function: Fire At Target
Date Created: 11/02/18
Date Last Modified: 11/02/18
Description: Checks if the target has been shot at before.  If not, shoot, then print to file the result. 
Updates the player's hits and misses.  Returns 1 if a shot is allowable, 0 if not.
Input Parameters: Player Array, player name, shot row, shot column, player hits, player misses, file pointer
Returns: Nothing
*/
// Return 0 for retry, 1 for continue
int fireAtTarget(char playerArray[10][10], char playerName[], int shotRow, int shotColumn, int *playerHits, int *playerMisses, FILE *fp) {

	char shot = playerArray[shotRow][shotColumn];

	// Check if shot has been used, look for "m"
	if (playerArray[shotRow][shotColumn] == 'm') {
		printf("\n You've already shot here before, please choose another row and column.");
		return 0;
	}

	if (playerArray[shotRow][shotColumn] == '*') {
		printf("\n You've already shot here before, please choose another row and column.");
		return 0;
	}

	//Check for star

	// Check player array, if it's not "-" then hit
	
	// FIX: POINTER NOT INCREMENTING
	else if (playerArray[shotRow][shotColumn] != '-') {
		fprintf(fp, "\n Row: %d", shotRow);
		fprintf(fp, "\n Column: %d", shotColumn);
		printf("\n %s shot has hit!", playerName);
		fprintf(fp, "\n %s shot has hit!", playerName);
		(*playerHits)++;
		playerArray[shotRow][shotColumn] = '*';
		return 1;
	}
	
	// Else miss
	else {
		fprintf(fp, "\n Row: %d", shotRow);
		fprintf(fp, "\n Column: %d", shotColumn);
		fprintf(fp, "\n %s shot has missed!", playerName);
		printf("\n %s shot has missed!", playerName);
		(*playerMisses)++;
		playerArray[shotRow][shotColumn] = 'm';
		return 1;
	}
	

}
/*
Function: Writes To File
Date Created: 11/02/18
Date Last Modified: 11/02/18
Description: Writes message to file.
Input Parameters: File, message
Returns: Nothing
*/
void writeToFile(FILE *fp, char message[]) {
	
	fprintf(fp, message);
}

/*
Function: Check If Row Is Used
Date Created: 11/02/18
Date Last Modified: 11/02/18
Description: Writes message to file.
Input Parameters: Row, row array to check against
Returns: 1 if it has been used, 0 if not.
*/
int checkIfRowIsUsed(int row, int usedRows[10]) {
	for (int i = 0; i < 10; i++) {
		if (row == usedRows[i]) {
			return 1;
		}
		
	}
	return 0;
}

/*
Function: Check If Input Arrays Rows and Columns Conflict
Date Created: 11/02/18
Date Last Modified: 11/02/18
Description: Determines whether input arrays conflict or not.
Input Parameters: Input array rows, input array columns, the size of the ship being placed, whether the ship is horizontal, used array being checked against.
Returns: 1 if it has been used, 0 if not.
*/
int doPositionsConflict(int inputArrayRows[5], int inputArrayColumns[5], int shipSize, int isArrayHorizontal, int usedArray[10][10]) {
	// True = 1, False = 0
	// Get
	
	
	//Horizontal
	if (isArrayHorizontal == 1) {
		int shipRow = inputArrayRows[0];
		for (int j = inputArrayColumns[0]; j < shipSize; j++) {
			if (usedArray[shipRow][j] != 0) {
				//printf("Row: %d, Column %d", usedArray[shipRow], usedArray[shipRow][j]);
				return 1;
			}
		}
	}
	
	// Vertical
	else {
		int shipColumn = inputArrayColumns[0];
		for (int j = inputArrayRows[0]; j < shipSize; j++) {
			if (usedArray[j][shipColumn] != 0) {
				//printf("Row: %d, Column %d", usedArray[shipColumn][j], usedArray[shipColumn]);
				return 1;
			}
		}
	}

	return 0;
}

// Player fire shot.  Check used fired shots column/row. Get row/column, check array for hit/miss
int playerFiredUpon(char playerArray[10][10], int row, int column, FILE *fp, char playerName[8]) {
	// Return 1 when function has successfully executed
	char location = playerArray[row][column];
	if (location == "m") {
		printf("This location has already been fired at.");
		
		return 0;
	}
	else if (location != "-") {
		// HIT!
		location = "*";
		fprintf(fp, "\n %s hit. Row: %d. Column: %d", playerName, row, column);
		return 1;
	}
	else {
		location = "m";
		fprintf(fp, "\n %s miss. Row: %d. Column: %d", playerName, row, column);
		return 1;
	}
	
}

/*
Function: Check If Row Is Used
Date Created: 11/02/18
Date Last Modified: 11/02/18
Description: Check to see if there are any instances of a character (ship) in a player's board. If not, boat is sunk. Report that ship is sunk in file.  If all ships of this player have been sunk, report game is over. Write results to file.
Input Parameters: Player array, player name, file pointer, isGameOver
Returns: 
*/

void checkIfShipIsSunk(char playerArray[10][10], char playerName[8], FILE *fp, int *isGameOver) {
	int shipsSunk = 0;
	*isGameOver = 0;
	int battleShipSlotsLeft = 0, carrierSlotsLeft = 0, cruiserSlotsLeft = 0, submarineSlotsLeft = 0, destroyerSlotsLeft = 0;
	
	

	//TODO: Populate with other ships

	for (int i = 0; i < 10; i++) {
		
		for (int j = 0; j < 10; j++) {
			// Check if battleship has been sunk
			
			if (playerArray[i][j] == 'c') {
				carrierSlotsLeft++;
			} else if (playerArray[i][j] == 'b') {
				battleShipSlotsLeft++;
			}
			else if (playerArray[i][j] == 'k') {
				cruiserSlotsLeft++;
			}
			else if (playerArray[i][j] == 's') {
				submarineSlotsLeft++;
			}
			else if (playerArray[i][j] == 'd') {
				destroyerSlotsLeft++;
			}
			
		}


	}

	if (battleShipSlotsLeft == 0) {
		//Battleship has been sunk
		printf("\n %s's battleship is sunk.", playerName);
		fprintf(fp, "\n %s's battleship is sunk.", playerName);
		shipsSunk++;
	}
	if (cruiserSlotsLeft == 0) {
		//Battleship has been sunk
		printf("\n %s's cruiser is sunk.", playerName);
		fprintf(fp, "\n %s's cruiser is sunk.", playerName);
		shipsSunk++;
	}
	if (carrierSlotsLeft == 0) {
		//Battleship has been sunk
		printf("\n %s's carrier is sunk.", playerName);
		fprintf(fp, "\n %s's carrier is sunk.", playerName);
		shipsSunk++;
	}
	if (destroyerSlotsLeft == 0) {
		//Battleship has been sunk
		printf("\n %s's destroyer is sunk.", playerName);
		fprintf(fp, "\n %s's destroyer is sunk.", playerName);
		shipsSunk++;
	}
	if (submarineSlotsLeft == 0) {
		//Battleship has been sunk
		printf("\n %s's submarine is sunk.", playerName);
		fprintf(fp, "\n %s's submarine is sunk.", playerName);
		shipsSunk++;
	}

	if (shipsSunk >= 5) {
		printf("\n %s's fleet has been sunk. They have lost!", playerName);
		fprintf(fp, "\n %s has lost.", playerName);
		*isGameOver = 1;
	}
}



/*
Function: Player Input Array
Date Created: 11/02/18
Date Last Modified: 11/02/18
Description: Gets player to manually input his ship's array
Input Parameters: Ship locations
Returns: 
*/
void playerInputArray(ShipLocations *ship) {
	int usedArray[10][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			 usedArray[i][j] = 0 ;
		}
	}
	

	printf("\n Will your carrier be placed horizontal? Enter 1 for yes, 0 for no: ");
	scanf(" %d", &ship->isCarrierHorizontal);
	/*
	ShipLocations *ship
	Accessing members
	ship->member
	or
	(*ship).member
	
	*/

	// Check for overlap at the end of the given ship position

	do {

		printf("\n  This check will run until you have non-conflicting ship positions.");

		if (ship->isCarrierHorizontal == 1) {
			printf("\n Please enter the row to place the Carrier across: ");
			scanf(" %d", &ship->carrierRows[0]);
			printf("\n Please enter the five columns to place the Carrier across: ");
			for (int i = 0; i < 5; i++) {
				int tempColumn[1];
				int breakCount = 0;

				scanf(" %d", &ship->carrierColumns[i]);
				
				
			}

		}
		else {
			printf("\n Please enter the column to place the Carrier across: ");
			scanf(" %d", &ship->carrierColumns);
			printf("\n Please enter the five rows to place the Carrier across: ");
			for (int i = 0; i < 5; i++) {
				scanf(" %d", &ship->carrierRows[i]);
				
			}
		}



	} while (doPositionsConflict(ship->carrierRows, ship->carrierColumns, 5, ship->isCarrierHorizontal, usedArray) == 1);


	// Update Used CARRIER Array
	for (int i = 0; i < 5; i++) {
		if (ship->isCarrierHorizontal == 1) {
			usedArray[ship->carrierRows[0]][ship->carrierColumns[i]] = 1;
		}
		else {
			usedArray[ship->carrierRows[i]][ship->carrierColumns[0]] = 1;
		}
		
	}
	

	/*
	for (int i = 0; i < 5; i++) {
		printf("\n Carrier columns: %d", ship->carrierColumns[i]);
		printf("\n Carrier rows: %d", ship->carrierRows[i]);
	}
	*/
	
	//BATTLESHIP
	printf("\n Will your Battleship be horizontal? Enter 1 for yes, 0 for no: ");
	scanf(" %d", &ship->isBattleshipHorizontal);

	do {
		if (ship->isBattleshipHorizontal == 1) {
			printf("\n Please enter the row to place the Battleship across: ");
			scanf(" %d", &ship->battleshipRows);
			printf("\n Please enter the four columns to place the Battleship across: ");
			for (int i = 0; i < 4; i++) {
				scanf(" %d", &ship->battleshipColumns[i]);
			}

		}
		else {
			printf("\n Please enter the column to place the Battleship across: ");
			scanf(" %d", &ship->battleshipColumns);
			printf("\n Please enter the four rows to place the Battleship across: ");
			for (int i = 0; i < 4; i++) {
				scanf(" %d", &ship->battleshipRows[i]);
			}
		}
	} while (doPositionsConflict(ship->battleshipRows, ship->battleshipColumns, 4, ship->isBattleshipHorizontal, usedArray) == 1);
	
	// Update Used BATTLESHIP Array
	for (int i = 0; i < 4; i++) {
		if (ship->isBattleshipHorizontal == 1) {
			usedArray[ship->battleshipRows[0]][ship->battleshipColumns[i]] = 1;
		}
		else {
			usedArray[ship->battleshipRows[i]][ship->battleshipColumns[0]] = 1;
		}

	}


	//CRUISER
	printf("\n Will your Cruiser be horizontal? Enter 1 for yes, 0 for no: ");
	scanf(" %d", &ship->isCruiserHorizontal);

	do {
		if (ship->isCruiserHorizontal == 1) {
			printf("\n Please enter the row to place the Cruiser across: ");
			scanf(" %d", &ship->cruiserRows);
			printf("\n Please enter the three columns to place the Cruiser across: ");
			for (int i = 0; i < 3; i++) {
				scanf(" %d", &ship->cruiserColumns[i]);
			}

		}
		else {
			printf("\n Please enter the column to place the Cruiser across: ");
			scanf(" %d", &ship->cruiserColumns);
			printf("\n Please enter the three rows to place the Cruiser across: ");
			for (int i = 0; i < 3; i++) {
				scanf(" %d", &ship->cruiserRows[i]);
			}
		}
	} while (doPositionsConflict(ship->cruiserRows, ship->cruiserColumns, 3, ship->isCruiserHorizontal, usedArray) == 1);

	// Update Used CRUISER Array
	for (int i = 0; i < 3; i++) {
		if (ship->isCruiserHorizontal == 1) {
			usedArray[ship->cruiserRows[0]][ship->cruiserColumns[i]] = 1;
		}
		else {
			usedArray[ship->cruiserRows[i]][ship->cruiserColumns[0]] = 1;
		}

	}

	//SUBMARINE
	printf("\n Will your Submarine be horizontal? Enter 1 for yes, 0 for no: ");
	scanf(" %d", &ship->isSubmarineHorizontal);

	do {
		if (ship->isSubmarineHorizontal == 1) {
			printf("\n Please enter the row to place the Submarine across: ");
			scanf(" %d", &ship->submarineRows);
			printf("\n Please enter the three columns to place the Submarine across: ");
			for (int i = 0; i < 3; i++) {
				scanf(" %d", &ship->submarineColumns[i]);
			}

		}
		else {
			printf("\n Please enter the column to place the Submarine across: ");
			scanf(" %d", &ship->submarineColumns);
			printf("\n Please enter the three rows to place the Submarine across: ");
			for (int i = 0; i < 3; i++) {
				scanf(" %d", &ship->submarineRows[i]);
			}
		}
	} while (doPositionsConflict(ship->submarineRows, ship->submarineColumns, 3, ship->isSubmarineHorizontal, usedArray) == 1);

	// Update Used SUBMARINE Array
	for (int i = 0; i < 3; i++) {
		if (ship->isSubmarineHorizontal == 1) {
			usedArray[ship->submarineRows[0]][ship->submarineColumns[i]] = 1;
		}
		else {
			usedArray[ship->submarineRows[i]][ship->submarineColumns[0]] = 1;
		}

	}

	//DESTROYER
	printf("\n Will your Destroyer be horizontal? Enter 1 for yes, 0 for no: ");
	scanf(" %d", &ship->isDestroyerHorizontal);

	do {
		if (ship->isDestroyerHorizontal == 1) {
			printf("\n Please enter the row to place the Destroyer across: ");
			scanf(" %d", &ship->destroyerRows);
			printf("\n Please enter the two columns to place the Destroyer across: ");
			for (int i = 0; i < 2; i++) {
				scanf(" %d", &ship->destroyerColumns[i]);
			}

		}
		else {
			printf("\n Please enter the column to place the Destroyer across: ");
			scanf(" %d", &ship->destroyerColumns);
			printf("\n Please enter the two rows to place the Destroyer across: ");
			for (int i = 0; i < 2; i++) {
				scanf(" %d", &ship->destroyerRows[i]);
			}
		}
	} while (doPositionsConflict(ship->destroyerRows, ship->destroyerColumns, 2, ship->isDestroyerHorizontal, usedArray) == 1);

	// Update Used DESTROYER Array
	for (int i = 0; i < 2; i++) {
		if (ship->isDestroyerHorizontal == 1) {
			usedArray[ship->destroyerRows[0]][ship->destroyerColumns[i]] = 1;
		}
		else {
			usedArray[ship->destroyerRows[i]][ship->destroyerColumns[0]] = 1;
		}

	}

	//TODO: Used column array, used row array
	
	
}


/*
Function: Place Ships
Date Created: 11/02/18
Date Last Modified: 11/02/18
Description: Places the given player's ship locations on the board
Input Parameters: Ship locations, player array
Returns:
*/
void placeShips(char playerArray[10][10], ShipLocations location) {
	// CARRIER
	if (location.isCarrierHorizontal == 1) {
		//printf("Carrier Column: %d \n", location.carrierRows[0]);

		int carrierRows = location.carrierRows[0];
		for (int i = 0; i < 5; i++) {
			
			//printf("Carrier Row: %d \n", location.carrierColumns[i]);
			playerArray[carrierRows][location.carrierColumns[i]] = 'c';
		}
	}
	else {
		//printf("Carrier Row: %d \n", location.carrierRows[0]);
		int carrierColumn = location.carrierColumns[0];
		for (int i = 0; i < 5; i++) {
			//printf("Carrier Column: %d \n", location.carrierColumns[i]);


			playerArray[location.carrierRows[i]][carrierColumn] = 'c';
		}
	}

	// BATTLESHIP
	if (location.isBattleshipHorizontal == 1) {
		//printf("Battleship Column: %d \n", location.battleshipRows[0]);

		int battleshipRow = location.battleshipRows[0];
		for (int i = 0; i < 4; i++) {

			//printf("Battleship Row: %d \n", location.battleshipColumns[i]);
			playerArray[battleshipRow][location.battleshipColumns[i]] = 'b';
		}
	}
	else {
		//printf("Battleship Row: %d \n", location.battleshipRows[0]);
		int battleshipColumn = location.battleshipColumns[0];
		for (int i = 0; i < 4; i++) {
			//printf("Battleship Column: %d \n", location.battleshipColumns[i]);


			playerArray[location.battleshipRows[i]][battleshipColumn] = 'b';
		}
	}

	// CRUISER
	if (location.isCruiserHorizontal == 1) {
		//printf("Cruiser Column: %d \n", location.cruiserRows[0]);

		int cruiserRow = location.cruiserRows[0];
		for (int i = 0; i < 3; i++) {

			//printf("Cruiser Row: %d \n", location.cruiserColumns[i]);
			playerArray[cruiserRow][location.cruiserColumns[i]] = 'k';
		}
	}
	else {
		//printf("Cruiser Row: %d \n", location.cruiserRows[0]);
		int cruiserColumn = location.cruiserColumns[0];
		for (int i = 0; i < 3; i++) {
			//printf("Cruiser Column: %d \n", location.cruiserColumns[i]);


			playerArray[location.cruiserRows[i]][cruiserColumn] = 'k';
		}
	}

	// SUBMARINE
	if (location.isSubmarineHorizontal == 1) {
		//printf("Cruiser Column: %d \n", location.cruiserRows[0]);

		int submarineRow = location.submarineRows[0];
		for (int i = 0; i < 3; i++) {

			//printf("Cruiser Row: %d \n", location.cruiserColumns[i]);
			playerArray[submarineRow][location.submarineColumns[i]] = 's';
		}
	}
	else {
		//printf("Cruiser Row: %d \n", location.cruiserRows[0]);
		int submarineColumn = location.submarineColumns[0];
		for (int i = 0; i < 3; i++) {
			//printf("Cruiser Column: %d \n", location.cruiserColumns[i]);


			playerArray[location.submarineRows[i]][submarineColumn] = 's';
		}
	}

	// DESTROYER
	if (location.isDestroyerHorizontal == 1) {
		//printf("Cruiser Column: %d \n", location.cruiserRows[0]);

		int destroyerRow = location.destroyerRows[0];
		for (int i = 0; i < 2; i++) {

			//printf("Cruiser Row: %d \n", location.cruiserColumns[i]);
			playerArray[destroyerRow][location.destroyerColumns[i]] = 'd';
		}
	}
	else {
		//printf("Cruiser Row: %d \n", location.cruiserRows[0]);
		int destroyerColumn = location.destroyerColumns[0];
		for (int i = 0; i < 2; i++) {
			//printf("Cruiser Column: %d \n", location.cruiserColumns[i]);


			playerArray[location.destroyerRows[i]][destroyerColumn] = 'd';
		}
	}
	
	// Debug player board placement


	// Ship length
}