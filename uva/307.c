/* @JUDGE_ID: 1102NT 307 C "" */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int cmp(const void *a, const void *b)
{
  int x = *((int *)a);
  int y = *((int *)b);

  return y - x;
}

void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

int fit(int start, int len, int n, int *list, int sum, int check)
{
  char used[60];
  int i, t;

  /* check if it's okay */
  if (sum > len) {
    return 0;
  } else if (sum == len) {
    sum = 0;
  }
  if (start == n) {
    assert(sum == 0);
    return 1;
  }

  /* do the recursion */

  /* start a new stick, so we can skip the permutation */
  if (sum == 0) {
    return fit(start+1, len, n, list, list[start], 0);
  }

  memset(used, 0, 60);
  for (i = start; i < n; i++) {
    t = list[i];
    if (!used[t] && (!check || t <= list[start-1])) {
      used[t] = 1;

      /* swap */
      swap(&(list[i]), &(list[start]));

      /* recurse */
      if (fit(start+1, len, n, list, sum+list[start], 1)) {
	return 1;
      }

      /* swap back */
      swap(&(list[i]), &(list[start]));
    }
  }
  return 0;
}

int main(void)
{
  int n, i;
  int *list, *list2;
  int sum, len, num_sticks;
  int found;

  while (scanf("%d", &n) == 1 && n != 0) {
    sum = 0;
    list = (int *)malloc(n * sizeof(int));
    list2 = (int *)malloc(n * sizeof(int));
    assert(list && list2);
    for (i = 0; i < n; i++) {
      scanf("%d", &(list[i]));
      sum += list[i];
    }
    qsort(list, n, sizeof(int), cmp);
    
    found = 0;
    for (len = list[0]; len <= sum/2 && !found; len++) {
      if (sum % len == 0) {
	num_sticks = sum / len;
	memcpy(list2, list, n*sizeof(int));
	if (fit(1, len, n, list2, list2[0], 0)) {
	  found = 1;
	  printf("%d\n", len);
	}
      }
    }
    if (!found) {
      /* longest stick is longer than half, so there must be one stick only */
      printf("%d\n", sum);
    }

    free(list);
    free(list2);
  }
  
  return 0;
}
