/* @JUDGE_ID: 1102NT 714 C "" */

#include <stdio.h>

#define MAX_M 500

int p[MAX_M];

int possible(int m, int k, long long mid, int start)
{
  int count, i;
  long long curr;

  curr = 0;
  count = 0;
  for (i = start; i < m; i++) {
    /* we know that p[i] <= mid */
    if ((curr += p[i]) > mid) {
      curr = p[i];
      count++;
    }
  }
  if (curr > 0) {
    count++;
  }
  return (count <= k);
}

void print_partition(int m, int k, long long max)
{
  int i, j;

  i = 0;
  while (i < m) {
    for (j = i; j+1 < m; j++) {
      if (possible(m, k-1, max, j+1))
	break;
    }

    /* since we know the partition is possible, we know we can go from */
    /* i to j without going over max.  We do not need to check it.     */
    while (i <= j) {
      printf("%s%d", i ? " " : "", p[i]);
      i++;
    }
    printf(" /");
    if (--k == 1) {
      while (i < m) {
	printf("%s%d", i ? " " : "", p[i]);
	i++;
      }
      printf("\n");
    }
  }
}

void solve(int m, int k)
{
  long long hi, lo, mid;
  int i;

  hi = lo = p[0];
  for (i = 1; i < m; i++) {
    hi += p[i];
    if (lo < p[i]) {
      lo = p[i];
    }
  }
  if (lo < hi/k-1) {
    lo = hi/k-1;
  }

  while (lo+1 < hi) {
    mid = (lo+hi)/2;
    if (possible(m, k, mid, 0)) {
      hi = mid;
    } else {
      lo = mid;
    }
  }
  print_partition(m, k, hi);
}

int main(void)
{
  int N, i;
  int m, k;

  scanf("%d", &N);
  while (N-- > 0) {
    scanf("%d %d", &m, &k);
    for (i = 0; i < m; i++) {
      scanf("%d", p+i);
    }
    solve(m, k);
  }
  return 0;
}
