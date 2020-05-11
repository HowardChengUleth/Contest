/*
 * Network Flow (Relabel-to-front)
 *
 * Author: Howard Cheng
 *
 * The routine network_flow() finds the maximum flow that can be
 * pushed from the source (s) to the sink (t) in a flow network
 * (i.e. directed graph with capacities on the edges).  The maximum
 * flow is returned.  The flow is given in the flow array (look for
 * positive flow).
 *
 * The complexity of this algorithm is O(n^3), which is good if the
 * graph is small but the maximum flow can be large.  Since the
 * algorithm is O(n^3) we are going to use the adjacency matrix
 * representation.
 *
 */

#include <iostream>
#include <list>
#include <cassert>

using namespace std;

const int MAX_NODE = 50;

void clear_graph(long long graph[MAX_NODE][MAX_NODE], int n)
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      graph[i][j] = 0;
    }
  }
}

void push(long long graph[MAX_NODE][MAX_NODE],
	  long long flow[MAX_NODE][MAX_NODE],
	  long long e[], int u, int v)
{
  long long cf = graph[u][v] - flow[u][v];
  long long d = (e[u] < cf) ? e[u] : cf;
  flow[u][v] += d;
  flow[v][u] = -flow[u][v];
  e[u] -= d;
  e[v] += d;
}

void relabel(long long graph[MAX_NODE][MAX_NODE],
	     long long flow[MAX_NODE][MAX_NODE],
	     int n, int h[], int u)
{
  h[u] = -1;
  for (int v = 0; v < n; v++) {
    if (graph[u][v] - flow[u][v] > 0 &&
	(h[u] == -1 || 1 + h[v] < h[u])) {
      h[u] = 1 + h[v];
    }
  }
  assert(h[u] >= 0);
}

void discharge(long long graph[MAX_NODE][MAX_NODE],
	       long long flow[MAX_NODE][MAX_NODE],
	       int n, long long e[], int h[], list<int>& NU, 
	       list<int>::iterator &current, int u)
{
  while (e[u] > 0) {
    if (current == NU.end()) {
      relabel(graph, flow, n, h, u);
      current = NU.begin();
    } else {
      int v = *current;
      if (graph[u][v] - flow[u][v] > 0 && h[u] == h[v] + 1) {
	push(graph, flow, e, u, v);
      } else {
	++current;
      }
    }
  }
}

long long network_flow(long long graph[MAX_NODE][MAX_NODE],
		       long long flow[MAX_NODE][MAX_NODE], 
		 int n, int s, int t)
{
  long long e[MAX_NODE];
  int h[MAX_NODE];
  int u, v, oh;
  list<int> N[MAX_NODE], L;
  list<int>::iterator current[MAX_NODE], p;

  for (u = 0; u < n; u++) {
    h[u] = e[u] = 0;
  }
  for (u = 0; u < n; u++) {
    for (v = 0; v < n; v++) {
      flow[u][v] = 0;
      if (graph[u][v] > 0 || graph[v][u] > 0) {
	N[u].push_front(v);
      }
    }
  }
  h[s] = n;
  for (u = 0; u < n; u++) {
    if (graph[s][u] > 0) {
      e[u] = flow[s][u] = graph[s][u];
      e[s] += flow[u][s] = -graph[s][u];
    }
    if (u != s && u != t) {
      L.push_front(u);
    }
    current[u] = N[u].begin();
  }

  p = L.begin();
  while (p != L.end()) {
    u = *p;
    oh = h[u];
    discharge(graph, flow, n, e, h, N[u], current[u], u);
    if (h[u] > oh) {
      L.erase(p);
      L.push_front(u);
      p = L.begin();
    }
    ++p;
  }
  
  long long maxflow = 0;
  for (u = 0; u < n; u++) {
    if (flow[s][u] > 0) {
      maxflow += flow[s][u];
    }
  }
  return maxflow;
}

void dfs(int n, int v, int mark[], long long graph[MAX_NODE][MAX_NODE],
	 long long flow[MAX_NODE][MAX_NODE])
{
  mark[v] = 1;
  for (int w = 0; w < n; w++) {
    if (mark[w] != 0) continue;
    if ((flow[v][w] > 0 && flow[v][w] < graph[v][w]) ||
        (flow[w][v] > 0)) {
      dfs(n, w, mark, graph, flow);
    }
  }
}

void dfs(int n, int v, int mark[], long long flow[MAX_NODE][MAX_NODE])
{
  mark[v] = 1;
  for (int w = 0; w < n; w++) {
    if (flow[v][w] > 0 && mark[w] == 0) {
      dfs(n, w, mark, flow);
    }
  }
}

bool solve()
{
  int n, m;
  cin >> n >> m;
  if (!n && !m) return false;
  
  long long graph[MAX_NODE][MAX_NODE];
  clear_graph(graph, n);

  while (m--) {
    int u, v;
    long long c;
    cin >> u >> v >> c;
    u--, v--;
    graph[u][v] = graph[v][u] = c;
  }

  long long flow[MAX_NODE][MAX_NODE];
  network_flow(graph, flow, n, 0, 1);

  // one part contains all the vertices reachable from the source through
  // in the residual network.  The other part are the rest.
  //
  // any vertices which are not reachable by any flow should be ignored
  int mark[MAX_NODE] = { 0 };
  int hasflow[MAX_NODE] = { 0 };
  dfs(n, 0, mark, graph, flow);
  dfs(n, 0, hasflow, flow);

  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      if (hasflow[i] && hasflow[j] && mark[i] != mark[j] && graph[i][j] > 0) {
	cout << i+1 << ' ' << j+1 << endl;
      }
    }
  }
  
  cout << endl;
  return true;
}


int main(void)
{
  while (solve())
    ;
  return 0;
}
