#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
int t[1000000];

// dp[i] = cost to take trips up to i
ll dp[1000000];

int main()
{
  ll s, p, m, n;
  cin >> s >> p >> m >> n;
  for (int i = 0; i < n; i++) {
    cin >> t[i];
  }

  dp[0] = min(s, p);
  int start = 0;
  
  for (int i = 1; i < n; i++) {
    // you can always buy single ticket
    dp[i] = s + dp[i-1];
    while (t[start] < t[i] - m + 1) {
      start++;
    }
    dp[i] = min(dp[i], p + (start > 0 ? dp[start-1] : 0));
  }

  cout << dp[n-1] << endl;

  return 0;
}
