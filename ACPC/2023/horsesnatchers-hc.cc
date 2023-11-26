#include <bits/stdc++.h>

using namespace std;

/*
 * Dijkstra's Algorithm for sparse graphs
 *
 * Author: Howard Cheng
 *
 * Given a weight matrix representing a graph and a source vertex, this
 * algorithm computes the shortest distance, as well as path, to each
 * of the other vertices.  The paths are represented by an inverted list,
 * such that if v preceeds immediately before w in a path from the
 * source to vertex w, then the path P[w] is v.  The distances from
 * the source to v is given in D[v] (-1 if not connected).
 *
 * Call get_path to recover the path.
 *
 * Note: Dijkstra's algorithm only works if all weight edges are
 *       non-negative.
 *
 * This version works well if the graph is not dense.  The complexity
 * is O((n + m) log (n + m)) where n is the number of vertices and
 * m is the number of edges.
 *
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <queue>

using namespace std;


struct Edge {
  int to;
  int weight;       // can be double or other numeric type
  Edge(int t, int w)
    : to(t), weight(w) { }
};
  
typedef vector<Edge>::iterator EdgeIter;

struct Graph {
  vector<Edge> *nbr;
  int num_nodes;
  Graph(int n)
    : num_nodes(n)
  {
    nbr = new vector<Edge>[num_nodes];
  }

  ~Graph()
  {
    delete[] nbr;
  }

  // note: There is no check on duplicate edge, so it is possible to
  // add multiple edges between two vertices
  //
  // If this is an undirected graph, be sure to add an edge both
  // ways
  void add_edge(int u, int v, int weight)
  {
    nbr[u].push_back(Edge(v, weight));
  }
};

/* assume that D and P have been allocated */
void dijkstra(const Graph &G, int src, vector<int> &D, vector<int> &P)
{
  typedef pair<int,int> pii;

  int n = G.num_nodes;
  vector<bool> used(n, false);
  priority_queue<pii, vector<pii>,  greater<pii> > fringe;

  D.resize(n);
  P.resize(n);
  fill(D.begin(), D.end(), -1);
  fill(P.begin(), P.end(), -1);

  D[src] = 0;
  fringe.push(make_pair(D[src], src));

  while (!fringe.empty()) {
    pii next = fringe.top();
    fringe.pop();
    int u = next.second;
    if (used[u]) continue;
    used[u] = true;

    for (EdgeIter it = G.nbr[u].begin(); it != G.nbr[u].end(); ++it) {
      int v = it->to;
      int weight = it->weight + next.first;
      if (used[v]) continue;
      if (D[v] == -1 || weight < D[v]) {
	D[v] = weight;
	P[v] = u;
	fringe.push(make_pair(D[v], v));
      }
    }
  }
}

int get_path(int v, const vector<int> &P, vector<int> &path)
{
  path.clear();
  path.push_back(v);
  while (P[v] != -1) {
    v = P[v];
    path.push_back(v);
  }
  reverse(path.begin(), path.end());
  return path.size();
}

int main(void)
{
  int n, k, m;
  cin >> n >> k >> m;

  Graph Ghorse(n);
  Graph Gwalk(n);
  
  int T, w;
  cin >> T >> w;

  bool snatch[1000] = { false };
  for (int i = 0; i < k; i++) {
    int s;
    cin >> s;
    snatch[s-1] = true;
  }

  for (int i = 0; i < m; i++) {
    int a, b, d;
    cin >> a >> b >> d;
    a--; b--;
    if (!snatch[a]) 
      Ghorse.add_edge(a, b, d);
    if (!snatch[b])
      Ghorse.add_edge(b, a, d);
    Gwalk.add_edge(a, b, d);
    Gwalk.add_edge(b, a, d);
  }

  vector<int> Dhorse, Phorse, Dwalk, Pwalk;
  dijkstra(Ghorse, 0, Dhorse, Phorse);
  dijkstra(Gwalk, n-1, Dwalk, Pwalk);

  if (Dwalk[0] <= T * w) {
    cout << "No horse needed!" << endl;
    return 0;
  }

  double best_speed = DBL_MAX;
  for (int i = 0; i < n; i++) {
    if (Dhorse[i] != -1 && Dwalk[i] != -1) {
      double time_left = T - Dwalk[i] / (double)w;
      if (time_left > 0) {
	double speed = Dhorse[i] / time_left;
	best_speed = min(best_speed, speed);
      }
    }
  }

  if (best_speed == DBL_MAX) {
    cout << "Impossible" << endl;
  } else {
    cout << fixed << setprecision(10) << best_speed << endl;
  }
  
  return 0;
}
