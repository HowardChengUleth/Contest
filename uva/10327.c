/* @JUDGE_ID: 1102NT 10327 C "" */

#include <stdio.h>

int main(void)
{
  int A[1000];
  int n, i, j, inv;

  while (scanf("%d", &n) == 1) {
    inv = 0;
    for (i = 0; i < n; i++) {
      scanf("%d", A+i);
      for (j = 0; j < i; j++) {
	if (A[j] > A[i]) {
	  inv++;
	}
      }
    }
    printf("Minimum exchange operations : %d\n", inv);
  }

  return 0;
}
