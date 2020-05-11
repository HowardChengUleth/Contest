#include <stdio.h>

unsigned long long binom[71][71];

void init(void)
{
  int n, k;

  for (n = 0; n <= 70; n++) {
    binom[n][0] = binom[n][n] = 1;
    for (k = 1; k < n; k++) {
      binom[n][k] = binom[n-1][k] + binom[n-1][k-1];
    }
  }
}

int main(void)
{
  int K;
  int N, T, P;

  init();
  scanf("%d", &K);
  while (K-- > 0) {
    scanf("%d %d %d", &N, &T, &P);
    

    printf("%llu\n", binom[T-N*P+N-1][N-1]);
  }
  
  return 0;
}
