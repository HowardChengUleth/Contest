#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int n;
  int A[100][100];
  int i, j, k;
  char str[1024];
  int ans;

  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    A[i][i] = 0;
    for (j = 0; j < i; j++) {
      scanf("%s", str);
      if (str[0] == 'x') {
	A[i][j] = A[j][i] = -1;
      } else {
	A[i][j] = A[j][i] = atoi(str);
      }
    }
  }

  for (k = 0; k < n; k++) {
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
	if (A[i][k] >= 0 && A[k][j] >= 0) {
	  if (A[i][j] < 0 || A[i][k] + A[k][j] < A[i][j]) {
	    A[i][j] = A[i][k] + A[k][j];
	  }
	}
      }
    }
  }

  ans = 0;
  for (i = 0; i < n; i++) {
    if (A[0][i] > ans) {
      ans = A[0][i];
    }
  }

  printf("%d\n", ans);

  return 0;
}
