/* @JUDGE_ID: 1102NT 558 C "Depth-first search" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int G[1000][1000];
int n, m;
int visited[1000];
int len[1000];

int DFS(int u)
{
  int v, l;

  visited[u] = 1;
  for (v = 0; v < n; v++) {
    if (G[u][v] > 1000) {
      continue;
    }
    if (visited[v]) {
      l = len[u] - len[v] + G[u][v];
      if (l < 0) {
	return 1;
      }

    } else {
      len[v] = len[u] + G[u][v];
      if (DFS(v)) {
	return 1;
      }
    }
  }

  return 0;
}

int main(void)
{
  int c, i, j, u, v;

  scanf("%d", &c);
  while (c-- > 0) {
    scanf("%d %d", &n, &m);
    
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
	G[i][j] = 1001;
      }
    }
    for (i = 0; i < m; i++) {
      scanf("%d %d", &u, &v);
      scanf("%d", &(G[u][v]));
    }
    
    for (i = 0; i < n; i++) {
      visited[i] = 0;
    }
    len[0] = 0;
    if (DFS(0)) {
      printf("possible\n");
    } else {
      printf("not possible\n");
    }
  }
  return 0;
}
