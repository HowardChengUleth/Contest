#include <stdio.h>
#include <string.h>
#include <limits.h>

int R, C;
char board[18][19];
char inv[256];

int read_case(void)
{
  int i, j, t;
  
  scanf("%d %d", &R, &C);
  if (!R && !C) {
    return 0;
  }
  for (i = 1; i <= R; i++) {
    scanf("%s", board[i]+1);
  }

  if (R < C) {
    for (i = 1; i <= R; i++) {
      for (j = i+1; j <= C; j++) {
	t = board[i][j];
	board[i][j] = board[j][i];
	board[j][i] = t;
      }
    }
    t = R;
    R = C;
    C = t;
  }

  return 1;
}

void flip(char B[18][19], int i, int j)
{
  B[i][j] = inv[(unsigned char)B[i][j]];
  B[i-1][j] = inv[(unsigned char)B[i-1][j]];
  B[i+1][j] = inv[(unsigned char)B[i+1][j]];
  B[i][j-1] = inv[(unsigned char)B[i][j-1]];
  B[i][j+1] = inv[(unsigned char)B[i][j+1]];
}

int solve_mask(int mask, int best)
{
  int num = 0;
  int i, j;
  char board2[18][19];

  for (i = 1; i <= R; i++) {
    strcpy(board2[i]+1, board[i]+1);
  }

  /* flip first row */
  for (j = 1; j <= C; j++) {
    if (mask & 0x01) {
      num++;
      flip(board2, 1, j);
    }
    mask >>= 1;
  }

  /* now flip the rest */
  for (i = 1; i <= R-1; i++) {
    for (j = 1; j <= C; j++) {
      if (board2[i][j] == 'X') {
	num++;
	if (num >= best) {
	  return num;
	}
	flip(board2, i+1, j);
      }
    }
  }

  /* check the last row */
  for (j = 1; j <= C; j++) {
    if (board2[R][j] == 'X') {
      return best;
    }
  }
  return num;
}

void solve_case()
{
  int mask;
  int best = INT_MAX;
  int num;
  for (mask = 0; mask < (1 << C); mask++) {
    if ((num = solve_mask(mask, best)) < best) {
      best = num;
    }
  }
  if (best < INT_MAX) {
    printf("You have to tap %d tiles.\n", best);
  } else {
    printf("Damaged billboard.\n");
  }
}

int main(void)
{
  inv['.'] = 'X';
  inv['X'] = '.';

  while (read_case()) {
    solve_case();
  }
  return 0;
}
