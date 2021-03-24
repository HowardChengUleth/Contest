#include <bits/stdc++.h>

using namespace std;

int P, n;
int b[100];

// best[i][j] = min number of coins to make sum i, using coins 1, ..., j-1
//              10000 if impossible to make the sum
//              -1 if uninitialized
const int INF = 10000;
int best[20001][101];

int f(int S, int k)
{
  if (k == 0) {
    return (S == 0) ? 0 : INF;
  }
  if (best[S][k] >= 0) {
    return best[S][k];
  }

  // don't use coin k-1
  int t1 = f(S, k-1);

  // use coin k-1
  int t2 = (b[k-1] <= S) ? f(S - b[k-1], k-1) + 1 : INF;

  return best[S][k] = min(t1, t2);
}

void solve()
{
  cin >> P >> n;
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }

  for (int i = 0; i <= 20000; i++) {
    fill(best[i], best[i]+n+1, -1);
  }

  for (int i = P; true; i++) {
    if (f(i, n) <= n) {
      cout << i << ' ' << best[i][n] << endl;
      break;
    }
  }
}

int main()
{
  int C;
  cin >> C;
  while (C--) {
    solve();
  }

  return 0;
}
