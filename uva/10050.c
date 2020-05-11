/* @JUDGE_ID: 1102NT 10050 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void)
{
  int t, n, p, h;
  int i, j;
  char days[3651];
  int count;
  
  scanf("%d", &t);
  while (t-- > 0) {
    scanf("%d %d", &n, &p);
    for (i = 1; i <= n; i++) {
      days[i] = 0;
    }
    count = 0;
    for (i = 0; i < p; i++) {
      scanf("%d", &h);
      for (j = h; j <= n; j += h) {
	if (j % 7 != 6 && j % 7 != 0) {
	  if (!days[j]) {
	    days[j] = 1;
	    count++;
	  }
	}
      }
    }
    printf("%d\n", count);
  }
  return 0;
}
