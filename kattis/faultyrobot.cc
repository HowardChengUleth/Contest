#include <bits/stdc++.h>

using namespace std;

typedef pair<int,bool> pib;
typedef pib edge;

vector<vector<edge>> G;

bool visited[1001][2];
bool stuck[1001];

void DFS(pib node)
{
  auto [v, bugged] = node;

  visited[v][bugged] = true;
  bool hasmove = false;
  for (auto e : G[v]) {
    auto [w, forced] = e;

    if (forced) {
      if (!visited[w][bugged]) {
	DFS(pib(w, bugged));
      }
      hasmove = true;
    } else if (!forced && !bugged) {
      if (!visited[w][true]) {
	DFS(pib(w, true));
      }
    }
  }

  stuck[v] |= !hasmove;
}

int main()
{
  int n, m;
  cin >> n >> m;

  G.resize(n+1);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    G[abs(a)].emplace_back(b, a < 0);
  }

  DFS(pib(1, false));

  cout << count(stuck, stuck+n+1, true) << endl;
  
  return 0;
}
