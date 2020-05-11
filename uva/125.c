#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_NODE 30
#define DISCONNECT 0

void find_cycle(char graph[MAX_NODE][MAX_NODE], 
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
	graph2[i][j] |= (graph2[i][k] && graph2[k][j]);
      }
    }
  }

  for (k = 0; k < n; k++) {
    if (graph2[k][k]) {
      for (i = 0; i < n; i++) {
	for (j = 0; j < n; j++) {
	  if (graph2[i][k] && graph2[k][j]) {
	    paths[i][j] = -1;
	  }
	}
      }
    }
  }
}

void find_paths(char graph[MAX_NODE][MAX_NODE], 
		int paths[MAX_NODE][MAX_NODE],
		int n)
{
  int i, j, k;
  
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (paths[i][j] != -1 && graph[i][j]) {
	paths[i][j] = 1;
      }
    }
  }
  
  for (k = 0; k < n; k++) {
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
	if (paths[i][j] == -1) continue;

	/* I now know that if paths[i][k] or paths[k][j] == -1, then the
	   other one must be 0 */

	paths[i][j] += paths[i][k] * paths[k][j];
      }
    }
  }

}

void compute_paths(char graph[MAX_NODE][MAX_NODE], 
		   int paths[MAX_NODE][MAX_NODE], int n)
{
  find_cycle(graph, paths, n);
  find_paths(graph, paths, n);
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
	graph[i][j] = 0;
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
