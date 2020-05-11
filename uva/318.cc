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
#include <iomanip>

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

int main(void)
{
  int n, m;
  int case_num = 1;
  while (cin >> n >> m && (n || m)) {
    Graph G(n+1);

    for (int i = 0; i < m; i++) {
      int u, v, w;
      cin >> u >> v >> w;
      G.add_edge(u, v, w);
      G.add_edge(v, u, w);
    }

    vector<int> D, P;
    dijkstra(G, 1, D, P);

    double t = 0.0;
    int v1 = 1, v2 = -1;
    for (int i = 1; i <= n; i++) {
      if (t < D[i]) {
	t = D[i];
	v1 = i;
      }
    }
    
    for (int i = 1; i <= n; i++) {
      for (EdgeIter it = G.nbr[i].begin(); it != G.nbr[i].end(); ++it) {
	int t1 = D[i];
	int t2 = D[it->to];
	int len = it->weight;

	if (t1 + len == t2 || t2 + len == t1) continue;
	double temp = (len - abs(t2-t1))/ 2.0 + max(t1, t2);
	if (temp > t) {
	  t = temp;
	  v1 = i;
	  v2 = it->to;
	}
      }
    }

    cout << "System #" << case_num++ << endl;
    cout << "The last domino falls after "
	 << fixed << setprecision(1) << t << " seconds, ";
    if (v2 == -1) {
      cout << "at key domino " << v1 << "." << endl;
    } else {
      cout << "between key dominoes " << v1 << " and " << v2 << "." << endl;
    }
    cout << endl;
  }
  return 0;
}
