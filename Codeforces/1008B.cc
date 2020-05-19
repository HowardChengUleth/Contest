#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  int w[100000], h[100000];
  bool dp[2][100000];

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> w[i] >> h[i];
  }

  dp[0][0] = dp[1][0] = true;

  for (int i = 1; i < n; i++) {
    dp[0][i] = (h[i] <= h[i-1] && dp[0][i-1]) ||
      (h[i] <= w[i-1] && dp[1][i-1]);
    dp[1][i] = (w[i] <= h[i-1] && dp[0][i-1]) ||
      (w[i] <= w[i-1] && dp[1][i-1]);
  }

  if (dp[0][n-1] || dp[1][n-1]) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }
  

  return 0;
}
