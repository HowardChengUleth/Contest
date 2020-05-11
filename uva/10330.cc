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

const long long MAX_NODE = 202;

#define SOURCE 0
#define SINK 1
#define REG_IN(x) (2*((x)-1)+2)
#define REG_OUT(x) (2*((x)-1)+3)

void clear_graph(long long graph[MAX_NODE][MAX_NODE], long long n)
{
  for (long long i = 0; i < n; i++) {
    for (long long j = 0; j < n; j++) {
      graph[i][j] = 0;
    }
  }
}

void push(long long graph[MAX_NODE][MAX_NODE], long long flow[MAX_NODE][MAX_NODE],
	  long long e[], long long u, long long v)
{
  long long cf = graph[u][v] - flow[u][v];
  long long d = (e[u] < cf) ? e[u] : cf;
  flow[u][v] += d;
  flow[v][u] = -flow[u][v];
  e[u] -= d;
  e[v] += d;
}

void relabel(long long graph[MAX_NODE][MAX_NODE], long long flow[MAX_NODE][MAX_NODE],
	     long long n, long long h[], long long u)
{
  h[u] = -1;
  for (long long v = 0; v < n; v++) {
    if (graph[u][v] - flow[u][v] > 0 &&
	(h[u] == -1 || 1 + h[v] < h[u])) {
      h[u] = 1 + h[v];
    }
  }
  assert(h[u] >= 0);
}

void discharge(long long graph[MAX_NODE][MAX_NODE], long long flow[MAX_NODE][MAX_NODE],
	       long long n, long long e[], long long h[], list<long long>& NU, 
	       list<long long>::iterator &current, long long u)
{
  while (e[u] > 0) {
    if (current == NU.end()) {
      relabel(graph, flow, n, h, u);
      current = NU.begin();
    } else {
      long long v = *current;
      if (graph[u][v] - flow[u][v] > 0 && h[u] == h[v] + 1) {
	push(graph, flow, e, u, v);
      } else {
	++current;
      }
    }
  }
}

long long network_flow(long long graph[MAX_NODE][MAX_NODE], long long flow[MAX_NODE][MAX_NODE], 
		 long long n, long long s, long long t)
{
  long long e[MAX_NODE], h[MAX_NODE];
  long long u, v, oh;
  list<long long> N[MAX_NODE], L;
  list<long long>::iterator current[MAX_NODE], p;

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

void print_flow(long long flow[MAX_NODE][MAX_NODE], long long n)
{
  for (long long i = 0; i < n; i++) {
    for (long long j = 0; j < n; j++) {
      if (flow[i][j] > 0) {
	cout << i << " -> " << j << ": " << flow[i][j] << endl;
      }
    }
  }
}

bool read_case(long long graph[MAX_NODE][MAX_NODE], long long &N)
{
  long long orig_N;
  if (!(cin >> orig_N)) {
    return false;
  }

  N = 2*orig_N+2;
  clear_graph(graph, N);

  for (long long i = 1; i <= orig_N; i++) {
    cin >> graph[REG_IN(i)][REG_OUT(i)];
  }

  long long M;
  cin >> M;
  for (long long k = 0; k < M; k++) {
    long long i, j, C;
    cin >> i >> j >> C;
    graph[REG_OUT(i)][REG_IN(j)] = C;
  }

  long long B, D;
  cin >> B >> D;
  for (long long k = 0; k < B; k++) {
    long long i;
    cin >> i;
    graph[SOURCE][REG_IN(i)] = INT_MAX;
  }
  for (long long k = 0; k < D; k++) {
    long long i;
    cin >> i;
    graph[REG_OUT(i)][SINK] = INT_MAX;
  }

  return true;
}

int main(void)
{
  long long graph[MAX_NODE][MAX_NODE];
  long long N;
  
  while (read_case(graph, N)) {
    long long flow[MAX_NODE][MAX_NODE];
    cout << network_flow(graph, flow, N, SOURCE, SINK) << endl;
    /*
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
	cout << graph[i][j] << ' ';
      }
      cout << endl;
      }
    */
  }

  return 0;
}
