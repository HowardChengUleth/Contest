#include <stdio.h>

int main(void)
{
  int case_num = 1;
  int i, j, k, t;
  int D[21][21];
  int X, N, A, B;

  while (1) {
    for (i = 1; i <= 20; i++) {
      for (j = 1; j <= 20; j++) {
	D[i][j] = -1;
      }
      D[i][i] = 0;
    }
    for (i = 1; i <= 19; i++) {
      if (scanf("%d", &X) != 1) {
	return 0;
      }
      while (X-- > 0) {
	scanf("%d", &j);
	D[i][j] = D[j][i] = 1;
      }
    }
    
    for (k = 1; k <= 20; k++) {
      for (i = 1; i <= 20; i++) {
	for (j = 1; j <= 20; j++) {
	  if (D[i][k] != -1 && D[k][j] != -1) {
	    t = D[i][k] + D[k][j];
	    if (D[i][j] == -1 || t < D[i][j]) {
	      D[i][j] = t;
	    }
	  }
	}
      }
    }

    printf("Test Set #%d\n", case_num++);
    scanf("%d", &N);
    while (N-- > 0) {
      scanf("%d %d", &A, &B);
      printf("%2d to %2d: %d\n", A, B, D[A][B]);
    }
    printf("\n");
  }

}
