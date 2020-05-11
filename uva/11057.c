#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
  return *(int *)a - *(int *)b;
}

int main(void)
{
  int N, M;
  int prices[10000];
  int i, best, i2;

  while (scanf("%d", &N) == 1) {
    for (i = 0; i < N; i++) {
      scanf("%d", prices+i);
    }
    scanf("%d", &M);
    qsort(prices, N, sizeof(*prices), cmp);
    
    best = -1;
    for (i = 0; i < N; i++) {
      i2 = M - prices[i];
      if (i2 < prices[i]) break;
      if (bsearch(&i2, prices, N, sizeof(*prices), cmp)) {
	if (best == -1 || i2 - prices[i] < M - 2*best) {
	  best = prices[i];
	}
      }
    }
    printf("Peter should buy books whose prices are %d and %d.\n\n",
	   best, M-best);
    
  }
  return 0;
}
