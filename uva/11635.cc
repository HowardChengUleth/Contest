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
void dijkstra(const Graph &G, int src, vector<int> &D)
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
    D[v] = it->weight;
    fringe.push(make_pair(D[v], v));
  }

  while (!fringe.empty()) {
    pii next = fringe.top();
    if (next.first > 600) return;  // cut off early
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
	fringe.push(make_pair(D[v], v));
      }
    }
  }
}

#include <climits>

const int MAX_HOTEL = 100;

bool solve()
{
  int n;
  cin >> n;
  if (!n) return false;

  int h;
  int hotel[MAX_HOTEL+2];
  cin >> h;
  for (int i = 1; i <= h; i++) {
    cin >> hotel[i];
    hotel[i]--;
  }
  hotel[0] = 0;
  hotel[h+1] = n-1;
  
  Graph G(n);
  int m;
  cin >> m;
  while (m--) {
    int a, b, t;
    cin >> a >> b >> t;
    a--; b--;
    G.add_edge(a, b, t);
    G.add_edge(b, a, t);
  }

  int G2[MAX_HOTEL+2][MAX_HOTEL+2];
  for (int i = 0; i <= h+1; i++) {
    fill(G2[i], G2[i]+h+2, INT_MAX);
    G2[i][i] = 0;
    vector<int> D;
    dijkstra(G, hotel[i], D);
    for (int j = 0; j <= h+1; j++) {
      if (i != j && 0 <= D[hotel[j]] && D[hotel[j]] <= 600) {
	G2[i][j] = 1;
      }
    }
  }

  for (int k = 0; k <= h+1; k++) {
    for (int i = 0; i <= h+1; i++) {
      if (G2[i][k] == INT_MAX) continue;
      for (int j = 0; j <= h+1; j++) {
	if (G2[k][j] == INT_MAX) continue;
	G2[i][j] = min(G2[i][j], G2[i][k] + G2[k][j]);
      }
    }
  }

  if (G2[0][h+1] == INT_MAX) {
    cout << -1 << endl;
  } else {
    cout << G2[0][h+1]-1 << endl;
  }
  
  return true;
}

int main()
{
  while (solve())
    ;
  return 0;
}
