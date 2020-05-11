/* @JUDGE_ID: 1102NT 10600 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
  int a, b, cost, tree_edge;
} Edge;

int cmp(const void *a, const void *b)
{
  return ((Edge *)a)->cost - ((Edge *)b)->cost;
}

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

void solve_case(void)
{
  int N, M;
  Edge *edgelist;
  int i, j;
  UnionFind uf[100];
  int cost1, cost2, cost3;
  int edge_count;

  scanf("%d %d", &N, &M);
  edgelist = malloc(M*sizeof(*edgelist));
  assert(edgelist);
  
  for (i = 0; i < M; i++) {
    scanf("%d %d %d", &(edgelist[i].a), &(edgelist[i].b), &(edgelist[i].cost));
    if (edgelist[i].a > edgelist[i].b) {
      j = edgelist[i].a;
      edgelist[i].a = edgelist[i].b;
      edgelist[i].b = j;
    }
    edgelist[i].tree_edge = 0;
  }
  qsort(edgelist, M, sizeof(*edgelist), cmp);

  /* do the first tree */
  cost1 = 0;
  init_uf(uf, N);
  edge_count = 0;
  for (i = 0; i < M; i++) {
    if (find(uf, edgelist[i].a-1) != find(uf, edgelist[i].b-1)) {
      edgelist[i].tree_edge = 1;
      cost1 += edgelist[i].cost;
      merge(uf, edgelist[i].a-1, edgelist[i].b-1);
      edge_count++;
    }
  }

  assert(edge_count == N-1);

  cost2 = -1;
  for (i = 0; i < M; i++) {
    if (!edgelist[i].tree_edge) continue;
    cost3 = 0;
    init_uf(uf, N);
    edge_count = 0;
    for (j = 0; j < M; j++) {
      if (i != j && find(uf, edgelist[j].a-1) != find(uf, edgelist[j].b-1)) {
	cost3 += edgelist[j].cost;
	merge(uf, edgelist[j].a-1, edgelist[j].b-1);
	edge_count++;
      }
    }
    if (edge_count == N-1 && (cost2 < 0 || cost3 < cost2)) {
      cost2 = cost3;
    }
  }

  printf("%d %d\n", cost1, cost2);

  free(edgelist);

}

int main(void)
{
  int cases;

  scanf("%d", &cases);
  while (cases-- > 0) {
    solve_case();
  }
  return 0;
}
