#include <stdio.h>

long long ways[21][10000];

int main(void)
{
  int i, k, j;

  ways[0][0] = 1;
  for (i = 1; i < 10000; i++) {
    ways[0][i] = 1;
  }

  for (k = 1; k < 21; k++) {
    ways[k][0] = 1;
    for (i = 1; i < 10000; i++) {
      ways[k][i] = ways[k-1][i];
      j = k+1;
      if (j*j*j <= i) {
	ways[k][i] += ways[k][i-j*j*j];
      }
    }
  }
  
  while (scanf("%d", &i) == 1) {
    printf("%lld\n", ways[20][i]);
  }
  return 0;
}
