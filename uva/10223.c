#include <stdio.h>

int main(void)
{
  long long binom[39][39];

  int n, k;
  long long t;

  for (n = 0; n <= 38; n++) {
    binom[n][0] = binom[n][n] = 1;
    for (k = 1; k < n; k++) {
      binom[n][k] = binom[n-1][k] + binom[n-1][k-1];
    }
  }

  while (scanf("%lld", &t) == 1) {
    for (n = 1; n <= 19; n++) {
      if (binom[2*n][n]/(n+1) == t) {
	printf("%d\n", n);
	break;
      }
    }
  }
  return 0;
}
