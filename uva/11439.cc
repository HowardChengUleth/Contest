#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

typedef int Edge;
struct Graph {
  vector<vector<Edge> > nbr;
  int num_nodes;
  Graph(int n) : nbr(n), num_nodes(n) { }
  
  void add_edge(int u, int v) {
    Edge e1 = v;   nbr[u].push_back(e1);
    Edge e2 = u;   nbr[v].push_back(e2);
  }
};

const int MAX_N = 100;

int lca(int match[], int base[], int p[], int a, int b)
{
  bool used[MAX_N] = {false};
  while (true) {
    a = base[a];  used[a] = true;  if (match[a] == -1) break;
    a = p[match[a]];
  }
  while (true) {
    b = base[b];  if (used[b]) return b;  b = p[match[b]];
  }
}

void mark_path(int match[], int base[], bool blossom[], int p[], int v, int b,
	       int c)
{
  for (; base[v] != b; v = p[match[v]]) {
    blossom[base[v]] = blossom[base[match[v]]] = true;
    p[v] = c;   c = match[v];
  }
}

int find_path(const Graph &G, int match[], int p[], int root)
{
  int n = G.num_nodes;
  bool used[MAX_N] = {false};     int base[MAX_N];
  fill(p, p + n, -1);
  for (int i = 0; i < n; i++) base[i] = i;

  used[root] = true;
  queue<int> q;   q.push(root);
  while (!q.empty()) {
    int v = q.front();  q.pop();
    for (int t = 0; t < G.nbr[v].size(); t++) {
      int to = G.nbr[v][t];
      if (base[v] == base[to] || match[v] == to) continue;
      if (to == root || (match[to] != -1 && p[match[to]] != -1)) {
	int cb = lca(match, base, p, v, to);
	bool blossom[MAX_N] = {false};
	mark_path(match, base, blossom, p, v, cb, to);
	mark_path(match, base, blossom, p, to, cb, v);
	for (int i = 0; i < n; i++) {
	  if (blossom[base[i]]) {
	    base[i] = cb;
	    if (!used[i]) { used[i] = true;  q.push(i); }
	  }
	}
      } else if (p[to] == -1) {
	p[to] = v;
	if (match[to] == -1) return to;
	to = match[to];   used[to] = true;  q.push(to);
      }
    }
  }
  return -1;
}

int max_matching(const Graph &G, int match[])
{
  int p[MAX_N];
  int n = G.num_nodes;
  fill(match, match + n, -1);
  for (int i = 0; i < n; i++) {
    if (match[i] != -1) continue;
    int v = find_path(G, match, p, i);
    while (v != -1) {
      int pv = p[v];
      int ppv = match[pv];
      match[v] = pv;
      match[pv] = v;
      v = ppv;
    }
  }

  return (n - count(match, match + n, -1)) / 2;
}

struct GEdge
{
  int w, a, b;
};

void solve()
{
  int N, W;
  cin >> N;
  W = (1 << N);

  GEdge edge[63*32];
  int m = 0;

  for (int i = 0; i < W-1; i++) {
    for (int j = 0; j < W-1-i; j++) {
      edge[m].a = i;
      edge[m].b = i+j+1;
      cin >> edge[m].w;
      m++;
    }
  }

  int lo = 0;  // possible
  int hi = 1000000001;  // impossible
  while (hi - lo > 1) {
    int mid = lo + (hi-lo)/2;
    Graph G(W);
    for (int i = 0; i < m; i++) {
      if (edge[i].w >= mid) {
	G.add_edge(edge[i].a, edge[i].b);
      }
    }
    int match[100];
    if (max_matching(G, match) == W/2) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  cout << lo << endl;
}

int main()
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": ";
    solve();
  }

  return 0;
}
