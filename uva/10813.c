/* @JUDGE_ID: 1102NT 10813 C "" */

#include <stdio.h>

int board[5][5];
char mark[5][5];
int numbers[75];

void read_case(void)
{
  int i, j;

  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      if (i == 2 && j == 2) {
	board[i][j] = 100;     /* doesn't really matter */
	mark[i][j] = 1;
      } else {
	scanf("%d", &(board[i][j]));
	mark[i][j] = 0;
      }
    }
  }

  for (i = 0; i < 75; i++) {
    scanf("%d", numbers+i);
  }
}

void put_mark(int k)
{
  int i, j;

  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      if (board[i][j] == k) {
	mark[i][j] = 1;
	return;
      }
    }
  }
}

int line(int r, int c, int dr, int dc)
{
  int i;

  for (i = 0; i < 5; i++) {
    if (!mark[r][c]) {
      return 0;
    }
    r += dr;
    c += dc;
  }
  return 1;
}

int win(void)
{
  int i;
  for (i = 0; i < 5; i++) {
    if (line(i, 0, 0, 1)) {
      return 1;
    }
    if (line(0, i, 1, 0)) {
      return 1;
    }
  }
  return line(0, 0, 1, 1) || line(0, 4, 1, -1);
}

void solve_case(void)
{
  int i;

  for (i = 0; i < 75; i++) {
    put_mark(numbers[i]);
    if (win()) {
      printf("BINGO after %d numbers announced\n", i+1);
      return;
    }
  }
}

int main(void)
{
  int n;

  scanf("%d", &n);
  while (n-- > 0) {
    read_case();
    solve_case();
  }

  return 0;
}
