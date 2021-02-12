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

int node(int r, int c, int si)
{
  return (r * 100 + c) * 51 + si;
}

int main()
{
  int C, R;
  cin >> C >> R;
  cin.ignore();
  
  string key;
  getline(cin, key);

  int A[100][100];
  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      char ch;
      cin >> ch;
      A[r][c] = ch - '0';
    }
  }

  Graph G(100*100*51);
  int dr[] = {-1, 0};
  int dc[] = {0, 1};
  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      for (int si = 0; si <= key.length(); si++) {
	for (int d = 0; d < 2; d++) {
	  int r2 = r + dr[d], c2 = c + dc[d];
	  if (0 <= r2 && r2 < R && 0 <= c2 && c2 < C) {
	    G.add_edge(node(r, c, si), node(r2, c2, si), A[r][c]);
	  }

	  if (si == key.length()) continue;
	  r2 += (key[si]-'0')*dr[d];
	  c2 += (key[si]-'0')*dc[d];
	  if (0 <= r2 && r2 < R && 0 <= c2 && c2 < C) {
	    G.add_edge(node(r, c, si), node(r2, c2, si+1), A[r][c]);
	  }
	}
      }
    }
  }

  vector<int> D, P;
  dijkstra(G, node(R-1, 0, 0), D, P);
  int ans = INT_MAX;
  for (int si = 0; si <= key.length(); si++) {
    if (D[node(0, C-1, si)] >= 0) {
      ans = min(ans, D[node(0, C-1, si)]);
    }
  }

  cout << ans + A[0][C-1] << endl;

  return 0;
}
