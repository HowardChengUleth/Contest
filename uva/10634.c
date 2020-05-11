/* @JUDGE_ID: 1102NT 10634 C "" */

#include <stdio.h>

unsigned long long ans[1001][1001];
unsigned long long binomial[2000][1001];

void init(void)
{
  int n, v, k;

  for (n = 0; n < 2000; n++) {
    binomial[n][0] = 1;
    if (n < 1001) {
      binomial[n][n] = 1;
    }
    for (k = 1; k < n && k < 1001; k++) {
      binomial[n][k] = binomial[n-1][k] + binomial[n-1][k-1];
    }
  }

  for (v = 0; v <= 1000; v++) {
    ans[0][v] = 1;    /* just the constant term */
    ans[1][v] = v;    /* just the degree 1 term */
  }

  for (n = 2; n <= 1000; n++) {
    ans[n][0] = (n % 2) ? 1 : 0;
    for (v = 1; v <= 1000; v++) {
      /* ans[n][v] = ans[n-2][v] + number of ways to write the sum
	 i_1 + i_2 + ... + i_v = n with i_j >= 0 */
      ans[n][v] = ans[n-2][v] + binomial[n+v-1][n];
    }

  }
}

int main(void)
{
  int n, v;

  init();
  while (scanf("%d %d", &n, &v) == 2 && (n || v)) {
    printf("%llu\n", ans[n][v]);
  }
  return 0;
}
