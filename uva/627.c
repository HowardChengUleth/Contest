/* @JUDGE_ID: 1102NT 627 C "" */

/*
 * Shortest Path with BFS
 *
 * Author: Howard Cheng
 *
 * Given a graph represented by an adjacency list, this algorithm uses
 * BFS to find the shortest path from a source vertex to each of the
 * other vertices.  The distances from the source to v is given in D[v], and
 * D[v] is set to -1 if the source vertex is not connected to w.  Also,
 * the shortest path tree is stored in the array P.
 *
 * Call get_path to recover the path.
 * 
 * Note: All edges must have the same cost for this to work.
 *       This algorithm has complexity O(n+m).
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_NODES 300

typedef struct {
  int deg;           /* number of outgoing edges */
  int adj[50];
} Node;

int min(int x, int y)
{
  return (x < y) ? x : y;
}

void BFS_shortest_path(Node graph[MAX_NODES], int n, int src, int D[MAX_NODES],
		       int P[MAX_NODES])
{
  char used[MAX_NODES];
  int queue[MAX_NODES+1];
  int q_in, q_out, i;
  int v, w;

  memset(used, 0, MAX_NODES);
  queue[0] = src;
  used[src] = 1;
  q_in = 1;
  q_out = 0;
  
  for (i = 0; i < MAX_NODES; i++) {
    D[i] = -1;
    P[i] = -1;
  }
  D[src] = 0;

  while (q_out < q_in) {
    v = queue[q_out++];
    for (i = 0; i < graph[v].deg; i++) {
      w = graph[v].adj[i];
      if (!used[w]) {
	D[w] = D[v] + 1;
	P[w] = v;
	queue[q_in++] = w;
	used[w] = 1;
      } else if (D[v] + 1 == D[w]) {
	/* put tie-breaker here */
	/* eg. find smallest path in lexicographic order, when the path */
        /*     is considered in REVERSE!                               */
	P[w] = min(P[w], v);
      }
    }
  }
}

void clear(Node graph[MAX_NODES], int n)
{
  int i;
  for (i = 0; i < n; i++) {
    graph[i].deg = 0;
  }
}

void add_edge(Node graph[MAX_NODES], int v, int w)
{
  graph[v].adj[graph[v].deg] = w;
  graph[v].deg++;
}

int get_path(int v, int *P, int *path)
{
  int A[MAX_NODES];
  int i, k;

  k = 0;
  A[k++] = v;
  while (P[v] != -1) {
    v = P[v];
    A[k++] = v;
  }
  for (i = k-1; i >= 0; i--) {
    path[k-1-i] = A[i];
  }
  return k;
}

int read_graph(Node *graph)
{
  char buffer[1024], *p;
  int n, i, v, w;
  
  if (scanf("%d\n", &n) != 1) {
    return 0;
  }
  clear(graph, n);
  for (i = 0; i < n; i++) {
    fgets(buffer, 1024, stdin);
    p = strtok(buffer, "-, \n");
    w = atoi(p) - 1;
    while (p = strtok(0, "-, \n")) {
      v = atoi(p) - 1;
      add_edge(graph, v, w);
    }
  }

  return n;
}

int main(void)
{
  Node graph[MAX_NODES];
  int n, m, i;
  int D[MAX_NODES], P[MAX_NODES], path[MAX_NODES];
  int src, dest;

  while (n = read_graph(graph)) {
    printf("-----\n");
    scanf("%d", &m);
    while (m-- > 0) {
      scanf("%d %d", &src, &dest);
      src--;
      dest--;
      BFS_shortest_path(graph, n, dest, D, P);
      if (D[src] == -1) {
	printf("connection impossible\n");
      } else {
	get_path(src, P, path);
	for (i = D[src]; i >= 0; i--) {
	  printf("%d", path[i]+1);
	  if (i) {
	    printf(" ");
	  }
	}
	printf("\n");
      }
    }
  }
  return 0;
}
