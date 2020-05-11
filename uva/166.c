#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <limits.h>

int val[6] = {5, 10, 20, 50, 100, 200};

int best_change(int n)
{
  int i;
  int count = 0;

  i = 5;
  while (n) {
    assert(i >= 0);
    if (n >= val[i]) {
      count++;
      n -= val[i];
    } else {
      i--;
    }
  }
  return count;
}

int best_comb(int coins[6], int n)
{
  int i;
  int count = 0;
  int used[6];

  for (i = 0; i < 6; i++) {
    used[i] = 0;
  }

  i = 5;
  while (n) {
    if (i < 0) {
      return -1;
    }
    if (used[i] < coins[i] && n >= val[i]) {
      count++;
      n -= val[i];
      used[i]++;
    } else {
      i--;
    }
  }
  return count;
}

int main(void)
{
  int coins[6];
  int i;
  int total;
  double price;
  int trans;
  int best;
  int t;

  while (1) {
    total = 0;
    for (i = 0; i < 6; i++) {
      scanf("%d", coins+i);
      total += val[i] * coins[i];
    }
    if (total > 700) total = 700;   /* no need to go that high */
    if (!total) break;
    scanf("%lf", &price);
    trans = floor(price * 100 + 0.5);
    
    best = INT_MAX;
    for (i = trans; i <= total; i++) {
      if ((t = best_comb(coins, i)) < 0) {
	continue;
      }
      t += best_change(i-trans);
      if (t < best) {
	best = t;
      }
    }
    printf("%3d\n", best);
  }
  return 0;
}
