/* @JUDGE_ID: 1102NT 558 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

typedef struct {
  int from, to, weight;
} Edge;

int n, m;
Edge edgelist[2000];

void bellmanford(Edge *edgelist, int n, int src, int *D)
{
  int v, w, t, k, i, changed;

  for (v = 0; v < n; v++) {
    D[v] = INT_MAX;
  }
  D[0] = 0;
  changed = -1;

  for (k = 0; k < n; k++) {
    for (i = 0; i < m; i++) {
      v = edgelist[i].from;
      w = edgelist[i].to;
      t = edgelist[i].weight;

      if (D[v] != INT_MAX) {
	if (D[w] == INT_MAX || D[w] > D[v] + t) {
	  D[w] = D[v] + t;
	  changed = k;
	}
      }
    }
  }
  if (changed == n-1) {
    printf("possible\n");
  } else {
    printf("not possible\n");
  }
}

int main(void)
{
  int c, i, D[1000];

  scanf("%d", &c);
  while (c-- > 0) {
    scanf("%d %d", &n, &m);
    for (i = 0; i < m; i++) {
      scanf("%d %d %d", &(edgelist[i].from), &(edgelist[i].to),
	    &(edgelist[i].weight));
    }
    bellmanford(edgelist, n, 0, D);
  }
  
  return 0;
}

