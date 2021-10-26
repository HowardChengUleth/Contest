#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1000000007;

string s;
int n;

ll memo[2001][2001];

ll f(int start, int end)
{
  if (end - start == 1) {
    return memo[start][end] = 1;
  }
  if (end - start == 0) {
    return memo[start][end] = 0;
  }

  if (memo[start][end] >= 0) {
    return memo[start][end];
  }

  ll &ans = memo[start][end];
  ans = 0;

  // if first and last match, then we can keep them both and recurse
  // need to add 1 because the "empty string" recursively has to be counted
  if (s[start] == s[end-1]) {
    ans += f(start+1, end-1) + 1;
    ans %= MOD;
  }

  // we can always remove the first or the last one
  ans += f(start+1, end);
  ans %= MOD;
  ans += f(start, end-1);
  ans %= MOD;

  // double counted the ones that have both removed
  ans += (MOD - f(start+1, end-1));
  ans %= MOD;
      
  return ans;
}

void solve()
{
  cin >> s;
  n = s.length();

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n+1; j++) {
      memo[i][j] = -1;
    }
  }

  cout << f(0, n) << endl;
  
}

int main()
{
  int T;
  cin >> T;

  while (T--) 
    solve();

  return 0;
}
