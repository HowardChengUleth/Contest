#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

// Graph layout
//  -- Each problem has its own Edge structure.
// If you see "typedef int Edge;" at the top of an algorithm, change
//    vector<vector<Edge> > nbr; --->  vector<vector<int> > nbr;

struct Edge{ int to,weight; }; // weight can be double or other numeric type
typedef vector<Edge>::const_iterator EdgeIter;

struct Graph {
  vector<vector<Edge> > nbr;
  int num_nodes;
  Graph(int n) : nbr(n), num_nodes(n) { }
  
  void add_edge(int u, int v, int weight) {
    Edge e1 = {v,weight};   nbr[u].push_back(e1);
    Edge e2 = {u,weight};   nbr[v].push_back(e2);
  }
};

// Dijkstra's Algorithm [Sparse Graphs] (Directed and Undirected) -- O((n+m)*log(n+m))
//  -- Edge weight >= 0.  May use get_path to obtain the path.


void dijkstra(const Graph &G, int src, vector<int> &D, vector<int> &P) {
  typedef pair<int,int> pii;
  int n = G.num_nodes;
  vector<bool> used(n, false);
  priority_queue<pii, vector<pii>,  greater<pii> > fringe;

  D.resize(n);  fill(D.begin(), D.end(), -1);  
  P.resize(n);  fill(P.begin(), P.end(), -1);

  D[src] = 0;
  fringe.push(make_pair(0, src));

  while (!fringe.empty()) {
    pii next = fringe.top();    fringe.pop();
    int u = next.second;
    if (used[u]) continue;
    used[u] = true;

    for (EdgeIter it = G.nbr[u].begin(); it != G.nbr[u].end(); ++it) {
      int v = it->to, weight = it->weight + next.first;
      if (used[v]) continue;
      if (D[v] == -1 || weight < D[v]) {
	D[v] = weight;    P[v] = u;    fringe.push(make_pair(D[v], v));
      }
    }
  }
}

int main()
{
  int P, T;
  cin >> P >> T;
  
  Graph G(P);
  for (int i = 0; i < T; i++) {
    int p1, p2, l;
    cin >> p1 >> p2 >> l;
    G.add_edge(p1, p2, l);
  }

  vector<int> D1, P1, D2, P2;
  dijkstra(G, 0, D1, P1);
  dijkstra(G, P-1, D2, P2);

  int best = D1[P-1];
  int sum = 0;

  for (int i = 0; i < P; i++) {
    for (const auto &e : G.nbr[i]) {
      if (D1[i] < 0 || D2[e.to] < 0) continue;
      if (D1[i] + D2[e.to] + e.weight == best) {
	sum += 2*e.weight;
      }
    }
  }

  cout << sum << endl;
  return 0;
}
