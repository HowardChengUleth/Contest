#include <stdio.h>

int main(void)
{
  int binom[200][200];
  int n, k;


  /* precompute all binomial coefficients */
  for (n = 0; n <= 199; n++) {
    binom[n][0] = binom[n][n] = 1;
    for (k = 1; k < n; k++) {
      binom[n][k] = (binom[n-1][k] + binom[n-1][k-1]) % 1000000;
    }
  }

  while (scanf("%d %d", &n, &k) == 2 && (n || k)) {
    printf("%d\n", binom[n+k-1][k-1]);
  }

  return 0;
}
