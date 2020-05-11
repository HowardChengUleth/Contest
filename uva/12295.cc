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

const int mod = 1000000009;

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
void dijkstra(const Graph &G, int src, vector<int> &D)
{
  typedef pair<int,int> pii;

  int n = G.num_nodes;
  vector<bool> used(n, false);
  priority_queue<pii, vector<pii>,  greater<pii> > fringe;
  vector<int> paths(n, 0);

  D.resize(n);
  fill(D.begin(), D.end(), -1);

  D[src] = 0;
  used[src] = true;
  paths[src] = 1;
  for (EdgeIter it = G.nbr[src].begin(); it != G.nbr[src].end(); ++it) {
    int v = it->to;
    D[v] = it->weight;
    paths[v] = paths[src];
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

      // note: we have to continue here even if used[v] is true.
      if (D[v] == -1 || weight < D[v]) {
	// never seen this distance before, just copy the paths from
	// parent
	D[v] = weight;
	paths[v] = paths[u];
	fringe.push(make_pair(D[v], v));
      } else if (weight == D[v]) {
	// we have seen this distance before, so add the paths
	paths[v] += paths[u];
	paths[v] %= mod;
      }
    }
  }
  cout << paths[1] << endl;
}

int ind(int i, int j, int n)
{
  return i*n+j+2;
}

bool solve()
{
  int n;
  cin >> n;
  if (!n) return false;

  int A[100][100];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> A[i][j];
    }
  }

  // fold the matrix along the antidiagonal
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i+j <= n-1) continue;
      A[n-1-j][n-1-i] += A[i][j];
    }
  }

  const int dr[4] = { -1, 1, 0, 0 };
  const int dc[4] = {  0, 0, 1, -1};
  Graph G(n*n+2);   // 0 = src, 1 = dest, 2 - n*n+1 = array elements
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i+j > n-1) continue;
      for (int d = 0; d < 4; d++) {
	int ni = i + dr[d], nj = j + dc[d];
	if (!(0 <= ni && ni < n && 0 <= nj && nj < n && ni+nj <= n-1)) continue;
	G.add_edge(ind(i, j, n), ind(ni, nj, n), A[ni][nj]);
      }

      // antidiagonal to dummy dest
      if (i+j == n-1) {
	G.add_edge(ind(i, j, n), 1, 0);
      }
    }
  }

  // dummy src to A[0][0]
  G.add_edge(0, ind(0, 0, n), A[0][0]);
  vector<int> D;
  dijkstra(G, 0, D);

  return true;
}

int main(void)
{
  while (solve())
    ;
  return 0;
}
  
