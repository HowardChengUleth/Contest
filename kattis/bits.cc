#include <bits/stdc++.h>

using namespace std;

void solve()
{
  int X;
  cin >> X;

  int ans = 0;
  int curr = 0;
  string s = to_string(X);
  for (auto c : s) {
    int val = c - '0';
    curr = curr * 10 + val;
    ans = max(ans, __builtin_popcount(curr));
  }
  cout << ans << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T--)
    solve();
  
  return 0;
}
