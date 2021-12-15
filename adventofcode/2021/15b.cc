#include <bits/stdc++.h>

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

using namespace std;

int n;

int node(int r, int c)
{
  return r*n + c;
}

int main()
{
  vector<string> B;

  string s;
  while (cin >> s) {
    B.push_back(s);
  }
  n = B.size();

  vector<string> A(5*n);
  for (int r = 0; r < 5*n; r++) {
    A[r] = string(5*n, ' ');
    for (int c = 0; c < 5*n; c++) {
      int rB = r % n, cB = c % n;
      int step = r / n + c / n;
      int val = B[rB][cB] - '0' + step;
      while (val > 9)
	val -= 9;
      A[r][c] = val + '0';
    }
  }

  n = 5*n;
  
  const int dr[] = {-1, 1, 0, 0};
  const int dc[] = {0, 0, -1, 1};
  
  Graph G(n*n);
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < n; c++) {
      int from = node(r, c);
      for (int d = 0; d < 4; d++) {
	int r2 = r + dr[d], c2 = c + dc[d];
	if (0 <= r2 && r2 < n && 0 <= c2 && c2 < n) {
	  int to = node(r2, c2);
	  G.add_edge(from, to, A[r2][c2] - '0');
	}
      }
    }
  }

  vector<int> D, P;
  dijkstra(G, node(0, 0), D, P);
  cout << D[node(n-1, n-1)] << endl;

  return 0;
}
