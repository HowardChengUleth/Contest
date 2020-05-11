/* @JUDGE_ID: 1102NT 10586 C "" */

#include <stdio.h>

int main(void)
{
  int r[10001], a[10001], n, k, i, j, sign, d;

  while (scanf("%d %d", &n, &k) == 2 && (n >= 0 && k >= 0)) {
    for (i = 0; i <= n; i++) {
      scanf("%d", a+i);
    }
    for (i = 0; i <= k-1; i++) {
      r[i] = 0;
    }

    sign = 1;
    j = 0;
    for (i = 0; i <= n; i++) {
      r[j++] += sign*a[i];
      if (j >= k) {
	j = 0;
	sign *= -1;
      }
    }

    for (d = k-1; d >= 0 && !r[d]; d--) ;
    if (d < 0) {
      printf("0\n");
    } else {
      for (i = 0; i <= d; i++) {
	if (i) {
	  printf(" ");
	}
	printf("%d", r[i]);
      }
      printf("\n");
    }
  }

  return 0;
}
