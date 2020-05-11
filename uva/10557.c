/* @JUDGE_ID: 1102NT 10557 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#define MAX_NODES  101
#define DISCONNECT INT_MAX

int main(void)
{
  int graph[MAX_NODES][MAX_NODES];
  int last[MAX_NODES];
  int n;
  int w, m, d;
  int i, j, k;
  char winnable;

  while (scanf("%d", &n) == 1 && n != -1) {
    /* clear graph */
    for (i = 0; i <= n; i++) {
      for (j = 0; j <= n; j++) {
	graph[i][j] = DISCONNECT;
      }
    }
    graph[0][1] = -100;

    /* read graph */
    for (i = 1; i <= n; i++) {
      scanf("%d %d", &w, &m);
      for (j = 0; j < m; j++) {
	scanf("%d", &d);
	graph[i][d] = -w;
      }
    }

    /* look for negative cycles that are reachable with Bellman-Ford */
    for (i = 0; i <= n; i++) {
      last[i] = 0;
    }
    for (k = 0; k <= n; k++) {
      for (i = 0; i <= n; i++) {
	for (j = 0; j <= n; j++) {
	  if (graph[i][j] != DISCONNECT && graph[0][i] < 0) {
	    int temp = graph[0][i] + graph[i][j];
	    if (graph[0][j] == DISCONNECT || temp < graph[0][j]) {
	      graph[0][j] = temp;
	      last[j] = k;
	    }
	  }
	}
      }
    }

    /* maybe we don't need to pick up negative cycles */
    winnable = (graph[0][n] < 0);
    
    if (!winnable) {
      /* look for reachability */
      for (i = 0; i <= n; i++) {
	for (j = 0; j <= n; j++) {
	  graph[i][j] = (graph[i][j] != DISCONNECT);
	}
      }
      for (k = 0; k <= n; k++) {
	for (i = 0; i <= n; i++) {
	  for (j = 0; j <= n; j++) {
	    graph[i][j] |= (graph[i][k] && graph[k][j]);
	  }
	}
      }
      
      /* those with last[j] == n must participate in a negative cycle */
      for (i = 0; i <= n && !winnable; i++) {
	winnable |= (last[i] == n && graph[i][n]);
      }
    }

    printf("%s\n", (winnable) ? "winnable" : "hopeless");
  }
  return 0;
}
