#include <bits/stdc++.h>

using namespace std;

int M, N;
vector<string> gridstr;
vector<vector<int>> grid;

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

// N = 0, E = 1, S = 2, W = 3;
const int dr[] = { -1, 0, 1, 0 };
const int dc[] = { 0, 1, 0, -1 };

int index(int r, int c, int steps, int dir)
{
  int ans = ((r * N + c) * 4 + steps) * 4 + dir;
  assert(0 <= ans && ans < M*N*16+2);
  return ans;
}

bool inside(int r, int c)
{
  return 0 <= r && r < M && 0 <= c && c < N;
}

void build_graph(Graph &G, int src, int dest)
{
  // src
  G.add_edge(src, index(0, 0, 0, 1), 0);
  G.add_edge(src, index(0, 0, 0, 2), 0);

  // dest
  for (int steps = 0; steps < 4; steps++) {
    for (int dir = 0; dir < 4; dir++) {
      G.add_edge(index(M-1, N-1, steps, dir), dest, 0);
    }
  }

  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      for (int steps = 0; steps < 4; steps++) {
	for (int dir = 0; dir < 4; dir++) {
	  for (int new_dir = 0; new_dir < 4; new_dir++) {
	    int r2 = r + dr[new_dir];
	    int c2 = c + dc[new_dir];
	    if (!inside(r2, c2)) continue;

	    // must turn
	    if (steps == 3 && new_dir == dir) continue;

	    // go backwards
	    if (new_dir != dir && new_dir % 2 == dir % 2) continue; 

	    int new_steps = (dir == new_dir) ? steps+1 : 1;
	    G.add_edge(index(r, c, steps, dir),
		       index(r2, c2, new_steps, new_dir),
		       grid[r2][c2]);
	  }
	}
      }
    }
  }
}

int main()
{
  string line;
  while (getline(cin, line)) {
    gridstr.push_back(line);
  }
  M = gridstr.size();
  N = gridstr[0].size();

  grid.resize(M, vector<int>(N, 0));
  
  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      grid[r][c] = gridstr[r][c] - '0';
    }
  }

  Graph G(M*N*4*4 + 2);
  int src = M*N*4*4;
  int dest = M*N*4*4+1;

  build_graph(G, src, dest);

  vector<int> D, P;
  dijkstra(G, src, D, P);
  cout << D[dest] << endl;

  return 0;
}
