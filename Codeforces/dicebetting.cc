#include <bits/stdc++.h>

using namespace std;

double memo[10001][501];

// prob of exactly k different numbers in n throws
double f(int n, int k, int s)
{
  if (k == 0 || k > n) {
    return 0.0;
  }
  if (n == 1 && k == 1) {
    return memo[n][k] = 1.0;
  }
  if (memo[n][k] >= 0.0) {
    return memo[n][k];
  }

  // the n-th row is either a new one or a duplicate
  memo[n][k] = f(n-1,k,s) * (double)k/s +
    f(n-1,k-1,s) * (double)(s-k+1)/s;
  return memo[n][k];
}

int main()
{
  int n, s, k;
  cin >> n >> s >> k;

  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= s; j++) {
      memo[i][j] = -1.0;
    }
  }
  
  double ans = 0.0;
  for (int i = k; i <= min(n,s); i++) {
    ans += f(n, i, s);
  }
  cout << fixed << setprecision(10) << ans << endl;
  
  return 0;
}
