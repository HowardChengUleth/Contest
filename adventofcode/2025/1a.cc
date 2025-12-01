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
    if (dir == 'L') {
      pos = (pos + (MOD - amt % MOD)) % MOD;
    } else {
      pos = (pos + amt) % MOD;
    }
    if (pos == 0) {
      ans++;
    }
  }
  cout << ans << endl;
  return 0;
}
