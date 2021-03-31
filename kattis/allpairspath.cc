#include <bits/stdc++.h>

using namespace std;

const long long inf = INT_MAX;

bool solve()
{
  int n, m, q;
  cin >> n >> m >> q;
  if (!n && !m && !q)
    return false;

  long long D[150][150];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      D[i][j] = inf;
    }
    D[i][i] = 0;
  }

  for (int i = 0; i < m; i++) {
    long long u, v, w;
    cin >> u >> v >> w;
    D[u][v] = min(D[u][v], w);
  }

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
	if (max(D[i][k], D[k][j]) < inf) {
	  D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
	}
      }
    }
  }

  for (int i = 0; i < q; i++) {
    int u, v;
    cin >> u >> v;

    if (D[u][v] == inf) {
      cout << "Impossible" << endl;
      continue;
    }

    bool negcycle = false;
    for (int k = 0; k < n; k++) {
      negcycle |= (D[k][k] < 0 && max(D[u][k], D[k][v]) < inf);
    }

    if (negcycle) {
      cout << "-Infinity" << endl;
    } else {
      cout << D[u][v] << endl;
    }
  }

  cout << endl;
  
  
  return true;
}

int main()
{
  while (solve())
    ;

  return 0;
}
