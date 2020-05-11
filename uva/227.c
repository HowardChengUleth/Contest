/* @JUDGE_ID: 1102NT 227 C "" */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

char board[5][1024];

int read_board(void)
{
  int i;

  for (i = 0; i < 5; i++) {
    fgets(board[i], 1024, stdin);
    if (i == 0 && board[0][0] == 'Z') {
      return 0;
    }
  }
  return 1;
}

int do_moves(void)
{
  char buffer[1024];
  int good = 1;
  int r, c;
  int i, j;
  int ch;

  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      if (board[i][j] == ' ') {
	r = i;
	c = j;
      }
    }
  }

  while ((ch = getchar()) != EOF && ch != '0') {
    if (isspace(ch)) continue;
    switch (ch) {
    case 'A':
      if (r == 0) {
	good = 0;
      } else {
	board[r][c] = board[r-1][c];
	board[--r][c] = ' ';
      }
      break;
    case 'B':
      if (r == 4) {
	good = 0;
      } else {
	board[r][c] = board[r+1][c];
	board[++r][c] = ' ';
      }
      break;
    case 'R':
      if (c == 4) {
	good = 0;
      } else {
	board[r][c] = board[r][c+1];
	board[r][++c] = ' ';
      }
      break;
    case 'L':
      if (c == 0) {
	good = 0;
      } else {
	board[r][c] = board[r][c-1];
	board[r][--c] = ' ';
      }
      break;
    default:
      good = 0;
    }
  }


  /* read the remaining new line */
  fgets(buffer, 1024, stdin);

  return good;
}


int main(void)
{
  int cases = 1;
  int i, j;

  while (read_board()) {
    if (cases > 1) {
      printf("\n");
    }
    printf("Puzzle #%d:\n", cases++);
    if (do_moves()) {
      for (i = 0; i < 5; i++) {
	for (j = 0; j < 5; j++) {
	  printf("%c%s", board[i][j], (j < 4) ? " " : "\n");
	}
      }
    } else {
      printf("This puzzle has no final configuration.\n");
    }
  }

  return 0;
}

