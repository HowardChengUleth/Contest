#include <iostream>
#include <algorithm>

using namespace std;

bool dfs(bool adj[300][300], int n, int v, int color[], int curr = 1)
{
  if (color[v] > 0) {
    return color[v] == curr;
  }

  color[v] = curr;
  for (int w = 0; w < n; w++) {
    if (adj[v][w]) {
      if (!dfs(adj, n, w, color, 3-curr)) {
	return false;
      }
    }
  }
  return true;
}

bool solve()
{
  int n;
  cin >> n;
  if (!n) return false;

  bool adj[300][300];
  for (int i = 0; i < n; i++) {
    fill(adj[i], adj[i]+n, false);
  }
  int u, v;
  while (cin >> u >> v && (u || v)) {
    adj[u-1][v-1] = adj[v-1][u-1] = true;
  }

  int color[300] = {0};
  bool good = true;
  for (int i = 0; i < n && good; i++) {
    if (color[i]) continue;
    good &= dfs(adj, n, i, color);
  }
  cout << (good ? "YES" : "NO") << endl;
  
  return true;
}

int main()
{
  while (solve())
    ;
  return 0;
}
