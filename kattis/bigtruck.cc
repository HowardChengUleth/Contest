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
  int items;
  Edge(int t, int w, int i)
    : to(t), weight(w), items(i) { }
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
  void add_edge(int u, int v, int weight, int items)
  {
    nbr[u].push_back(Edge(v, weight, items));
  }
};

typedef pair<int,int> pii;
typedef pair<pii, int> Qelem;

int n;
int t[100];

/* assume that D and P have been allocated */
void dijkstra(const Graph &G, int src, vector<pii> &D, vector<int> &P)
{
  int n = G.num_nodes;
  vector<bool> used(n, false);
  priority_queue<Qelem, vector<Qelem>,  greater<Qelem> > fringe;

  D.resize(n);
  P.resize(n);
  fill(D.begin(), D.end(), pii(-1, 0));
  fill(P.begin(), P.end(), -1);

  D[src] = pii(0, -t[src]);
  fringe.push(make_pair(D[src], src));

  while (!fringe.empty()) {
    auto next = fringe.top();
    fringe.pop();
    int u = next.second;
    if (used[u]) continue;
    used[u] = true;

    for (EdgeIter it = G.nbr[u].begin(); it != G.nbr[u].end(); ++it) {
      int v = it->to;
      pii next_weight = next.first;
      pii nbr_weight(next_weight.first + it->weight,
		     next_weight.second - it->items);
      if (used[v]) continue;
      if (D[v].first == -1 || nbr_weight < D[v]) {
	D[v] = nbr_weight;
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
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> t[i];
  }

  int m;
  cin >> m;

  Graph G(n);
  for (int i = 0; i < m; i++) {
    int a, b, d;
    cin >> a >> b >> d;
    a--;
    b--;
    G.add_edge(a, b, d, t[b]);
    G.add_edge(b, a, d, t[a]);
  }

  vector<pii> D;
  vector<int> P;
  dijkstra(G, 0, D, P);
  if (D[n-1].first == -1) {
    cout << "impossible" << endl;
  } else {
    cout << D[n-1].first << ' ' << -D[n-1].second << endl;
  }
  
  
  return 0;
}
