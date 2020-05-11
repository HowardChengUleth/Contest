#include <stdio.h>
#include <string.h>

int weight(char *s)
{
  int A[80][80];
  int n = strlen(s);
  int i, j, k, l, m, p;
  int good;

  for (i = 0; i < n; i++) {
    A[i][i] = 1;
  }

  for (k = 2; k <= n; k++) {
    for (i = 0, j = k-1; i < n && j < n; i++, j++) {
      /* assume the worst */
      A[i][j] = k;
      
      /* now see if we can get a better one by concatenating */
      for (l = i; l < j; l++) {
	if (A[i][l] + A[l+1][j] < A[i][j]) {
	  A[i][j] = A[i][l] + A[l+1][j];
	}
      }

      /* now check if it is a power */
      for (l = 1; l <= k; l++) {
	if (k % l) continue;

	good = 1;
	for (m = i; m < i+l && good; m++) {
	  for (p = m+l; p <= j && good; p += l) {
	    if (s[m] != s[p]) {
	      good = 0;
	    }
	  }
	}
	if (good) {
	  A[i][j] = A[i][i+l-1];
	}
      }
    }
  }

  /*
  printf("     ");
  for (j = 0; j < n; j++) {
    printf("%3d", j);
  }
  printf("\n");
  for (i = 0; i < n; i++) {
    printf("%3d: ", i);
    for (j = 0; j < n; j++) {
      printf("%3d", A[i][j]);
    }
    printf("\n");
  }
  */

  return A[0][n-1];
}

int main(void)
{
  char s[100];

  while (scanf("%s", s) == 1 && strcmp(s, "*")) {
    printf("%d\n", weight(s));
  }
  return 0;
}
