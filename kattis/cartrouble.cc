#include <bits/stdc++.h>

using namespace std;

void BFS(const vector<vector<int>> &G, int src, vector<bool> &visited)
{
  queue<int> Q;
  Q.push(src);
  visited[src] = true;
  while (!Q.empty()) {
    int curr = Q.front();
    Q.pop();
    for (auto v : G[curr]) {
      if (!visited[v]) {
	Q.push(v);
	visited[v] = true;
      }
    }
  }
}

int main()
{
  int n;
  cin >> n;

  vector<vector<int>> G(1000), Grev(1000);
  vector<int> ID(n);

  for (int i = 0; i < n; i++) {
    int deg;
    cin >> ID[i] >> deg;
    for (int j = 0; j < deg; j++) {
      int v;
      cin >> v;
      G[ID[i]].push_back(v);
      Grev[v].push_back(ID[i]);
    }
  }

  vector<bool> reach(1000, false), reachrev(1000, false);

  BFS(G, 0, reach);
  BFS(Grev, 0, reachrev);

  bool bad = false;
  for (int i = 0; i < n; i++) {
    if (!reachrev[ID[i]]) {
      cout << "TRAPPED " << ID[i] << endl;
      bad = true;
    }
  }
  for (int i = 0; i < n; i++) {
    if (!reach[ID[i]]) {
      cout << "UNREACHABLE " << ID[i] << endl;
      bad = true;
    }
  }

  if (!bad) {
    cout << "NO PROBLEMS" << endl;
  }
  
  return 0;
}
