#include <iostream>
#include <algorithm>

using namespace std;

int matching(int n, bool odd_deg[], int D[16][16], int index = 1)
{
  int start = find(odd_deg+index, odd_deg+n+1, true) - odd_deg;
  if (start == n+1) return 0;

  int best = -1;
  odd_deg[start] = false;
  for (int i = start+1; i <= n; i++) {
    if (!odd_deg[i]) continue;
    odd_deg[i] = false;
    int temp = D[start][i] + matching(n, odd_deg, D, start+1);
    odd_deg[i] = true;
    if (best == -1 || temp < best) {
      best = temp;
    }
  }
  odd_deg[start] = true;
  return best;
}

int main(void)
{
  int n, m;

  while (cin >> n && n > 0) {
    cin >> m;
    int D[16][16];
    for (int i = 1; i <= n; i++) {
      fill(D[i]+1, D[i]+n+1, -1);
      D[i][i] = 0;
    }
    bool odd_deg[16];
    fill(odd_deg+1, odd_deg+n+1, false);

    int u, v, len;
    int ans = 0;
    while (m-- > 0) {
      cin >> u >> v >> len;
      ans += len;            // must travel at least that much
      odd_deg[u] = !odd_deg[u];
      odd_deg[v] = !odd_deg[v];
      if (D[u][v] == -1 || len < D[u][v]) {
	D[u][v] = D[v][u] = len;
      }
    }

    for (int k = 1; k <= n; k++) {
      for (int i = 1; i <= n; i++) {
	if (D[i][k] == -1) continue;
	for (int j = 1; j <= n; j++) {
	  if (D[k][j] == -1) continue;
	  if (D[i][j] == -1 || D[i][k] + D[k][j] < D[i][j]) {
	    D[i][j] = D[i][k] + D[k][j];
	  }
	}
      }
    }

    cout << ans + matching(n, odd_deg, D) << endl;

  }

  return 0;
}
