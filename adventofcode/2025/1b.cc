#include <bits/stdc++.h>

using namespace std;

int main()
{
  int pos = 50;
  int MOD = 100;

  int ans = 0;
  
  char dir;
  int amt;
  while (cin >> dir >> amt) {
    ans += amt / MOD;
    amt %= MOD;
    if (dir == 'L') {
      ans += (pos > 0 && amt >= pos);
      pos = (pos + MOD - amt) % MOD;
    } else {
      ans += (pos > 0 && amt >= MOD-pos);
      pos = (pos + amt) % MOD;
    }
  }
  cout << ans << endl;
  return 0;
}
