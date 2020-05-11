/* @JUDGE_ID: 1102NT 507 C "" */

/*
 * Largest subvector sum
 *
 * Author: Howard Cheng
 * Reference: Programming Pearl, page 74
 *
 * Given an array of integers, we find the continguous subvector that
 * gives the maximum sum.  If all entries are negative, it returns
 * an empty vector with sum = 0.
 *
 * If we want the subvector to be nonempty, we should first scan for the
 * largest element in the vector (1-element subvector) and combine the
 * result in this routine.
 *
 * The sum is returned, as well as the start and the end position
 * (inclusive).  If start > end, then the subvector is empty.
 *
 */

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
  int b, r, s, i;
  int n[20000];
  int sum, start, end;

  scanf("%d", &b);
  for (r = 1; r <= b; r++) {
    scanf("%d", &s);
    for (i = 0; i < s-1; i++) {
      scanf("%d", n+i);
    }
    sum = vecsum(n, s-1, &start, &end);
    if (sum > 0) {
      printf("The nicest part of route %d is between stops %d and %d\n",
	     r, start+1, end+2);
    } else {
      printf("Route %d has no nice parts\n", r);
    }
  }

  return 0;
}
