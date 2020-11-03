#include <bits/stdc++.h>

using namespace std;

typedef int Edge;

struct Graph {
  vector<vector<Edge> > nbr;
  vector<unordered_set<int>> dist;
  vector<bool> visited;
  int num_nodes;
  Graph(int n) : nbr(n), dist(n), visited(n, false), num_nodes(n) { }
  
  // No check for duplicate edges!
  // Add (or remove) any parameters that matter for your problem
  void add_edge(int u, int v) {
    Edge e = v;    nbr[u].push_back(e);
  }

  void comp_dist(int root = 0)
  {
    if (visited[root]) return;
    if (root == num_nodes-1) {
      dist[root].insert(0);
    } else {
      for (auto child : nbr[root]) {
	comp_dist(child);
	for (auto d : dist[child]) {
	  dist[root].insert(d+1);
	}
      }
    }

    visited[root] = 1;
  }
  
};

int main()
{
  int N1, N2, M1, M2;
  cin >> N1 >> N2 >> M1 >> M2;
 
  Graph G1(N1), G2(N2);

  for (int i = 0; i < M1; i++) {
    int u, v;
    cin >> u >> v;
    G1.add_edge(u-1, v-1);
  }
  for (int i = 0; i < M2; i++) {
    int u, v;
    cin >> u >> v;
    G2.add_edge(u-1, v-1);
  }

  G1.comp_dist();
  G2.comp_dist();
  unordered_set<int> dist;
  for (auto x : G1.dist[0]) {
    for (auto y : G2.dist[0]) {
      dist.insert(x+y);
    }
  }
  
  int Q;
  cin >> Q;
  while (Q--) {
    int q;
    cin >> q;
    cout << (dist.count(q) > 0 ? "Yes" : "No") << endl;
  }

  return 0;
}
