#include <bits/stdc++.h>

using namespace std;

int N, M;

vector<vector<int>> adj;
vector<int> color;

void DFS(int v)
{
  assert(color[v] == 0);
  
  bool used[4] = {false};
  for (auto w : adj[v]) {
    used[color[w]] = true;
  }

  for (int c = 1; c <= 3; c++) {
    if (!used[c]) {
      color[v] = c;
      break;
    }
  }
  assert(color[v] > 0);

  for (auto w : adj[v]) {
    if (color[w] > 0) continue;
    DFS(w);
  }

}

int main()
{
  cin >> N >> M;
  adj.resize(N);
  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  color.resize(N, 0);
  for (int i = 0; i < N; i++) {
    if (color[i] > 0) continue;
    DFS(i);
  }

  for (int i = 0; i < N; i++) {
    cout << color[i] << ' ';
  }
  cout << endl;
  
  return 0;
}
