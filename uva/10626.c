#include <stdio.h>
#include <limits.h>

int ans[151][151][51];

int C, n1, n2, n3;

int compute(int C_left, int num5, int num10)
{
  int num1, best, temp;

  if (!C_left) {
    /* no more coke to buy, 0 coins */
    return ans[C_left][num5][num10] = 0;
  }
  if (ans[C_left][num5][num10] >= 0) {
    /* already computed, just return its value */
    return ans[C_left][num5][num10];
  }
  
  /* try all the different ways of buying one coke */
  num1 = n1 + 5*n2 + 10*n3 - 8*(C-C_left) - num5 - num10;

  best = INT_MAX;
  
  if (num1 >= 8) {
    temp = compute(C_left-1, num5, num10) + 8;
    if (temp < best) best = temp;
  }
  if (num5 >= 1 && num1 >= 3) {
    temp = compute(C_left-1, num5-1, num10) + 4;
    if (temp < best) best = temp;
  }
  if (num10 >= 1 && num1 >= 3) {
    temp = compute(C_left-1, num5+1, num10-1) + 4;
    if (temp < best) best = temp;
  }
  if (num5 >= 2) {
    temp = compute(C_left-1, num5-2, num10) + 2;
    if (temp < best) best = temp;
  }
  if (num10 >= 1) {
    temp = compute(C_left-1, num5, num10-1) + 1;
    if (temp < best) best = temp;
  }
    
  return ans[C_left][num5][num10] = best;
}

int main(void)
{
  int i, j, k;
  int cases;

  for (i = 0; i <= 150; i++) {
    for (j = 0; j <= 150; j++) {
      for (k = 0; k <= 50; k++) {
	ans[i][j][k] = -1;
      }
    }
  }

  scanf("%d", &cases);
  while (cases--) {
    scanf("%d %d %d %d", &C, &n1, &n2, &n3);
    printf("%d\n", compute(C, n2, n3));
  }

  return 0;
}
