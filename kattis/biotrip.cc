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

typedef pair<int,int> pii;
int n, d, alpha1, alpha2;

struct Vertex
{
  int m;
  int d[5], t[5], a[5];

  vector<pii> inangle;
  
  void read() {
    cin >> m;
    for (int i = 0; i < m; i++) {
      cin >> d[i] >> t[i] >> a[i];
      d[i]--;
    }
    for (int i = 0; i < m; i++) {
      int angle = (a[i] + 180) % 360;
      if (find(angle) == -1) {
	inangle.emplace_back(angle, 0);
      }
    }
  }

  int find(int angle) const
  {
    for (auto [ang, node] : inangle) {
      if (ang == angle) {
	return node;
      }
    }
    return -1;
  }

  int find_match(int from) const
  {
    int angle = -1;
    for (int i = 0; i < m; i++) {
      if (d[i] == from) {
	angle = (a[i] + 180) % 360;
      }
    }
    assert(angle >= 0);
    return find(angle);
  }
};

bool can_use_edge(int src, int curr_angle, int next_angle)
{
  // can do anything at station 1
  if (src == 0) return true;

  int ccw = next_angle - curr_angle;
  if (ccw < 0) ccw += 360;
  if (ccw <= alpha1) return true;

  int cw = curr_angle - next_angle;
  if (cw < 0) cw += 360;
  if (cw <= alpha2) return true;

  return false;
}

Vertex v[1000];

int process_inangle()
{
  int index = 0;
  for (int i = 0; i < n; i++) {
    for (auto &[a, node] : v[i].inangle) {
      node = index++;
    }
  }
  return index;
}

void build_graph(Graph &G)
{
  for (int i = 0; i < n; i++) {
    for (auto [ang, src] : v[i].inangle) {
      for (int k = 0; k < v[i].m; k++) {
	if (!can_use_edge(i, ang, v[i].a[k])) continue;
	int dest_v = v[i].d[k];
	int dest = v[dest_v].find_match(i);
	G.add_edge(src, dest, v[i].t[k]);
      }
    }
  }
}

int main()
{
  cin >> n >> d >> alpha1 >> alpha2;
  d--;
  for (int i = 0; i < n; i++) {
    v[i].read();
  }

  int num_nodes = process_inangle();

  for (int i = 0; i < n; i++) {
    //    v[i].debug(i);
  }

  Graph G(num_nodes);
  build_graph(G);

  int ans = INT_MAX;
  for (auto [angle, dest] : v[d].inangle) {
    vector<int> D1, P1, D2, P2;
    dijkstra(G, v[0].inangle[0].second, D1, P1);
    if (D1[dest] == -1) continue;
    dijkstra(G, dest, D2, P2);
    for (auto [angle_src, dest_src] : v[0].inangle) {
      if (D2[dest_src] == -1) continue;
      ans = min(ans, D1[dest] + D2[dest_src]);
    }
  }

  if (ans < INT_MAX) {
    cout << ans << endl;
  } else {
    cout << "impossible" << endl;
  }
  

  return 0;
}
