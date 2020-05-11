#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_NODE 30
#define DISCONNECT 0

void floyd(char graph[MAX_NODE][MAX_NODE], 
	   int paths[MAX_NODE][MAX_NODE],
	   int n)
{
  int i, j, k;
  char graph2[MAX_NODE][MAX_NODE];
  
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      graph2[i][j] = graph[i][j];
    }
  }
  
  for (k = 0; k < n; k++) {
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
	if (graph2[i][k] != DISCONNECT && graph2[k][j] != DISCONNECT) {
	  graph2[i][j] = 1;
	}
      }
    }
  }

  for (k = 0; k < n; k++) {
    if (graph2[k][k] != DISCONNECT) {
      for (i = 0; i < n; i++) {
	for (j = 0; j < n; j++) {
	  if (graph2[i][k] != DISCONNECT && graph2[k][j] != DISCONNECT) {
	    paths[i][j] = -1;
	  }
	}
      }
    }
  }
}

void DFS(char graph[MAX_NODE][MAX_NODE], 
	 int paths[MAX_NODE][MAX_NODE], 
	 int n, int node, int start, char *visited)
{
  int i;

  visited[node] = 1;
  for (i = 0; i < n; i++) {
    if (graph[node][i] != DISCONNECT) {
      if (paths[start][i] != -1) {
	paths[start][i]++;
      }
      if (!visited[i] && paths[i][i] != -1) {
	DFS(graph, paths, n, i, start, visited);
      }
    }
  }
  visited[node] = 0;
}

void compute_paths(char graph[MAX_NODE][MAX_NODE], 
		   int paths[MAX_NODE][MAX_NODE], int n)
{
  int i;
  char visited[MAX_NODE];

  floyd(graph, paths, n);
  for (i = 0; i < n; i++) {
    visited[i] = 0;
  }
  for (i = 0; i < n; i++) {
    if (paths[i][i] != -1) {
      DFS(graph, paths, n, i, i, visited);
    }
  }
}

int main(void)
{
  char graph[MAX_NODE][MAX_NODE];
  int paths[MAX_NODE][MAX_NODE];
  int n, m, i, j, n1, n2;
  int count = 0;

  while (scanf("%d", &m) == 1) {
    /* initialize data structures */
    n = 0;
    for (i = 0; i < MAX_NODE; i++) {
      for (j = 0; j < MAX_NODE; j++) {
	graph[i][j] = DISCONNECT;
	paths[i][j] = 0;
      }
    }

    /* read graphs */
    for (i = 0; i < m; i++) {
      scanf("%d %d", &n1, &n2);
      graph[n1][n2] = 1;
      if (n1 > n) {
	n = n1;
      }
      if (n2 > n) {
	n = n2;
      }
    }
    n++;

    /* compute paths */
    compute_paths(graph, paths, n);

    /* print result */
    printf("matrix for city %d\n", count++);
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
	printf("%d", paths[i][j]);
	if (j < n-1) {
	  printf(" ");
	}
      }
      printf("\n");
    }
  }
  return 0;
}
