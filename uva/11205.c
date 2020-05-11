#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

int cmp(const void *a, const void *b)
{
  return *(int *)a - *(int *)b;
}

int main(void)
{
  int N, P, symbol[MAX_N], symbol2[MAX_N];
  int ones[(1 << 15)];
  int cases;
  int x, i, j, b, good, best = -1;

  for (i = 0; i < (1 << 15); i++) {
    ones[i] = 0;
    x = i;
    while (x) {
      ones[i] += (x & 1);
      x >>= 1;
    }
  }

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%d %d", &P, &N);
    for (i = 0; i < N; i++) {
      symbol[i] = 0;
      for (j = 0; j < P; j++) {
	scanf("%d", &b);
	if (b) {
	  symbol[i] += (1 << j);
	}
      }
    }
      
    best = P;
    for (i = 0; i < (1 << P); i++) {
      for (j = 0; j < N; j++) {
	symbol2[j] = (symbol[j] & i);
      }
      qsort(symbol2, N, sizeof(int), cmp);
      good = 1;
      for (j = 0; j < N-1 && good; j++) {
	good &= (symbol2[j] != symbol2[j+1]);
      }
      if (good && ones[i] < best) {
	best = ones[i];
      }
    }
    printf("%d\n", best);
  }

  return 0;
}
