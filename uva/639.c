#include <stdio.h>

int max_rooks(char board[4][5], int n, int r, int c)
{
  int t1, t2;
  int i, good;

  if (c >= n) {
    r++;
    c = 0;
  }

  if (r >= n) {
    return 0;
  }

  /* try not adding one */
  t1 = max_rooks(board, n, r, c+1);

  if (board[r][c] == 'X') {
    return t1;
  }

  /* add one if possible */
  good = 1;
  for (i = r-1; i >= 0 && board[i][c] != 'X' && good; i--) {
    if (board[i][c] == 'R') {
      good = 0;
    }
  }
  for (i = c-1; i >= 0 && board[r][i] != 'X' && good; i--) {
    if (board[r][i] == 'R') {
      good = 0;
    }
  }
  if (!good) {
    return t1;
  }

  board[r][c] = 'R';
  t2 = 1 + max_rooks(board, n, r, c+1);
  board[r][c] = '.';
  return (t1 > t2) ? t1 : t2;
}

int main(void)
{
  int n;
  char board[4][5];
  int i;

  while (scanf("%d", &n) == 1 && n) {
    for (i = 0; i < n; i++) {
      scanf("%s", board[i]);
    }
    
    printf("%d\n", max_rooks(board, n, 0, 0));
  }
  return 0;
}
