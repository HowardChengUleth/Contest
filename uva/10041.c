/* @JUDGE_ID: 1102NT 10041 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

int cmp(const void *a, const void *b)
{
   return *(int *)a - *(int *)b;
}

int main(void)
{
  int cases, r, s[500], i, median, d;

  scanf("%d", &cases);
  while (cases-- > 0) {
     scanf("%d", &r);
     for (i = 0; i < r; i++) {
	scanf("%d", s+i);
     }
     qsort(s, r, sizeof(int), cmp);

     median = (r % 2) ? s[r/2] : (int)floor((s[r/2] + s[r/2-1])*0.5 + 0.5);

     d = 0;
     for (i = 0; i < r; i++) {
	d += (s[i] > median) ? s[i] - median : median - s[i];
     }
     printf("%d\n", d);
  }
  
  return 0;
}
