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
#include <algorithm>

using namespace std;

const int MAX_NODE = 30*11+1;

void clear_graph(int graph[MAX_NODE][MAX_NODE], int n)
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      graph[i][j] = 0;
    }
  }
}

void push(int graph[MAX_NODE][MAX_NODE], int flow[MAX_NODE][MAX_NODE],
	  int e[], int u, int v)
{
  int cf = graph[u][v] - flow[u][v];
  int d = (e[u] < cf) ? e[u] : cf;
  flow[u][v] += d;
  flow[v][u] = -flow[u][v];
  e[u] -= d;
  e[v] += d;
}

void relabel(int graph[MAX_NODE][MAX_NODE], int flow[MAX_NODE][MAX_NODE],
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

void discharge(int graph[MAX_NODE][MAX_NODE], int flow[MAX_NODE][MAX_NODE],
	       int n, int e[], int h[], list<int>& NU, 
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

int network_flow(int graph[MAX_NODE][MAX_NODE], int flow[MAX_NODE][MAX_NODE], 
		 int n, int s, int t)
{
  int e[MAX_NODE], h[MAX_NODE];
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
  
  int maxflow = 0;
  for (u = 0; u < n; u++) {
    if (flow[s][u] > 0) {
      maxflow += flow[s][u];
    }
  }
  return maxflow;
}

#define SRC 0
#define NODE(c, d) ((d)*30+(c))

int n, d, m;
struct Flight
{
  int u, v, c, p, e;
};
Flight flight[1000];
int z[30];
int total;
int cost[1000];

bool possible(int cost)
{
  int graph[MAX_NODE][MAX_NODE];

  for (int i = 0; i < MAX_NODE; i++) {
    fill(graph[i], graph[i]+MAX_NODE, 0);
  }

  // how many people there are at each city initially
  for (int c = 1; c <= n; c++) {
    graph[SRC][NODE(c, 0)] = z[c-1];
  }

  // each day people can just stay put
  for (int i = 0; i < d; i++) {
    for (int c = 1; c <= n; c++) {
      graph[NODE(c, i)][NODE(c, i+1)] = 3000;
    }
  }

  // now add the possible flights
  for (int i = 0; i < m; i++) {
    if (flight[i].p > cost) continue;
    graph[NODE(flight[i].u, flight[i].e)][NODE(flight[i].v, flight[i].e+1)] =
      flight[i].c;
  }

  int flow[MAX_NODE][MAX_NODE];
  int maxflow = network_flow(graph, flow, MAX_NODE, SRC, NODE(n, d));
  return maxflow == total;
}

void solve()
{
  cin >> n >> d >> m;
  for (int i = 0; i < m; i++) {
    cin >> flight[i].u >> flight[i].v >> flight[i].c >> flight[i].p
	>> flight[i].e;
    cost[i] = flight[i].p;
  }

  sort(cost, cost+m);
  
  total = 0;
  for (int i = 0; i < n; i++) {
    cin >> z[i];
    total += z[i];
  }

  int lo = 0, hi = m-1;
  if (!possible(cost[hi])) {
    cout << "Impossible" << endl;
    return;
  } else if (possible(cost[lo])) {
    cout << 0 << endl;
    return;
  }

  while (lo+1 < hi) {
    int mid = (lo+hi)/2;
    if (possible(cost[mid])) {
      hi = mid;
    } else {
      lo = mid;
    }
  }
  
  cout << cost[hi] << endl;
}

int main(void)
{
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
  return 0;
}


