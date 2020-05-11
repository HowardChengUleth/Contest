#include <stdio.h>

int A[100][100];
int n;

int main(void)
{
  int i, j;
  int bad_row, bad_col, parity;

  while (scanf("%d", &n) == 1 && n) {
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
	scanf("%d", &A[i][j]);
      }
    }
    bad_row = bad_col = -1;
    for (i = 0; i < n; i++) {
      parity = 0;
      for (j = 0; j < n; j++) {
	parity += A[i][j];
      }
      if (parity % 2) {
	bad_row = (bad_row == -1) ? i : -2;
      }
    }
    for (j = 0; j < n; j++) {
      parity = 0;
      for (i = 0; i < n; i++) {
	parity += A[i][j];
      }
      if (parity % 2) {
	bad_col = (bad_col == -1) ? j : -2;
      }
    }

    if (bad_row == -1 && bad_col == -1) {
      printf("OK\n");
    } else if (bad_row >= 0 && bad_col >= 0) {
      printf("Change bit (%d,%d)\n", bad_row+1, bad_col+1);
    } else {
      printf("Corrupt\n");
    }
  }
  return 0;
}
