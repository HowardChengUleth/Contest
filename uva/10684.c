#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int vecsum(int *v, int n, int *start, int *end)
{
  int maxval = 0;
  int max_end = 0;
  int max_end_start, max_end_end;
  int i;

  *start = max_end_start = 0;
  *end = max_end_end = -1;
  for (i = 0; i < n; i++) {
    if (v[i] + max_end >= 0) {
      max_end = v[i] + max_end;
      max_end_end = i;
    } else {
      max_end_start = i+1;
      max_end_end = -1;
      max_end = 0;
    }

    if (maxval < max_end) {
      *start = max_end_start;
      *end = max_end_end;
      maxval = max_end;
    } else if (maxval == max_end) {
      /* put whatever preferences we have for a tie */
      /* eg. longest subvector, and then the one that starts the earliest */
      if (max_end_end - max_end_start > *end - *start ||
          (max_end_end - max_end_start == *end - *start &&
           max_end_start < *start)) {
        *start = max_end_start;
        *end = max_end_end;
        maxval = max_end;
      }
    }
  }
  return maxval;
}

int main(void)
{
  int n;
  int v[10000];
  int i;
  int sum, start, end;

  while (scanf("%d", &n) == 1 && n > 0) {
    for (i = 0; i < n; i++) {
      scanf("%d", v+i);
    }
    sum = vecsum(v, n, &start, &end);
    if (sum <= 0) {
      printf("Losing streak.\n");
    } else {
      printf("The maximum winning streak is %d.\n", sum);
    }

  }

  return 0;
}
