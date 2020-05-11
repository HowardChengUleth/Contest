/* @JUDGE_ID: 1102NT 336 C "" */

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

#define MAX_NODES 40

typedef struct {
  int deg;           /* number of outgoing edges */
  int adj[MAX_NODES];
} Node;

void BFS_shortest_path(Node graph[MAX_NODES], int n, int src, int D[MAX_NODES])
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
  }
  D[src] = 0;

  while (q_out < q_in) {
    v = queue[q_out++];
    for (i = 0; i < graph[v].deg; i++) {
      w = graph[v].adj[i];
      if (!used[w]) {
	D[w] = D[v] + 1;
	queue[q_in++] = w;
	used[w] = 1;
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
  int i;

  graph[v].adj[graph[v].deg] = w;
  graph[v].deg++;
}

int n;
int nodes[MAX_NODES];

int find(int a)
{
  int i;
  for (i = 0; i < n; i++) {
    if (nodes[i] == a) {
      return i;
    }
  }
  assert(n <= MAX_NODES);
  nodes[n++] = a;
  return n-1;
}

int main(void)
{
  int cases;
  int m, u, v, a, b, i, count;
  Node graph[MAX_NODES];
  int D[MAX_NODES];
  
  cases = 1;
  while (scanf("%d", &m) == 1 && m > 0) {
    n = 0;
    clear(graph, MAX_NODES);
    for (i = 0; i < m; i++) {
      scanf("%d %d", &a, &b);
      u = find(a);
      v = find(b);
      add_edge(graph, u, v);
      add_edge(graph, v, u);
    }

    while (scanf("%d %d", &a, &b) == 2 && (a || b)) {
      BFS_shortest_path(graph, n, find(a), D);
      count = 0;
      for (i = 0; i < n; i++) {
	if (D[i] > b || D[i] == -1) count++;
      }
      printf("Case %d: %d nodes not reachable from node %d with TTL = %d.\n",
	     cases++, count, a, b);
    }
  }
  return 0;
}
