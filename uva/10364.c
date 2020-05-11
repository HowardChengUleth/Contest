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
  char used[10001];
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

  memset(used, 0, 10001);
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

void solve()
{
  int n, i;
  int list[20];
  int sum, len;
  int found;

  while (scanf("%d", &n) == 1 && n != 0) {
    sum = 0;
    for (i = 0; i < n; i++) {
      scanf("%d", &(list[i]));
      sum += list[i];
    }
    qsort(list, n, sizeof(int), cmp);
    
    found = 0;
    len = sum / 4;
    if (sum % 4 == 0) {
      if (fit(1, len, n, list, list[0], 0)) {
	found = 1;
      }
    }

    if (found) {
      printf("yes\n");
    } else {
      printf("no\n");
    }
  }
  
}

int main(void)
{
  int n;
  scanf("%d", &n);
  while (n--) {
    solve();
  }
  return 0;
}
