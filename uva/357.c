/* @JUDGE_ID: 1102NT 357 C "" */


#include <stdio.h>

#define MAX_COINS 5
#define MAX_AMOUNT 30000

int coins[MAX_COINS] = { 1, 5, 10, 25, 50 };

/* ways[i][j] = # of ways to make amount j using coin types 0, ..., i */
long long ways[MAX_COINS][MAX_AMOUNT+1];     

void precompute(void)
{
  int i, j;

  for (j = 0; j <= MAX_AMOUNT; j++) {
    ways[0][j] = 1;
  }
  for (i = 1; i < MAX_COINS; i++) {
    for (j = 0; j <= MAX_AMOUNT; j++) {
      ways[i][j] = ways[i-1][j];
      if (j-coins[i] >= 0) {
	ways[i][j] += ways[i][j-coins[i]];
      }
    }
  }
}

int main(void)
{
  int amt;
  long long ans;

  precompute();
  while (scanf("%d", &amt) == 1) {
    if ((ans = ways[MAX_COINS-1][amt]) == 1) {
      printf("There is only 1 way to produce %d cents change.\n", amt);
    } else {
      printf("There are %lld ways to produce %d cents change.\n", ans, amt);
    }
  }

  return 0;
}
