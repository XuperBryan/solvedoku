#include <iostream>
#include <vector>

using namespace std;

int repCounter = 0;

// represents each number's attributes
/*struct number {	
	int count = 0;

	// true equates to filled position, false equates to empty position
	bool row [9] = {false,false,false,false,false,false,false,false,false};
	bool column [9] = {false,false,false,false,false,false,false,false,false};
	bool box [9] = {false,false,false,false,false,false,false,false,false};
};*/

struct sudoku {
	int matrix[9][9];
	bool solved = false;
/*	number list[10];
*/};

sudoku original;

/*void printNum(int num) {
	for (int i = 0; i < 9; i++) {
		cout << "Row " << i+1 << ": " << original.list[num].row[i] << endl;
		cout << "Column " << i+1 << ": " << original.list[num].row[i] << endl;
		cout << "Box " << i+1 << ": " << original.list[num].row[i] << endl;
	}
}*/

// returns false if incomplete
bool checkComplete(){
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			if (original.matrix[i][j]==0)
				return false;
		}
	}
	return true;
}

void printSudoku() {
	cout << endl;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << original.matrix[i][j] << " ";

			// starts at 0, need to shift over by 1. 
			// Add column symbol after every three numbers, %3 returns 0 when (j+1) is a multiple of 3
			// ! inverts it
			if (!((j+1)%3) && j != 8) {	
				cout << "| ";
			}
		}
		if (!((i+1)%3) && i != 8) {
			cout << "\n" << "_____________________";
		}
		cout << endl;		
	}
}

//solves the original.matrix puzzle by boxes
/*bool initSolver(int num, int boxNum) {

	bool miniBox[3][3];
	// initialization of miniBox
	for (int boxIs = 0; boxIs < 3; boxIs++) {
		for (int sboxJ = 0; sboxJ < 3; sboxJ++) {
			miniBox[boxIs][sboxJ] = false;
		}
	}

	if (!(original.list[num].box[boxNum])) {
		for (int r = (boxNum/3)*3; r <= (boxNum/3)*3+2; r++) {
			for (int c = (boxNum%3)*3; c <= (boxNum%3)*3+2; c++) {
				if(original.list[num].row[r]==true){
					miniBox[r%3][c%3] = true;
				} else if(original.list[num].column[c]==true){
					miniBox[r%3][c%3] = true; 
				} else if(original.matrix[r][c]!=0) {
					miniBox[r%3][c%3] = true;
				}
				
			}
		}
		
		int counter = 0;
		int rCoordinate = -1;
		int cCoordinate = -1;
		for(int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				if (miniBox[i][j] == false){
					counter++;
					rCoordinate = i;
					cCoordinate = j;
				}
			}
		}
		// insert value if only one possible spot
		if (counter == 1){
			original.matrix[rCoordinate + (boxNum/3)*3][cCoordinate + (boxNum%3)*3] = num;
			original.list[num].count++;
			original.list[num].row[rCoordinate + (boxNum/3)*3] = true;
			original.list[num].column[cCoordinate + (boxNum%3)*3] = true;
			original.list[num].box[boxNum] = true;
			return true;
		}
		return false;
	}
	return false;
}*/


// gives the box # (0-9) for row i, column j
int giveBox(int i, int j ){
	if(i>=0&&i<=2&&j>=0&&j<=2){
					return 0;
				} else if(j>2&&j<=5&&i>=0&&i<=2){
					return 1;
				} else if(j>5&&j<=8&&i>=0&&i<=2){
					return 2;
				}else if(j>=0&&j<=2&&i>2&&i<=5){
					return 3;
				}else if(j>2&&j<=5&&i>2&&i<=5){
					return 4;
				}else if(j>5&&j<=8&&i>2&&i<=5){
					return 5;
				}else if(j>=0&&j<=2&&i>5&&i<=8){
					return 6;
				}else if(j>2&&j<=5&&i>5&&i<=8){
					return 7;
				}else {
					return 8;
				}
}

// returns true if we can put into original[i][j]
bool validInput(int num, int i, int j){
	// box coordinates of row i, column j
	int boxNum = giveBox(i, j);

	for (int k = 0; k < 9; k++){
		if(original.matrix[i][k] == num)
			return false;
	}

	for (int k = 0; k < 9; k++){
		if(original.matrix[k][j] == num)
			return false;
	}

	for(int boxRow = (boxNum/3)*3; boxRow <= (boxNum/3)*3+2; boxRow++){
		for (int boxCol = (boxNum%3)*3; boxCol <= (boxNum%3)*3+2; boxCol++){
			if(original.matrix[boxRow][boxCol] == num)
				return false;
		}
	}
	return true;
}


// finds the next empty spot in sudoku
bool findEmpty(int &row, int &col){
	for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (original.matrix[row][col] == 0)
                return true;
    return false;
}


bool backTrack(){
	int row, col;
	if(findEmpty(row, col) == false){
		return true;
	} else {
		for(int num = 1; num <= 9; num++){
			// inserts num into sudoku if within rules
			if(validInput(num, row, col)){
				original.matrix[row][col] = num;
		
				// recursively calls itself, ends when sudoku is complete
				if(backTrack()){
					return true;
				}
				original.matrix[row][col] = 0;
			}				
		}
			
	}
	return false;
}

int main() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> original.matrix[i][j];
			/*if(original.matrix[i][j] != 0){
				original.list[original.matrix[i][j]].count++;
				original.list[original.matrix[i][j]].row[i] = true;
				original.list[original.matrix[i][j]].column[j] = true;
				original.list[original.matrix[i][j]].box[giveBox(i,j)] = true;  
			}*/
		}
	}


	// before solve
	printSudoku();
	/*while (repCounter < 10){
		for (int num = 1; num <= 9 && repCounter < 10; num++) {
			repCounter++;
			for (int box = 0; box < 9; box++) {
				if (initSolver(num,box)) {
					repCounter = 0;
				}
			}
		}
	}*/

	backTrack();

	cout << endl << endl << endl;
	// after solve
	printSudoku();

	return 0;
}


/*TEST
5 3 4 6 7 8 9 1 2 6 7 2 1 9 5 0 4 8 0 9 8 3 4 0 5 6 7 8 5 9 7 6 1 4 2 3 0 2 6 8 0 3 7 9 1 7 1 3 9 2 4 8 5 0 9 6 1 5 3 7 2 8 4 2 8 0 4 1 9 6 3 5 3 4 5 2 0 6 1 7 0

0 8 0 0 0 0 2 0 0 0 0 0 0 8 4 0 9 0 0 0 6 3 2 0 0 1 0 0 9 7 0 0 0 0 8 0 8 0 0 9 0 3 0 0 2 0 1 0 0 0 0 9 5 0 0 7 0 0 4 5 8 0 0 0 3 0 7 1 0 0 0 0 0 0 8 0 0 0 0 4 0

9 2 0 8 1 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 2 6 5 0 0 0 5 0 8 4 0 2 0 0 0 0 4 0 0 0 0 6 8 0 0 9 0 0 3 8 2 0 4 0 3 4 0 0 0 0 0 2 0 8 0 0 2 3 0 7 9 0 0 0 0 0 0 5 0 8 

9 0 1 2 0 0 0 0 6 0 6 0 0 8 0 0 0 4 0 0 0 0 0 4 0 0 3 7 0 0 0 0 1 0 0 5 0 0 5 0 4 0 6 0 0 3 0 0 5 0 0 0 0 8 2 0 0 4 0 0 0 0 0 6 0 0 0 5 0 0 9 0 4 0 0 0 0 7 8 0 1

0 0 0 7 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 4 3 0 2 0 0 0 0 0 0 0 0 0 0 6 0 0 0 5 0 9 0 0 0 0 0 0 0 0 0 4 1 8 0 0 0 0 8 1 0 0 0 0 0 2 0 0 0 0 5 0 0 4 0 0 0 0 3 0 0 
*/
