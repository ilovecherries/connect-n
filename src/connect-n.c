#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>

#define BOARD_WIDTH 6
#define BOARD_HEIGHT 7
#define N 4
#define true 1
#define false 0
#define EMPTY_CIRCLE "◯"
#define FILLED_CIRCLE "⬤"

typedef enum {
  None=0,
  Red,
  Yellow
} Player;

typedef Player Row[BOARD_WIDTH];
typedef Player Col[BOARD_HEIGHT];
typedef Row Board[BOARD_HEIGHT];
typedef int bool;

// this goes through all the columns in a row to check if someone
// has won. returns player ID
Player checkLine(Player line[], int length) {
  for (int i = 0; i < length - N; ++i) {
	Player start = line[i];
	if (start != None) {
	  bool matching = true;
	  for (int j = 0; j < N && matching; ++j) {
		if (line[i+j] != start) matching = false;
	  }
	  if (matching)
		return start;
	}
  }
  
  return 0;
}

// checks if a player has won on a certain row
Player checkRow(Row row) {
  return checkLine(row, BOARD_WIDTH);
}

// checks if a player has won on a certain column
Player checkCol(Board board, int col) {
  Col colarr;
  for (int i = 0; i < BOARD_HEIGHT; ++i) {
	colarr[i] = board[i][col];
  }
  return checkLine(colarr, BOARD_HEIGHT);
}

// checks if a player has won on a certain
// left top right diagonal
Player checkLeftToRightDiags(Board board) {
  for (int i = 0; i < BOARD_WIDTH; ++i) {
	for (int j = 0; j < BOARD_HEIGHT; ++j) {
	  // checks if it will be outside of bounds before iterating
	  // through to check
	  if ((i + N - 1) > BOARD_WIDTH ||
		  (j + N - 1) > BOARD_HEIGHT)
		continue;
	  // check through the array to see if there is a matching player
	  Player start = board[j][i];
	  if (start) {
		bool matching = true;
		for (int k = 0; k < N && matching; ++k) {
		  if (board[j+k][i+k] != start) matching = false;
		}
		if (matching)
		  return start;
	  }
	}
  }
  
  return None;
}

// checks if a player has won on a certain
// left top right diagonal
Player checkRightToLeftDiags(Board board) {
  for (int i = 0; i < BOARD_WIDTH; ++i) {
	for (int j = 0; j < BOARD_HEIGHT; ++j) {
	  // checks if it will be outside of bounds before iterating
	  // through to check
	  if ((i + N - 1) > BOARD_WIDTH ||
		  (j + N - 1) > BOARD_HEIGHT)
		continue;
	  // check through the array to see if there is a matching player
	  Player start = board[j][BOARD_WIDTH - 1 - i];
	  if (start) {
		bool matching = true;
		for (int k = 0; k < N && matching; ++k) {
		  if (board[j+k][BOARD_WIDTH - 1 - (i+k)] != start) matching = false;
		}
		if (matching)
		  return start;
	  }
	}
  }
  
  return None;
}

void displayBoard(Board board) {
  for (int i = 0; i < BOARD_HEIGHT; ++i) {
	for (int j = 0; j < BOARD_WIDTH; ++j) {
	  if (board[i][j]) {
		if (board[i][j] == Red)
		  printf("\033[31m");
		else
		  printf("\033[33m");
		printf(FILLED_CIRCLE);
	  } else {
		printf("\033[37m");
		printf(EMPTY_CIRCLE);
	  }
	}
	printf("\n");
  }
}

void makeMove(Row board[BOARD_HEIGHT], int col, Player player) {
  int i;
  for (i = BOARD_HEIGHT - 1; board[i][col]; --i);
  if (i == -1) exit(-1);
  board[i][col] = player;
}

int main(void) {
  Board board = {0};

  displayBoard(board);
  int player = 0;
  while (true) {
	int col;
	scanf("%d", &col);
	makeMove(board, col, player+1);
	displayBoard(board);
	// check if anyone has won
	for (int i = 0; i < BOARD_HEIGHT; ++i) {
	  if (checkRow(board[i])) exit(0);
	}
	for (int i = 0; i < BOARD_WIDTH; ++i) {
	  if (checkCol(board, i)) exit(0);
	}
	if (checkLeftToRightDiags(board)) exit(0);
	if (checkRightToLeftDiags(board)) exit(0);
	
	player = !player;
  }
  
  return 0;
}
