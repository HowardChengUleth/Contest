// note: we cannot have two big caves connected to each other or we will
// be able to go in an infinite loop

#include <bits/stdc++.h>

using namespace std;

map<string,int> idx;

struct Graph
{
  int n;
  vector<vector<int>> adj;

  Graph(int N)
    : n(N), adj(N)
  {
  }

  void add_edge(int u, int v)
  {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
};

int find_idx(string s)
{
  if (idx.find(s) == idx.end()) {
    int n = idx.size();
    idx[s] = n;
  }
  return idx[s];
}

Graph G(1000);
vector<bool> small(1000, false);

int search(int curr, vector<bool> &visited)
{
  if (curr == 1) {
    return 1;
  }

  visited[curr] = true;
  
  int ans = 0;
  for (auto u : G.adj[curr]) {
    if (small[u] && visited[u]) continue;
    ans += search(u, visited);
  }
  visited[curr] = false;

  return ans;

}

int main()
{
  idx["start"] = 0;
  idx["end"] = 1;

  string s;
  while (cin >> s) {
    replace(begin(s), end(s), '-', ' ');
    istringstream iss(s);
    string u, v;
    iss >> u >> v;

    G.add_edge(find_idx(u), find_idx(v));
    small[find_idx(u)] = islower(u[0]);
    small[find_idx(v)] = islower(v[0]);
  }

  vector<bool> visited(1000, false);
  int ans = search(0, visited);

  cout << ans << endl;
  
  return 0;
}
