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
  
typedef list<Edge>::iterator EdgeIter;

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

  // note: There is no check on duplicate edge, so it is possible to
  // add multiple edges between two vertices
  //
  // If this is an undirected graph, be sure to add an edge both
  // ways
  void add_edge(int u, int v, int weight)
  {
    nbr[u].push_front(Edge(v, weight));
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
  used[src] = true;
  for (EdgeIter it = G.nbr[src].begin(); it != G.nbr[src].end(); ++it) {
    int v = it->to;
    D[v] = it->weight;
    P[v] = src;
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

#include <sstream>

int node(int elevator, int floor)
{
  return elevator*100+floor+1;
}

bool solve()
{
  int n, k;
  if (!(cin >> n >> k)) {
    return false;
  }

  Graph G(5*100+1);

  int T[5];
  for (int i = 0; i < n; i++) {
    cin >> T[i];
    G.add_edge(0, node(i, 0), 0);
  }
  cin.ignore(1);

  bool floors[5][100];
  for (int i = 0; i < n; i++) {
    fill(floors[i], floors[i]+100, false);
    string line;
    getline(cin, line);
    istringstream iss(line);
    int prev = -1;
    int x;
    while (iss >> x) {
      if (prev != -1) {
	G.add_edge(node(i, prev), node(i, x), T[i]*(x-prev));
	G.add_edge(node(i, x), node(i, prev), T[i]*(x-prev));
      }
      floors[i][x] = true;
      prev = x;
    }
  }

  for (int f = 0; f < 100; f++) {
    for (int i = 0; i < n; i++) {
      for (int j = i+1; j < n; j++) {
	if (floors[i][f] && floors[j][f]) {
	  int u = node(i, f), v = node(j, f);
	  G.add_edge(u, v, 60);
	  G.add_edge(v, u, 60);
	}
      }
    }
  }

  vector<int> D, P;
  dijkstra(G, 0, D, P);

  int best = -1;
  for (int i = 0; i < n; i++) {
    int u = node(i, k);
    if (D[u] < 0) continue;
    if (best == -1 || D[u] < best) {
      best = D[u];
    }
  }

  if (best >= 0) {
    cout << best << endl;
  } else {
    cout << "IMPOSSIBLE" << endl;
  }
  return true;
}

int main(void)
{
  while (solve())
    ;
  return 0;
}
  


