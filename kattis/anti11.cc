#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;

int main()
{
  int T;
  cin >> T;

  int ans[10001];
  ans[1] = 2;
  ans[2] = 3;
  for (int i = 3; i <= 10000; i++) {
    ans[i] = (ans[i-1] + ans[i-2]) % MOD;
  }

  
  for (int i = 0; i < T; i++) {
    int n;
    cin >> n;
    cout << ans[n] << endl;
  }

  return 0;
}
