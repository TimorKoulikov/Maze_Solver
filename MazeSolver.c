#include<stdio.h>
#include<stdlib.h>
#include <stdio.h>
#include "Node.h"
#include "Vector.h"


#define START 5
#define END 6

const int width = 20;
const int height = 20;
char** Board;


//Init() Init the board and the Maze
void Init();
//InitBoard() Init the board with walls,start,end
void InitBoard();
//InitMaze() Init Maze. the board must be Init first
void InitMaze();
//Draw the Board
void Draw();
//ChangeBoard() is changine the value in Board[x][y]=c
void ChangeBoard(int x,int y,char c);
//Solve the board in recurive way
void Solve(Node* start);
//creating the path of the maze
void CreateMaze();
//find all nearby cells of a given cell in the maze
vec** nearbyCells(int*);

int main() 
{

	Init();//Init the Board.everything saved in char** Board	
	Solve(NULL); //Solving the board;	

}


void Init() 
{
	InitBoard();
	
	InitMaze();
}

//Init Board
//the wall is made of '#' and empty space is ' '
void InitBoard()
{
	
	Board = (char**)malloc(sizeof(char*) * width);

	for (int i = 0; i < height; i++)
		Board[i] = (char*)malloc(sizeof(char) * height);

	
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			
			if (i == 0 || j == 0 || i == width - 1 || j == height - 1) 
				Board[i][j] = '#';
			else 
			{ 
				Board[i][j] = ' '; 
			}
			
		}
	}

	Board[START][0] = ' ';
	Board[END][height - 1] = ' ';

}


void InitMaze()
{
	
	srand(getpid());//Create uniqe rand(). without it the rand will generate the same random sequnce.

	//Create the Maze
	
	Node* start = NodeCreate(vector(START,0), VECTOR);

	
	
	while (start != NULL) {
				
		vec** close_cells = nearbyCells(start->data);
		int num_close_cells = close_cells[0]->x;

		if (num_close_cells == 0) {
			start = start->Next;
			continue;
		}

		int r_cell = rand() % (num_close_cells);
		
		vec* next_cell = close_cells[r_cell + 1];
		
		NodeAddStart(&start, copyVector(next_cell));
		
		ChangeBoard(next_cell->x, next_cell->y, '0');

		
		if (abs(next_cell->x - END) < 2 && abs(next_cell->y - (width - 2)) < 2) {
			if (abs(next_cell->x - END) ^ abs(next_cell->y - (width - 2))) {
				
				vec* temp = vector(END, width - 1);
				
				NodeAddStart(&start, copyVector(temp));
			}
		}
		
		for (int i = 0; i < num_close_cells; i++)
		{
			free(close_cells[i]);
		}
		free(close_cells);
	}


	//create wall and path.Reverse the path into empty space and empty space into wall
	for (int i = 1; i < width - 1; i++) {
		for (int j = 1; j < height - 1; j++) {
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
		return 0;
		
}
//return array of nearby cells
vec** nearbyCells(vec* cell) 
{
	
	int addVec[4][2] = { {-1,0},{1,0},{0,1},{0,-1} };
	int sumVec[4][2];
	int count = 0;
	int x = cell->x;
	int y = cell->y;

	
	
	for (int i = 0; i < 4; i++)
	{
		int Sx = x + addVec[i][0];
		int Sy = y + addVec[i][1];

		if (CanGo(Sx, Sy))
		{
			sumVec[count][0] =Sx;
			sumVec[count][1] = Sy;
			
			count++;
		}
		
	}

	vec** cells=(vec**)malloc((count+1)*sizeof(vec*));

	for (int i = 0; i < count; i++)
		cells[i + 1] = vector(sumVec[i][0], sumVec[i][1]);
	
	cells[0] = vector(count, 0);
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

void Solve(Node * node) {
		
		if (node == NULL) 			
			node = NodeCreate(vector(START,0), VECTOR);
		
	
		vec* nodeVector=copyVector(node->data);
			
		if (nodeVector->x == END && nodeVector->y == height - 2) {
			ChangeBoard(nodeVector->x, nodeVector->y, '2');
			return 0;
		}

		vec** close_cells = nearbyCells(node->data);
		int num_close_cells = close_cells[0]->x;
		if (num_close_cells == 0) {
			
			ChangeBoard(nodeVector->x, nodeVector->y, '1');
			
			//free memory allocation
			for (int i = 0; i < num_close_cells; i++)
			{
				free(close_cells[i]);
			}
			free(close_cells);
			return 0;
		}
		for (int i = 0; i < num_close_cells ; i++) {

			vec* next_cell = close_cells[i + 1];		
			NodeAddStart(&node, copyVector(next_cell));
			
			ChangeBoard(next_cell->x, next_cell->y, '0');
			
			Solve(node);
			if (Board[next_cell->x][next_cell->y] == '2') {
				
				ChangeBoard(nodeVector->x, nodeVector->y, '2');
				return 0;
			}


		 	

		}

		ChangeBoard(nodeVector->x, nodeVector->y, '1');	

}


