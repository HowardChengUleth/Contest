/* @JUDGE_ID: 1102NT 10465 C "" */

#include <stdio.h>

void solve_case(int m, int n, int t)
{
  int best[10000];
  int i;

  best[0] = 0;
  for (i = 1; i <= t; i++) {
    best[i] = -1;
    if (i-m >= 0 && best[i-m] >= 0) {
      best[i] = 1 + best[i-m];
    }
    if (i-n >= 0 && best[i-n] >= 0) {
      if (1+best[i-n] > best[i]) {
	best[i] = 1 + best[i-n];
      }
    }
  }

  for (i = t; i >= 0; i--) {
    if (best[i] >= 0) {
      printf("%d", best[i]);
      if (i < t) {
	printf(" %d", t-i);
      }
      printf("\n");
      break;
    }
  }
}

int main(void)
{
  int m, n, t;

  while (scanf("%d %d %d", &m, &n, &t) == 3) {
    solve_case(m, n, t);
  }
  return 0;
}
