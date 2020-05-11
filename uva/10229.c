#include <stdio.h>

void multiply(int A[2][2], int B[2][2], int mask)
{
  int C[2][2];
  int i, j, k;

  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      C[i][j] = 0;
      for (k = 0; k < 2; k++) {
	C[i][j] = (C[i][j] + ((A[i][k] * B[k][j]) & mask)) & mask;
      }
    }
  }

  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      A[i][j] = C[i][j];
    }
  }

}

void solve(int n, int m)
{
  int mask = (1 << m) - 1;
  int matrix[2][2] = { {0, 1},
		       {1, 1} };

  int result[2][2] = { {1, 0},
		       {0, 1} };
  
  while (n > 0) {
    if (n & 0x01) {
      n--;
      multiply(result, matrix, mask);
    } else {
      n >>= 1;
      multiply(matrix, matrix, mask);
    }
  }
  printf("%d\n", result[0][1]);

}

int main(void)
{
  int n, m;

  while (scanf("%d %d", &n, &m) == 2) {
    solve(n, m);
  }
  return 0;
}
