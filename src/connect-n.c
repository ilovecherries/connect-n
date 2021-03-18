#include <stdio.h>
#include <stdlib.h>

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
} Piece;

typedef Piece Row[BOARD_WIDTH];
typedef Piece Col[BOARD_HEIGHT];
typedef Row Board[BOARD_HEIGHT];
typedef int bool;

// this goes through all the columns in a row to check if someone
// has won. returns player ID
Piece checkLine(Piece line[], int length) {
  for (int i = 0; i < length - N + 1; ++i) {
	Piece start = line[i];
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
Piece checkRow(Row row) {
  return checkLine(row, BOARD_WIDTH);
}

// checks if a player has won on a certain column
Piece checkCol(Board board, int col) {
  Col colarr;
  for (int i = 0; i < BOARD_HEIGHT; ++i) {
	colarr[i] = board[i][col];
  }
  return checkLine(colarr, BOARD_HEIGHT);
}

// checks if a player has won on a certain
// left top right diagonal
Piece checkLeftToRightDiags(Board board) {
  for (int i = 0; i < BOARD_WIDTH; ++i) {
	for (int j = 0; j < BOARD_HEIGHT; ++j) {
	  // checks if it will be outside of bounds before iterating
	  // through to check
	  if ((i + N - 1) > BOARD_WIDTH ||
		  (j + N - 1) > BOARD_HEIGHT)
		continue;
	  // check through the array to see if there is a matching player
	  Piece start = board[j][i];
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
Piece checkRightToLeftDiags(Board board) {
  for (int i = 0; i < BOARD_WIDTH; ++i) {
	for (int j = 0; j < BOARD_HEIGHT; ++j) {
	  // checks if it will be outside of bounds before iterating
	  // through to check
	  if ((i + N - 1) > BOARD_WIDTH ||
		  (j + N - 1) > BOARD_HEIGHT)
		continue;
	  // check through the array to see if there is a matching player
	  Piece start = board[j][BOARD_WIDTH - 1 - i];
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

void makeMove(Row board[BOARD_HEIGHT], int col, Piece player) {
  int i;
  for (i = BOARD_HEIGHT - 1; board[i][col]; --i);
  if (i == -1) exit(-1);
  board[i][col] = player;
}

Piece checkWin(Board board) {
  Piece p;
  for (int i = 0; i < BOARD_HEIGHT; ++i) {
	p = checkRow(board[i]);
	if (p) return p;
  }
  for (int i = 0; i < BOARD_WIDTH; ++i) {
	p = checkCol(board, i);
	if (p) return p;
  }
  
  p = checkLeftToRightDiags(board);
  if (p) return p;
  
  p = checkRightToLeftDiags(board);
  if (p) return p;

  return 0;
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
	Piece winner = checkWin(board);
	
	if (winner) {
	  printf("%d IS THE WINNER\n", winner);
	  exit(0);
	}
	
	player = !player;
  }
  
  return 0;
}
