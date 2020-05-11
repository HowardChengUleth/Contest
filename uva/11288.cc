#include <iostream>
#include <algorithm>

using namespace std;

int n, m;
int dist[17][17];

int best[(1 << 15)-1];
int bits[(1 << 15)-1];
int baseS[(1 << 15)-1];
int basenum = 0;

void basecase(int S)
{
  int A[5];
  int k = 0;
  for (int i = 0; i < n; i++) {
    if (S & (1 << i)) {
      A[k++] = i+1;
    }
  }

  do {
    int d = dist[0][A[0]] + dist[A[bits[S]-1]][n+1] + 5*bits[S];
    for (int i = 0; i+1 < bits[S]; i++) {
      d += dist[A[i]][A[i+1]];
    }
    if (best[S] < 0 || d < best[S]) {
      best[S] = d;
    }
  } while (next_permutation(A, A+bits[S]));
}

void solve(int S)
{
  if (best[S] >= 0) return;
  if (bits[S] <= 5) {
    return;
  }

  int cars = (bits[S] + 4) / 5;
  for (int i = 0; i < basenum; i++) {
    int mask = baseS[i];
    if (mask & ~S) continue;
    if ((bits[S] - bits[mask] + 4) / 5 != cars-1) continue;
    int newS = S ^ mask;
    solve(newS);
    if (best[S] < 0 || max(best[mask],best[newS]) < best[S]) {
      best[S] = max(best[mask],best[newS]);
    }
  }
}

int main()
{
  cin >> n >> m;
  for (int i = 0; i <= n+1; i++) {
    for (int j = 0; j <= n+1; j++) {
      dist[i][j] = (i == j) ? 0 : -1;
    }
  }

  for (int i = 0; i < m; i++) {
    int u, v, d;
    cin >> u >> v >> d;
    if (dist[u][v] == -1 || d < dist[u][v]) {
      dist[u][v] = dist[v][u] = d;
    }
  }

  for (int k = 0; k <= n+1; k++) {
    for (int i = 0; i <= n+1; i++) {
      for (int j = 0; j <= n+1; j++) {
	if (dist[i][k] == -1 || dist[k][j] == -1) continue;
	int d = dist[i][k] + dist[k][j];
	if (dist[i][j] == -1 || d < dist[i][j]) {
	  dist[i][j] = d;
	}
      }
    }
  }

  fill(best, best + (1 << n), -1);
  best[0] = 0;

  for (int i = 1; i < (1 << n); i++) {
    bits[i] = __builtin_popcount(i);
    if (bits[i] <= 5) {
      basecase(i);
      baseS[basenum++] = i;
    }
  }

  solve((1 << n) - 1);
  cout << best[(1 << n) - 1] << endl;
  
  return 0;
}
