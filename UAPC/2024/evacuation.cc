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

typedef pair<int,int> pii;
map<pii, int> edges;
set<pii> tornado_edges;
map<int, int> tornado_time;



struct Edge {
  int to;
  int weight;       // can be double or other numeric type
  int last_time;
  bool backward;
  Edge(int t, int w, int last, bool back)
    : to(t), weight(w), last_time(last), backward(back) { }
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
  void add_edge(int u, int v, int weight, int last = INT_MAX)
  {
    nbr[u].push_back(Edge(v, weight, last));
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
      if (next.first > it->last_time) continue;
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

int N, M, K;
int H, E;

int main()
{
  cin >> N >> M >> K;
  cin >> H >> E;
  H--;
  E--;
  
  Graph G(N);
  for (int i = 0; i < M; i++) {
    int u, v, t;
    cin >> u >> v >> t;
    u--;
    v--;
    edges[pii(u,v)] = t;
    edges[pii(v,u)] = t;
  }

  int tornado;
  cin >> tornado;
  tornado--;
  int time = 0;
  tornado_time[tornado] = time;
  for (int i = 1; i < K; i++) {
    int next;
    cin >> next;
    next--;
    tornado_edges.emplace(tornado, next);
    time += edges[pii(tornado, next)];
    tornado = next;
    tornado_time[tornado] = time;
  }

  for (auto [e, t] : edges) {
    auto [u, v] = e;
    if (tornado_edges.count(pii(u, v)) > 0) {
      G.add_edge(u, v, t, tornado_time[u] - t);
    } else if (tornado_edges.count(pii(v, u)) > 0) {
      G.add_edge(u, v, t, tornado_time[v] - t);
    } else {
      G.add_edge(u, v, t);
    }
  }

  vector<int> D, P;
  dijkstra(G, H, D, P);

  cout << D[E] << endl;
  return 0;

}
