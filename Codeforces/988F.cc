#include <bits/stdc++.h>

using namespace std;

// this is standard DP.
//
// Note that there is no reason to ever carry more than 1 umbrella
//
// So at each point we can carry any one of the m umbrellas.  We can compute
// f(x, k) = what is the minimum total fatigue if we start the journey at
// location x, while carrying umbrella k (use 0 for not carrying anything)
//

typedef long long ll;

int a, n, m;
int rain[2001];
int p[2001];
int umbrella[2001];
ll memo[2001][2001];

ll f(int x, int k)
{
  if (memo[x][k] >= 0) {
    return memo[x][k];
  }
  if (x == a) {
    return 0;
  }

  memo[x][k] = INT_MAX;

  // you can carry the current umbrella
  if (k) {
    memo[x][k] = min(memo[x][k], p[k] + f(x+1, k));
  }

  // if there is an umbrella you can pick it up instead
  int k2 = umbrella[x];
  if (k2) {
    memo[x][k] = min(memo[x][k], p[k2] + f(x+1, k2));
  }
  
  if (!rain[x] || !rain[x+1] || (rain[x] != rain[x+1])) {
    // you can also drop the umbrella
    memo[x][k] = min(memo[x][k], f(x+1, 0));
  }

  return memo[x][k];
}


int main()
{
  cin >> a >> n >> m;
  for (int i = 0; i < n; i++) {
    int l, r;
    cin >> l >> r;
    fill(rain+l, rain+r+1, i+1);
  }
  for (int i = 0; i < m; i++) {
    int x, w;
    cin >> x >> w;
    p[i+1] = w;
    if (!umbrella[x] || w < p[umbrella[x]]) {
      umbrella[x] = i+1;
    }
  }

  for (int i = 0; i <= a; i++) {
    for (int j = 0; j <= m; j++) {
      memo[i][j] = -1;
    }
  }

  ll ans = f(0,0);
  if (ans >= INT_MAX) {
    cout << -1 << endl;
  } else {
    cout << ans << endl;
  }
  
  return 0;
}
