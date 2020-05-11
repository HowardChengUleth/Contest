/* @JUDGE_ID: 1102NT 387 C "" */


#include <stdio.h>
#include <assert.h>

int board[4][4];

char pieces[5][4][4];
int rows[5], cols[5];
int num;

int fit(int r, int c, int p)
{
  int i, j;

  for (i = 0; i < rows[p]; i++) {
    for (j = 0; j < cols[p]; j++) {
      if (((r+i >= 4 || c+j >= 4) && pieces[p][i][j]) || 
	  (pieces[p][i][j] && board[r+i][c+j])) {
	return 0;
      }
    }
  }
  return 1;
}

void put(int r, int c, int p)
{
  int i, j;

  for (i = 0; i < rows[p]; i++) {
    for (j = 0; j < cols[p]; j++) {
      if (pieces[p][i][j]) {
	board[r+i][c+j] = p+1;
      }
    }
  }
}

void clear(int r, int c, int p)
{
  int i, j;

  for (i = 0; i < rows[p]; i++) {
    for (j = 0; j < cols[p]; j++) {
      if (pieces[p][i][j]) {
	board[r+i][c+j] = 0;
      }
    }
  }
}

int search(int p)
{
  int r, c;

  if (p == num) {
    for (r = 0; r < 4; r++) {
      for (c = 0; c < 4; c++) {
	if (!board[r][c]) {
	  return 0;
	}
      }
    }
    for (r = 0; r < 4; r++) {
      for (c = 0; c < 4; c++) {
	printf("%d", board[r][c]);
      }
      printf("\n");
    }
    return 1;
  }

  for (r = 0; r < 4; r++) {
    for (c = 0; c < 4; c++) {
      if (fit(r, c, p)) {
	put(r, c, p);
	if (search(p+1)) {
	  return 1;
	}
	clear(r, c, p);
      }
    }
  }
  return 0;
}

int main(void)
{
  int i, j, k;
  char buffer[1024];
  char first = 1;

  while (scanf("%d", &num) == 1 && num > 0) {
    assert(num <= 5);
    for (i = 0; i < num; i++) {
      scanf("%d %d\n", rows+i, cols+i);
      assert(rows[i] <= 4 && cols[i] <= 4);
      for (j = 0; j < rows[i]; j++) {
	fgets(buffer, 1024, stdin);
	for (k = 0; k < cols[i]; k++) {
	  pieces[i][j][k] = (buffer[k] == '1');
	}
      }
    }

    if (first) {
      first = 0;
    } else {
      printf("\n");
    }

    for (i = 0; i < 4; i++) {
      for (j = 0; j < 4; j++) {
	board[i][j] = 0;
      }
    }

    if (!search(0)) {
      printf("No solution possible\n");
    }
  }
  return 0;
}
