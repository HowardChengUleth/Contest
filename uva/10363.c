#include <stdio.h>

int finished(char board[3][4])
{
  int i, j, k, l;
  int allx, allo;

  int start_i[8] = { 0, 0, 0, 0, 1, 2, 0, 0 };
  int start_j[8] = { 0, 1, 2, 0, 0, 0, 0, 2 };
  int d_i[8]     = { 1, 1, 1, 0, 0, 0, 1, 1 };
  int d_j[8]     = { 0, 0, 0, 1, 1, 1, 1, -1};

  for (k = 0; k < 8; k++) {
    allx = allo = 1;
    i = start_i[k];
    j = start_j[k];
    for (l = 0; l < 3; l++) {
      switch (board[i][j]) {
      case '.':
	allx = allo = 0;
	break;
      case 'O':
	allx = 0;
	break;
      case 'X':
	allo = 0;
	break;
      }
      i += d_i[k];
      j += d_j[k];
    }
    if (allx || allo) return 1;
  }

  return 0;
}

int search(char board[3][4], char newboard[3][4], int player, int moves)
{
  char piece[3] = "XO";
  int i, j;

  if (moves <= 1) {
    return 1;
  }

  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if (newboard[i][j] != '.' || board[i][j] != piece[player]) continue;
      newboard[i][j] = piece[player];
      if (!finished(newboard)) {
	if (search(board, newboard, 1-player, moves-1)) {
	  return 1;
	}
      }
      newboard[i][j] = '.';
    }
  }
  return 0;
}

int solve(void)
{
  char board[3][4];
  char newboard[3][4];
  int i, j;
  int ocount, xcount;

  ocount = xcount = 0;
  for (i = 0; i < 3; i++) {
    scanf("%s", board[i]);
    for (j = 0; j < 3; j++) {
      newboard[i][j] = '.';
      if (board[i][j] == 'O') ocount++;
      if (board[i][j] == 'X') xcount++;
    }
  }
  if (!(xcount == ocount || xcount == ocount+1)) {
    return 0;
  }

  return search(board, newboard, 0, xcount+ocount);
}

int main(void)
{
  int N;

  scanf("%d", &N);
  while (N-- > 0) {
    printf("%s\n", (solve() ? "yes" : "no"));
  }
  return 0;
}
