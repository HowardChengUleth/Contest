#include <stdio.h>

void solve(void)
{
  char possible[21][201];
  int M, C;
  int i, j, k;
  int K, price[20];

  for (i = 0; i <= 20; i++) {
    for (j = 0; j <= 200; j++) {
      possible[i][j] = 0;
    }
  }
  possible[0][0] = 1;

  scanf("%d %d", &M, &C);

  for (i = 0; i < C; i++) {
    scanf("%d", &K);
    for (k = 0; k < K; k++) {
      scanf("%d", price+k);
    }

    for (j = 0; j <= M; j++) {
      if (!possible[i][j]) continue;
      for (k = 0; k < K; k++) {
	if (j + price[k] <= M) {
	  possible[i+1][j+price[k]] = 1;
	}
      }
    }
  }

  for (i = M; i >= 0; i--) {
    if (possible[C][i]) {
      printf("%d\n", i);
      break;
    }
  }
  if (i < 0) {
    printf("no solution\n");
  }
}

int main(void)
{
  int N;
  scanf("%d", &N);
  while (N-- > 0) {
    solve();
  }
  return 0;
}
