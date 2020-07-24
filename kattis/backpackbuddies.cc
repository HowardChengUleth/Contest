#include <bits/stdc++.h>

using namespace std;

// This is a variation of the shortest path problem.
//
// For Knight, just use the standard Dijkstra's algorithm.  Once you figure
// out the distance, just divide the distance into chunks of 12 and adjust
// for sleeping (12 hours for each chunk except the last chunk).
//
// For Day, it is a bit more complicated.  We use Dijkstra again, but when
// calculating the distance for following an edge, we have to see if the
// current time has enough hours remaining in the day to take the edge.
// If not, we can still take the edge but have to add the extra cost of
// sleeping until the next day.
//
// Then just compare the answers returned by the two Dijkstra calls.


// Graph layout
//  -- Each problem has its own Edge structure.
// If you see "typedef int Edge;" at the top of an algorithm, change
//    vector<vector<Edge> > nbr; --->  vector<vector<int> > nbr;

struct Edge{ int to,weight; }; // weight can be double or other numeric type

struct Graph {
  vector<vector<Edge> > nbr;
  int num_nodes;
  Graph(int n) : nbr(n), num_nodes(n) { }
  
  // No check for duplicate edges!
  // Add (or remove) any parameters that matter for your problem
  void add_edge(int u, int v, int weight) {
    Edge e1 = {v,weight};   nbr[u].push_back(e1);
    Edge e2 = {u,weight};   nbr[v].push_back(e2);
  }
};

// Dijkstra's Algorithm [Sparse Graphs] (Directed and Undirected) -- O((n+m)*log(n+m))
//  -- Edge weight >= 0.  May use get_path to obtain the path.

typedef vector<Edge>::const_iterator EdgeIter;

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

void dijkstra2(const Graph &G, int src, vector<int> &D) {
  typedef pair<int,int> pii;
  int n = G.num_nodes;
  vector<bool> used(n, false);
  priority_queue<pii, vector<pii>,  greater<pii> > fringe;

  D.resize(n);  fill(D.begin(), D.end(), -1);  

  D[src] = 0;
  fringe.push(make_pair(0, src));

  while (!fringe.empty()) {
    pii next = fringe.top();    fringe.pop();
    int u = next.second;
    if (used[u]) continue;
    used[u] = true;

    for (EdgeIter it = G.nbr[u].begin(); it != G.nbr[u].end(); ++it) {
      int v = it->to;

      int hours = next.first % 24;
      assert(hours <= 12);
      int weight = it->weight + next.first;
      if (hours + it->weight > 12) {
	weight += 24 - hours;
      }
      if (used[v]) continue;
      if (D[v] == -1 || weight < D[v]) {
	D[v] = weight;
	fringe.push(make_pair(D[v], v));
      }
    }
  }
}

int main()
{
  int n, m;
  cin >> n >> m;

  Graph G(n);
  for (int i = 0; i < m; i++) {
    int u, v, d;
    cin >> u >> v >> d;
    G.add_edge(u, v, d);
  }
  
  vector<int> D, P;
  dijkstra(G, 0, D, P);

  int d = D[n-1];
  int knight = (d) ? ((d + 11)/12 - 1) * 12 + d : 0;

  vector<int> D2;
  dijkstra2(G, 0, D2);
  int day = D2[n-1];

  cout << day - knight << endl;

  return 0;
}
