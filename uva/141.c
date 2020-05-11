/* @JUDGE_ID: 1102NT 141 C "Brute force" */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char board[50][50];
char history[200][251];
int hist_num;
int n;

void rotate(char board1[50][50], char board2[50][50], char board3[50][50])
{
  int i, j;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      board1[j][n-i-1] = board2[n-j-1][i] = board3[n-i-1][n-j-1] = board[i][j];
    }
  }
}

void signature(char board[50][50], char *buffer)
{
  int i, j;
  int b, c;

  b = c = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (board[i][j]) {
	b |= (1 << c);
      }
      if (++c == 7) {
	*buffer++ = b+1;
	b = c = 0;
      }
    }
  }
  if (c) {
    *buffer++ = b+1;
  }
  *buffer = 0;
}

int find_history(char *buffer)
{
  int i;
  for (i = 0; i < hist_num; i++) {
    if (!strcmp(history[i], buffer)) {
      return 1;
    }
  }
  return 0;
}

void do_case(void)
{
  int finished, i, j;
  int row, col;
  char buffer[2501];
  char new_board1[50][50], new_board2[50][50], new_board3[50][50];

  finished = 0;
  hist_num = 0;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      board[i][j] = 0;
    }
  }

  for (i = 0; i < 2*n; i++) {
    scanf("%d %d %1s", &row, &col, buffer);
    row--;
    col--;
    if (!finished) {
      if (buffer[0] == '+') {
	assert(board[row][col] == 0);
	board[row][col] = 1;
      } else {
	assert(buffer[0] == '-' && board[row][col] == 1);
	board[row][col] = 0;
      }

      signature(board, buffer);
      finished = find_history(buffer);
      if (!finished) {
	rotate(new_board1, new_board2, new_board3);
	signature(new_board1, buffer);
	finished = find_history(buffer);
      }
      if (!finished) {
	signature(new_board2, buffer);
	finished = find_history(buffer);
      }
      if (!finished) {
	signature(new_board3, buffer);
	finished = find_history(buffer);
      }

      if (finished) {
	printf("Player %d wins on move %d\n", (i % 2 == 0) ? 2 : 1, i+1);
      } else {
	strcpy(history[hist_num++], buffer);
      }
    }
  }
  if (!finished) {
    printf("Draw\n");
  }
}



int main(void)
{
  while (scanf("%d", &n) == 1 && n > 0) {
    do_case();
  }
  
  return 0;
}
