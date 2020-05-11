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

bool topological_sort(const Graph &G, vector<int> &order)
{
  vector<int> indeg(G.num_nodes);
  fill(indeg.begin(), indeg.end(), 0);
  for (int i = 0; i < G.num_nodes; i++) {
    for (int j = 0; j < G.nbr[i].size(); j++) {
      indeg[G.nbr[i][j].to]++;
    }
  }

  // use a priority queue if you want to get a topological sort order
  // with ties broken by lexicographical ordering
  queue<int> q;
  for (int i = 0; i < G.num_nodes; i++) {      
    if (indeg[i] == 0) {
      q.push(i);
    }
  }

  order.clear();
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    order.push_back(v);
    for (int i = 0; i < G.nbr[v].size(); i++) {
      if (--indeg[G.nbr[v][i].to] == 0) {
        q.push(G.nbr[v][i].to);
      }
    }
  }
   
  return order.size() == G.num_nodes;
}

bool solve()
{
  int N, M;
  cin >> N >> M;
  if (!N) return false;

  Graph G(N+1);
  for (int i = 0; i < M; i++) {
    int a, b, d;
    cin >> a >> b >> d;
    G.add_edge(a, b, d);
    G.add_edge(b, a, d);
  }

  // find distance to the destination
  vector<int> D, P;
  dijkstra(G, 2, D, P);

  // the edge a->b can be taken iff D[a] > D[b].  The resulting graph is
  // guaranteed to be acyclic.
  Graph DAG(N+1);

  for (int u = 1; u <= N; u++) {
    for (EdgeIter it = G.nbr[u].begin(); it != G.nbr[u].end(); ++it) {
      int v = it->to;
      if (D[u] > D[v]) {
	DAG.add_edge(u, v, 1);
      }
    }
  }

  vector<int> order;
  topological_sort(DAG, order);

  int paths[1001] = {0, 1, 0};
  for (int i = 0; i < N+1; i++) {
    if (order[i] < 1) continue;
    int u = order[i];
    for (EdgeIter it = DAG.nbr[u].begin(); it != DAG.nbr[u].end(); ++it) {
      int v = it->to;
      paths[v] += paths[u];
    }
  }
  
  cout << paths[2] << endl;
  
  return true;
}

int main()
{
  while (solve())
    ;
  return 0;
}

