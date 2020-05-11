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

const int MAX_N = 300;

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

#include <string>
#include <map>
#include <cassert>

void solve()
{
  int n;
  cin >> n;

  map<string,int> id_map;
  int id[300];
  string have[300], want[300];

  Graph G(n);
  for (int i = 0; i < n; i++) {
    string name;
    cin >> name >> have[i] >> want[i];
    if (id_map.find(name) == id_map.end()) {
      int t = id_map.size();
      id_map[name] = t;
    }
    id[i] = id_map[name];
    for (int j = 0; j < i; j++) {
      if (id[i] != id[j] && want[i] == have[j] && want[j] == have[i]) {
	G.add_edge(id[i],id[j]);
	assert(0 <= id[i] && id[i] < n);
	assert(0 <= id[j] && id[j] < n);
      }
    }
  }

  int match[300];
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
