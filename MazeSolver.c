#include<stdio.h>
#include<stdlib.h>
#include <stdio.h>
#include "Node.h"

//TO_DO//
//check about memory allocatin and returning array and pointer from function


#define START 5
#define END 6

const int width = 20;
const int height = 20;
char** Board;


//Init the Board
void Init();
//Draw the Board
void Draw();
void ChangeBoard(int x,int y,char c);
void Solve(Node* start);
void CreateMaze();
int** nearbyCells(int x, int y);

int main() {

	
	
	
	Init();//Init the Board.everything saved in char** Board
	
	Draw();//Draw the char** Board
	
	Solve(NULL); //Solving the board;
	Draw();
	
	
}
void Init() {

	srand(getpid());//Create uniqe rand(). without it the rand will generate the same random sequnce.

	//Creating empty Board. setting values for each element in char**Board.
	Board = (char**)malloc(sizeof(char*) * width);

	for (int i = 0; i < height; i++)
		Board[i] = (char*)malloc(sizeof(char) * height);

	//give walls to the board
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			//the border is #
			if (i == 0 || j == 0 || i == width - 1 || j == height - 1) 
				//if((i ==START && j== 0)||(i==END && j==height-1)){ Board[i][j] = ' '; }//Draw the start end end of maze
				Board[i][j] = '#';
			
			else 
			{
				Board[i][j] = ' ';
			}
		}
	}

	Board[START][0] = ' ';
	Board[END][height - 1] = ' ';
	
	
	
	//Create the Maze
	int startpoint[2] = { START, 0 };
	Node* start=NodeCreate(startpoint,VECTOR);

	int** cells;
	while (start != NULL) {//create Functions
		int start_point[2];
		start_point[0] =((int*)(start->data))[0] ;
		start_point[1] = ((int*)(start->data))[1];
		
		int** close_cells = nearbyCells(start_point[0], start_point[1]);
		int num_close_cells = close_cells[0][0];
		if (num_close_cells == 1) {
			start = start->Next;
			continue;
		}
		int r_cell = rand() % (num_close_cells-1);
		//printf("\033[32;1m %d %d\033[0m\n",r_cell,num_close_cells-1);
		int* next_cell= close_cells[r_cell+1];
		NodeAddStart(&start, next_cell);
		//Board[next_cell[0]][next_cell[1]] = '0';
		ChangeBoard(next_cell[0], next_cell[1], '0');
		
		if (abs(next_cell[0] - END) < 2 && abs(next_cell[1] - (width - 2)) < 2) {
			if (abs(next_cell[0] - END) ^ abs(next_cell[1] - (width - 2))) {
				int temp[2] = { END,width - 1 };
				next_cell = temp;
				NodeAddStart(&start, next_cell);
			}
		}
		
	}
	//create wall and path.Reverse the path into empty space and empty space into wall
	for (int i = 1; i < width-1; i++) {
		for (int j = 1; j < height-1; j++) {
			if (Board[i][j] == ' ') {
				Board[i][j] = '#';
			}
			if (Board[i][j] == '0') {
				Board[i][j] = ' ';
			}
			
		}
	}
	
}

//check if next point can be part of the path.
//RULES:1.cannot be a existing path(be '0')
//		2.cannot be a wall(be '#')
//		3.cannot connect 2 existing paths
int CanGo(int x,int y) {
	if (x > 0 && y > 0&&x<width-1&&y<height-1) {
		int count = 0;
		if (Board[x + 1][y] == '0') { count++; }
		if (Board[x - 1][y] == '0') { count++; }
		if (Board[x][y + 1] == '0') { count++; }
		if (Board[x][y - 1] == '0') { count++; }
	
		return (Board[x][y] != '#' && Board[x][y] != '0' && count<=1);
	}
		else
		return 0;
		
}
//return array of nearby cells
int** nearbyCells(int x, int y) {
	int** cells=(int**)calloc(1,sizeof(*cells));
	

	int addVec[4][2] = { {-1,0},{1,0},{0,1},{0,-1}	};
	int count = 1;
	for (int i = 0; i < 4; i++) {
		int Sx = x + addVec[i][0];
		int Sy = y + addVec[i][1];
		if (CanGo(Sx, Sy)) {	
			count++;			
			cells = (int**)realloc(cells,count*(sizeof(*cells)));

			cells[count - 1] =(int*) malloc(2*(sizeof(int)));
			cells[count - 1][0] = Sx;
			cells[count - 1][1] = Sy;
			
			
			
			
		}
	}
	cells[0] = (int*)malloc(2 * sizeof(int));
	cells[0][0] = count;
	return cells;

}
//Kinda explanatory.
//If not. it is drawing the Board. :(
void Draw() {

	system("cls");

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {

			//the border is #
			switch (Board[i][j]) {
			
			case '0':
				printf("\033[0;35m");
				break;
			case '1' :
				printf("\033[0;31m");
				break;
			case '2':
				printf("\033[0;32m");
				break;
			case '#':
				printf("\033[0;37m");
			case ' ':
				printf("\033[0m");
				break;

			}

			printf("%c\033[0m", Board[i][j]);
			
		}
		printf("\n");
	}
}

void ChangeBoard(int x, int y,char c){
	Board[x][y] = c;
	Draw();
}

void Solve(Node * start) {
		
		if (start == NULL) {
			int startpoint[2] = { START, 0 };
			start = NodeCreate(startpoint, VECTOR);
		}
	
		int start_point[2];
		start_point[0] = ((int*)(start->data))[0];
		start_point[1] = ((int*)(start->data))[1];
		
		if (start_point[0] == END && start_point[1] == height - 2) {
			//Board[start_point[0]][start_point[1]] = '2';
			ChangeBoard(start_point[0], start_point[1], '2');
			return 0;
		}

		int** close_cells = nearbyCells(start_point[0], start_point[1]);
		int num_close_cells = close_cells[0][0];
		if (num_close_cells == 1) {
			//Board[start_point[0]][start_point[1]] = '1';
			ChangeBoard(start_point[0], start_point[1], '1');
			
			return 0;
		}
		for (int i = 0; i < num_close_cells - 1; i++) {

			int* next_cell = close_cells[i + 1];

			NodeAddStart(&start, next_cell);
			//Board[next_cell[0]][next_cell[1]] = '0';
			ChangeBoard(next_cell[0], next_cell[1], '0');
			
			Solve(start);
			if (Board[next_cell[0]][next_cell[1]] == '2') {
				//Board[start_point[0]][start_point[1]] = '2';
				ChangeBoard(start_point[0], start_point[1], '2');
				return 0;
			}


		 	

		}

		
			//Board[start_point[0]][start_point[1]] = '1';
		ChangeBoard(start_point[0], start_point[1], '1');
			
		
		//printf("\033[32;1m %d %d\033[0m\n",r_cell,num_close_cells-1);
		
		
		
		
	

}


