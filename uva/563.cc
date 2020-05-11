#include <iostream>

using namespace std;

/*
 * Network Flow
 *
 * Author: Howard Cheng
 *
 * The routine network_flow() finds the maximum flow that can be
 * pushed from the source (s) to the sink (t) in a flow network
 * (i.e. directed graph with capacities on the edges).  The maximum
 * flow is returned.  Note that the graph is modified, so that the
 * capacity is decreased by the amount pushed through the edge.  If
 * you wish to recover the flow on an edge, it is max(0,capacity - residual).
 *
 * Note: it is possible for the residual capacities of the resulting graph to
 *       be greater than original capacities.  This happens when a flow is
 *       pushed through an edge, and the "reverse edge" has its residual
 *       capacity increased.  Therefore, make sure you only take the
 *       difference if the difference is positive.
 *
 * Note: it is required that if (u,v) is an edge, then there must be
 *       an edge (v,u).  In the code below add_edge() simply adds
 *       (v,u) with capacity 0.  If the graph actually has edges in
 *       both directions, then use the given capacity instead of 0.
 *
 * This code can also be used for bipartite matching by setting up an
 * appropriate flow network.
 *
 * The code here assumes an adjacency list representation since most
 * problems requiring network flow have sparse graphs.
 *
 * This is the basic augmenting path algorithm and it is not the most
 * efficient.  But it should be good enough for most programming contest
 * problems.  The complexity is O(f m) where f is the size of the flow
 * and m is the number of edges.  This is good if you know that f
 * is small, but can be exponential if f is large.
 *
 */

#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAX_NODE = 50*50*2+2;
const int MAX_DEG = MAX_NODE-1;

struct Node {
    int deg;
    int nbrs[MAX_DEG], cap[MAX_DEG], res[MAX_DEG];
};

void clear_graph(Node graph[])
{
  int i;

  for (i = 0; i < MAX_NODE; i++) {
    graph[i].deg = 0;
  }
}

void add_edge(Node graph[], int u, int v, int cap)
{
  graph[u].nbrs[graph[u].deg] = v;
  graph[u].cap[graph[u].deg] = cap;
  graph[u].res[graph[u].deg++] = cap;

  /* WARNING: see note in comment at the top */
  graph[v].nbrs[graph[v].deg] = u;
  graph[v].cap[graph[v].deg] = 0;
  graph[v].res[graph[v].deg++] = 0;
}

void inc_or_add_edge(Node graph[], int u, int v, int cap)
{
  for (int i = 0; i < graph[u].deg; i++) {
    if (graph[u].nbrs[i] == v) {
      graph[u].cap[i] += cap;
      graph[u].res[i] += cap;
      return;
    }
  }
  add_edge(graph, u, v, cap);
}

/* the path is stored in a peculiar way for efficiency:

   Let v(i) be the index of the vertex in the i-th element of the path.
   Then v(i) is computed by graph[v(i-1)].nbrs[path[i]], where
   v(-1) = source vertex.
*/
   
int augmenting_path(Node graph[], int s, int t, int path[], char visited[],
		    int minflow)
{
  int i, v, flow;
  
  if (s == t) {
    return -1;
  }
  for (i = 0; i < graph[s].deg; i++) {
    v = graph[s].nbrs[i];
    if (graph[s].res[i] >= minflow && !visited[v]) {
      path[0] = i;
      visited[v] = 1;
      if ((flow = augmenting_path(graph, v, t, path+1, visited, minflow))) {
	if (flow == -1) {
	  return graph[s].res[i];
	} else {
	  return (flow < graph[s].res[i]) ? flow : graph[s].res[i];
	}
      }
    }
  }
  return 0;
}

void push_path(Node graph[], int s, int t, int path[], int flow)
{
  int v, w;
  int i, j;

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
}

int network_flow(Node graph[], int s, int t)
{
  char visited[MAX_NODE];
  int path[MAX_NODE];
  int flow = 0, f = 1;

  while (f) {
    fill(visited, visited+MAX_NODE, 0);
    if (f = augmenting_path(graph, s, t, path, visited, 1)) {
      push_path(graph, s, t, path, f);
      flow += f;
    }
  }

  return flow;
}

#define SOURCE 0
#define SINK 1

int in_node(int x, int y)
{
  return 2*((x-1)*50+(y-1)) + 2;
}

int out_node(int x, int y)
{
  return in_node(x, y) + 1;
}


Node graph[MAX_NODE];

void do_case(void)
{
  int s, a, b;
  cin >> s >> a >> b;

  clear_graph(graph);

  /* set up the graph */
  for (int x = 1; x <= s; x++) {
    for (int y = 1; y <= a; y++) {
      // node capacity
      add_edge(graph, in_node(x,y), out_node(x,y), 1);

      // grid
      if (x > 1) {
	add_edge(graph, out_node(x,y), in_node(x-1, y), 1);
      }
      if (x < s) {
	add_edge(graph, out_node(x,y), in_node(x+1, y), 1);
      }
      if (y > 1) {
	add_edge(graph, out_node(x,y), in_node(x, y-1), 1);
      }
      if (y < a) {
	add_edge(graph, out_node(x,y), in_node(x, y+1), 1);
      }
      
      // on outside edge
      if (x == 1 || x == s || y == 1 || y == a) {
	add_edge(graph, out_node(x,y), SINK, 1);
      }      
    }
  }

  /* set up the banks */
  for (int i = 0; i < b; i++) {
    int x, y;
    cin >> x >> y;
    inc_or_add_edge(graph, SOURCE, in_node(x, y), 1);
  }

  int flow;
  if ((flow = network_flow(graph, SOURCE, SINK)) == b) {
    cout << "possible" << endl;
  } else {
    cout << "not possible" << endl;
  }
  //  cout << "flow = " << flow << endl;
}

int main(void)
{
  int P;
  cin >> P;

  while (P-- > 0) {
    do_case();
  }
  return 0;
}
