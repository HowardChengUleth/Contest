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

const int MAX_N = 200;

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
    for (auto to : G.nbr[v]) {
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

#include <set>

void solve()
{
  int n, m;
  cin >> n >> m;

  int C[MAX_N];
  set<int> S;
  for (int i = 0; i < n; i++) {
    cin >> C[i];
  }
  for (int i = 0; i < m; i++) {
    int x;
    cin >> x;
    S.insert(x);
  }

  Graph G(n);
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      if (S.count(C[i]+C[j])) {
	G.add_edge(i, j);
      }
    }
  }

  int match[MAX_N];
  cout << max_matching(G, match) << endl;
}


int main()
{
  int T;
  cin >> T;
  while (T--)
    solve();
  
  return 0;
}
