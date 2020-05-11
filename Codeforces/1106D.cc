#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n, m;
  vector<int> G[100001];

  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  priority_queue<int, vector<int>, greater<int>> pq;
  bool visited[100001] = {false};
  visited[1] = true;
  for (auto v : G[1]) {
    pq.push(v);
  }
  cout << 1;
  for (int i = 1; i < n; i++) {
    while (visited[pq.top()]) {
      pq.pop();
    }

    int u = pq.top();
    pq.pop();
    visited[u] = true;
    for (auto v : G[u]) {
      if (!visited[v])
	pq.push(v);
    }
    cout << ' ' << u;
  }
  cout << endl;
  
  return 0;
}
