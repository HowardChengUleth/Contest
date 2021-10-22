#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll memo[10001][2];
int N, D;
int H[10000], E[10000];

// minimum number of moves to destroy buildings k..N-1
// where t = 0 (building k destroyed before k-1)
//           1 (building k destroyed after k-1)
//     exp = carried over explosion from building k-1
ll f(int k, int t, ll exp)
{
  if (k >= N) {
    // no more houses
    return 0;
  }
  if (memo[k][t] >= 0) {
    return memo[k][t];
  }

  // destroy k first
  ll ans1 = max(0LL, (H[k] - exp + (D-1))/D)
    + f(k+1, 1, E[k]);

  // destroy k+1 first
  exp += (k+1 < N) ? E[k+1] : 0;
  ll ans2 = max(0LL, (H[k] - exp + (D-1))/D)
    + f(k+1, 0, 0);

  return memo[k][t] = min(ans1, ans2);
}

void solve()
{
  cin >> N >> D;
  for (int i = 0; i < N; i++) {
    cin >> H[i];
  }
  for (int i = 0; i < N; i++) {
    cin >> E[i];
  }

  for (int i = 0; i <= N; i++) {
    memo[i][0] = memo[i][1] = -1;
  }

  cout << f(0, 0, 0) << endl;
}


int main()
{
  int T;
  cin >> T;

  while (T--) {
    solve();
  }

  return 0;
}
