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
#include <list>
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
void dijkstra(const Graph &G, int src, vector<int> &D, int c)
{
  typedef pair<int,int> pii;

  int n = G.num_nodes;
  vector<bool> used(n, false);
  priority_queue<pii, vector<pii>,  greater<pii> > fringe;

  D.resize(n);
  fill(D.begin(), D.end(), -1);

  D[src] = 0;
  used[src] = true;
  for (EdgeIter it = G.nbr[src].begin(); it != G.nbr[src].end(); ++it) {
    int v = it->to;
    if (v % 101 > c) continue;
    D[v] = it->weight;
    fringe.push(make_pair(D[v], v));
  }

  while (!fringe.empty()) {
    pii next = fringe.top();
    fringe.pop();
    int u = next.second;
    if (used[u]) continue;
    used[u] = true;

    for (EdgeIter it = G.nbr[u].begin(); it != G.nbr[u].end(); ++it) {
      int v = it->to;
      int weight = it->weight + next.first;
      if (used[v] || v % 101 > c) continue;
      if (D[v] == -1 || weight < D[v]) {
	D[v] = weight;
	fringe.push(make_pair(D[v], v));
      }
    }
  }
}

int node(int n, int cap)
{
  return n*101 + cap;
}

int main(void)
{
  int n, m;
  cin >> n >> m;

  int p[1000];
  for (int i = 0; i < n; i++) {
    cin >> p[i];
  }

  pair< pair<int,int>, int> edge[10000];
  for (int i = 0; i < m; i++) {
    cin >> edge[i].first.first >> edge[i].first.second >> edge[i].second;
  }

  int c = 100;
  Graph G(n*101 + 100 + 1);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < c; j++) {
      G.add_edge(node(i, j), node(i, j+1), p[i]);
    }
  }
  for (int i = 0; i < m; i++) {
    int u = edge[i].first.first, v = edge[i].first.second, d = edge[i].second;
    
    for (int j = d; j <= c; j++) {
      G.add_edge(node(u, j), node(v, j-d), 0);
      G.add_edge(node(v, j), node(u, j-d), 0);
    }
  }

  
  int q;
  cin >> q;
  while (q--) {
    int s, e, c;
    cin >> c >> s >> e;

    vector<int> D;
    dijkstra(G, node(s, 0), D, c);
    int best = -1;
    for (int i = 0; i <= c; i++) {
      if (D[node(e,i)] < 0) continue;
      if (best == -1 || D[node(e,i)] < best) {
	best = D[node(e,i)];
      }
    }
    if (best < 0) {
      cout << "impossible" << endl;
    } else {
      cout << best << endl;
    }

  }

  return 0;
}
