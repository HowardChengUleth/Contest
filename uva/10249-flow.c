/* @JUDGE_ID: 1102NT 10249 C "" */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_NODE 130
#define MAX_DEG 100

typedef struct {
    int deg;
    int nbrs[MAX_DEG], cap[MAX_DEG], res[MAX_DEG];
} Node;

void clear_graph(Node *graph)
{
  int i;

  for (i = 0; i < MAX_NODE; i++) {
    graph[i].deg = 0;
  }
}

void add_edge(Node *graph, int u, int v, int cap)
{
  graph[u].nbrs[graph[u].deg] = v;
  graph[u].cap[graph[u].deg] = cap;
  graph[u].res[graph[u].deg++] = cap;
  graph[v].nbrs[graph[v].deg] = u;
  graph[v].cap[graph[v].deg] = 0;
  graph[v].res[graph[v].deg++] = 0;
}

/* the path is stored in a peculiar way for efficiency:

   Let v(i) be the index of the vertex in the i-th element of the path.
   Then v(i) is computed by graph[v(i-1)].nbrs[path[i]], where
   v(-1) = source vertex.
*/
   
int augmenting_path(Node *graph, int s, int t, int *path, char *visited, int
		    minflow)
{
  int i, v;
  
  if (s == t) {
    return 1;
  }
  for (i = 0; i < graph[s].deg; i++) {
    v = graph[s].nbrs[i];
    if (graph[s].res[i] >= minflow && !visited[v]) {
      path[0] = i;
      visited[v] = 1;
      if (augmenting_path(graph, v, t, path+1, visited, minflow)) {
	return 1;
      }
    }
  }
  return 0;
}

int push_path(Node *graph, int s, int t, int *path)
{
  int flow = -1;
  int v, w;
  int i, j;

  for (v = s, i = 0; v != t; v = w, i++) {
    w = graph[v].nbrs[path[i]];
    if (flow == -1 || flow > graph[v].res[path[i]]) {
      flow = graph[v].res[path[i]];
    }
  }
  
  for (v = s, i = 0; v != t; v = w, i++) {
    w = graph[v].nbrs[path[i]];
    graph[v].res[path[i]] -= flow;
    for (j = 0; j < graph[w].deg; j++) {
      if (graph[w].nbrs[j] == v) {
	graph[w].res[j] += flow;
	break;
      }
    }
  }
  
  return flow;
}

int network_flow(Node *graph, int s, int t)
{
  char visited[MAX_NODE];
  int path[MAX_NODE];
  int flow = 0, f = 1;
  int i, minflow;

  memset(visited, 0, MAX_NODE);
  while (f) {
    minflow = 0;
    for (i = 0; i < graph[s].deg; i++) {
      if (minflow < graph[s].res[i]) {
	minflow = graph[s].res[i];
      }
    }
    if (minflow) { minflow = 1; }
    for (f = 0; minflow; minflow /= 2) {
      memset(visited, 0, MAX_NODE);
      if (augmenting_path(graph, s, t, path, visited, minflow)) {
	f = push_path(graph, s, t, path);
	flow += f;
	break;
      }
    }
  }

  return flow;
}

#define SRC 0
#define SINK 1
#define TEAM(x) ((x)+2)
#define TABLE(x) ((x)+72)
#define INVTEAM(x) ((x)-2)
#define INVTABLE(x) ((x)-72)

int main(void)
{
  Node graph[MAX_NODE];
  int M, N, i, j, t, members, flow, first;
  int cases = 0;

  while (scanf("%d %d", &M, &N) == 2 && (M || N)) {
    assert(1 <= M && M <= 70);
    assert(1 <= N && N <= 50);
    cases++;
  
    clear_graph(graph);
    members = 0;
    for (i = 0; i < M; i++) {
      for (j = 0; j < N; j++) {
	add_edge(graph, TEAM(i), TABLE(j), 1);
      }
    }
    for (i = 0; i < M; i++) {
      scanf("%d", &t);
      add_edge(graph, SRC, TEAM(i), t);
      members += t;
    }
    for (i = 0; i < N; i++) {
      scanf("%d", &t);
      add_edge(graph, TABLE(i), SINK, t);
    }
  
    flow = network_flow(graph, SRC, SINK);
    if (flow < members) {
      printf("0\n");
    } else {
      printf("1\n");
      for (i = 0; i < M; i++) {
	first = 1;
	for (j = 0; j < graph[TEAM(i)].deg; j++) {
	  if (graph[TEAM(i)].cap[j] > graph[TEAM(i)].res[j]) {
	    if (!first) {
	      printf(" %d", INVTABLE(graph[TEAM(i)].nbrs[j])+1);
	    } else {
	      printf("%d", INVTABLE(graph[TEAM(i)].nbrs[j])+1);
	      first = 0;
	    }
	  }
	}
	printf("\n");
      }
    }
  }
  
  return 0;
}


