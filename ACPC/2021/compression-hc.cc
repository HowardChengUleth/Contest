#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
int n, c;
int x[1000001];

ll memo[1000001][32][2];

bool in_range(int x, int p, int s, int m)
{
  if (m) {
    int d = x - p;
    if (s == 0)
      return (d == 0);
    ll lim = (1LL << (s-1));
    return (-lim <= d && d < lim);
  } else {
    return x < (1LL << s);
  }
}

// best way to do it for x[i..n-1], if the last mode is m and current size is s
ll f(int i, int s, int m)
{
  if (i > n) {
    return 0;
  }

  ll &ans = memo[i][s][m];
  if (ans >= 0) {
    return ans;
  }

  ans = INT_MAX;
  if (!(in_range(x[i], x[i-1], s, m)))
    return ans;
  
  // can keep going
  ans = min(ans, f(i+1, s, m) + s);

  // can also switch
  for (int s2 = 0; s2 <= 31; s2++) {
    ans = min(ans, s + f(i+1, s2, 0) + c);
    ans = min(ans, s + f(i+1, s2, 1) + c);
  }

  return ans;
}


int main()
{
  cin >> n >> c;
  for (int i = 1; i <= n; i++) {
    cin >> x[i];
  }

  for (int i = 0; i <= n; i++) {
    for (int s = 0; s <= 31; s++) {
      for (int m = 0; m < 2; m++) {
	memo[i][s][m] = -1;
      }
    }
  }
  
  ll ans = INT_MAX;
  for (int s = 0; s <= 31; s++) {
    ans = min(ans, f(1, s, 0) + c);
    ans = min(ans, f(1, s, 1) + c);
  }

  cout << ans << endl;

  return 0;
}
