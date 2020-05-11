/* @JUDGE_ID: 1102NT 591 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void)
{
  int n, i, set, sum, m;
  int h[50];
  
  set = 1;
  while (scanf("%d", &n) == 1 && n > 0) {
    sum = 0;
    for (i = 0; i < n; i++) {
      scanf("%d", &(h[i]));
      sum += h[i];
    }
    sum /= n;
    m = 0;
    for (i = 0; i < n; i++) {
      if (h[i] > sum) {
	m += h[i] - sum;
      }
    }
    printf("Set #%d\n", set++);
    printf("The minimum number of moves is %d.\n\n", m);

  }
  return 0;

}
