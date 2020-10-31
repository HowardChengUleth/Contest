#include <bits/stdc++.h>

using namespace std;

/*
 * Network Flow
 *
 * Author: Howard Cheng
 *
 * The routine network_flow() finds the maximum flow that can be
 * pushed from the source (s) to the sink (t) in a flow network
 * (i.e. directed graph with capacities on the edges).  The maximum
 * flow is returned.  Note that the graph is modified.  If you wish to
 * recover the flow on an edge, it is in the "flow" field, as long as
 * is_real is set to true.
 *
 * Note: if you have an undirected network. simply call add_edge twice
 * with an edge in both directions (same capacity).  Note that 4 edges
 * will be added (2 real edges and 2 residual edges).  To discover the
 * actual flow between two vertices u and v, add up the flow of all
 * real edges from u to v and subtract all the flow of real edges from
 * v to u.  (In fact, for a residual edge the flow is always 0 in this
 * implementation.)
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


struct Edge;
typedef list<Edge>::iterator EdgeIter;

struct Edge {
  int to;
  int cap;
  int flow;
  bool is_real;
  EdgeIter partner;
  
  Edge(int t, int c, bool real = true)
    : to(t), cap(c), flow(0), is_real(real)
  {};

  int residual() const
  {
    return cap - flow;
  }
};

struct Graph {
  list<Edge> *nbr;
  int num_nodes;
  Graph(int n)
    : num_nodes(n)
  {
    nbr = new list<Edge>[num_nodes];
  }

  ~Graph()
  {
    delete[] nbr;
  }

  // note: this routine adds an edge to the graph with the specified capacity,
  // as well as a residual edge.  There is no check on duplicate edge, so it
  // is possible to add multiple edges (and residual edges) between two
  // vertices
  void add_edge(int u, int v, int cap)
  {
    nbr[u].push_front(Edge(v, cap));
    nbr[v].push_front(Edge(u, 0, false));
    nbr[v].begin()->partner = nbr[u].begin();
    nbr[u].begin()->partner = nbr[v].begin();
  }
};

void push_path(Graph &G, int s, int t, const vector<EdgeIter> &path, int flow)
{
  for (int i = 0; s != t; i++) {
    if (path[i]->is_real) {
      path[i]->flow += flow;
      path[i]->partner->cap += flow;
    } else {
      path[i]->cap -= flow;
      path[i]->partner->flow -= flow;
    }
    s = path[i]->to;
  }
}

// the path is stored in a peculiar way for efficiency: path[i] is the
// i-th edge taken in the path.
int augmenting_path(const Graph &G, int s, int t, vector<EdgeIter> &path,
		    vector<bool> &visited, int step = 0)
{
  if (s == t) {
    return -1;
  }
  for (EdgeIter it = G.nbr[s].begin(); it != G.nbr[s].end(); ++it) {
    int v = it->to;
    if (it->residual() > 0 && !visited[v]) {
      path[step] = it;
      visited[v] = true;
      int flow = augmenting_path(G, v, t, path, visited, step+1);
      if (flow == -1) {
	return it->residual();
      } else if (flow > 0) {
	return min(flow, it->residual());
      }
    }
  }
  return 0;
}

// note that the graph is modified
int network_flow(Graph &G, int s, int t)
{
  vector<bool> visited(G.num_nodes);
  vector<EdgeIter> path(G.num_nodes);
  int flow = 0, f;

  do {
    fill(visited.begin(), visited.end(), false);
    if ((f = augmenting_path(G, s, t, path, visited)) > 0) {
      push_path(G, s, t, path, f);
      flow += f;
    }
  } while (f > 0);
  
  return flow;
}

int n;
string A[80];

bool possible(Graph &G, int cap)
{
  const int SRC = 2*n, SINK = 2*n+1;
  
  for (int i = 0; i < G.num_nodes; i++) {
    G.nbr[i].clear();
  }
  for (int i = 0; i < n; i++) {
    G.add_edge(SRC, i, cap);
    G.add_edge(i+n, SINK, cap);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (A[i][j] == 'Y') {
	G.add_edge(j, i+n, 1);
      }
    }
  }

  int f = network_flow(G, SRC, SINK);
  return f == n * cap;
}

bool solve()
{
  if (!(cin >> n) || n == 0)
    return false;
  
  for (int i = 0; i < n; i++) {
    cin >> A[i];
    assert(A[i].length() == n);
  }

  Graph G(2*n+2);
  int lo = 0, hi = 1;
  while (possible(G, hi)) {
    hi *= 2;
  }
  while (hi - lo > 1) {
    int mid = (lo + hi)/2;
    if (possible(G, mid)) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  int rounds = lo;
  cout << rounds << endl;

  // now remove all the unwanted edges
  possible(G, rounds);
  for (int i = 0; i < n; i++) {
    for (auto e : G.nbr[i]) {
      if (!e.is_real || e.flow > 0) continue;
      assert(0 <= e.to-n && e.to-n < n);
      assert(0 <= i && i < n);
      A[e.to - n][i] = 'N';
    }
  }
  for (int i = 0; i < rounds; i++) {
    bool t = possible(G, 1);
    assert(t);
    for (int i = 0; i < n; i++) {
      for (auto e : G.nbr[i]) {
	if (!(e.flow > 0 && e.is_real)) continue;
	cout << e.to-n+1 << ' ';
	A[e.to - n][i] = 'N';
      }
    }
    cout << endl;
  }
  
  return true;
}

int main()
{
  while (solve())
    ;

  solve();
  return 0;
}
