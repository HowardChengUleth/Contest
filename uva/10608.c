/* @JUDGE_ID: 1102NT 10608 C "" */

/*
 * Union-find algorithm for equivalence classes
 *
 * Author: Howard Cheng
 *
 * Given n labels (0, 1, ..., n-1), the union and find operations are
 * implemented for equivalence classes computation.
 *
 * Revised: 21 June 2000 by Howard Cheng <hchcheng@scg.math.uwaterloo.ca>
 *   - use weighted union (cf. Cormen, Leiserson, Rivest, Ch. 22) to improve
 *     amortized run time
 */

#include <stdio.h>
#include <stdlib.h>

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

int find(UnionFind *uf, int x)
{
  if (uf[x].p != x) {
    uf[x].p = find(uf, uf[x].p);
  }
  return uf[x].p;
}

void merge(UnionFind *uf, int x, int y)
{
  int res1, res2;

  res1 = find(uf, x);
  res2 = find(uf, y);
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
  int c, n, m;
  UnionFind uf[30000];
  int groups[30000];
  int a, b;
  int best;

  scanf("%d", &c);
  while (c-- > 0) {
    scanf("%d %d", &n, &m);
    init_uf(uf, n);
    while (m-- > 0) {
      scanf("%d %d", &a, &b);
      merge(uf, a-1, b-1);
    }
    for (a = 0; a < n; a++) {
      groups[a] = 0;
    }
    for (a = 0; a < n; a++) {
      groups[find(uf, a)]++;
    }
    best = groups[0];
    for (a = 1; a < n; a++) {
      if (groups[a] > best) {
	best = groups[a];
      }
    }
    printf("%d\n", best);
  }

  return 0;
}
