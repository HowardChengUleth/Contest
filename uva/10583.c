/* @JUDGE_ID: 1102NT 10583 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50000

typedef struct {
  int p, rank;
} UnionFind;

void init_uf(UnionFind *uf, int n)
{
  int i;
  for (i = 0; i < n; i++) {
    uf[i].p = i;
    uf[i].rank = 0;
  }
}

int find(UnionFind *uf, int n, int x)
{
  if (uf[x].p != x) {
    uf[x].p = find(uf, n, uf[x].p);
  }
  return uf[x].p;
}

void merge(UnionFind *uf, int n, int x, int y)
{
  int res1, res2;

  res1 = find(uf, n, x);
  res2 = find(uf, n, y);
  if (res1 != res2) {
    if (uf[res1].rank > uf[res2].rank) {
      uf[res2].p = res1;
    } else {
      uf[res1].p = res2;
      if (uf[res1].rank == uf[res2].rank) {
	uf[res2].rank++;
      }
    }
  }
}

int main(void)
{
  int n, m;
  UnionFind uf[MAX_N];
  char used[MAX_N];
  int i, j, k;
  int case_no = 1;
  int count;
  
  while (scanf("%d %d", &n, &m) == 2 && (n || m)) {
    init_uf(uf, n);
    for (k = 0; k < m; k++) {
      scanf("%d %d", &i, &j);
      merge(uf, n, i-1, j-1);
    }

    memset(used, 0, MAX_N);
    count = 0;
    for (i = 0; i < n; i++) {
      k = find(uf, n, i);
      if (!used[k]) {
	used[k] = 1;
	count++;
      }
    }
    printf("Case %d: %d\n", case_no++, count);
  }

  return 0;
}
