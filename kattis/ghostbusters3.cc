#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

int main()
{
  ll binom[1001][1001];

  for (int n = 0; n <= 1000; n++) {
    binom[n][0] = binom[n][n] = 1;
    for (int m = 1; m < n; m++) {
      binom[n][m] = (binom[n-1][m-1] + binom[n-1][m]) % MOD;
    }
  }


  int n, m;
  cin >> n >> m;

  if (n == m) {
    cout << 1 << endl;
  } else if (n < m) {
    cout << binom[m][n] << endl;
  } else {
    cout << binom[n-1][m-1] << endl;
  }
  
  return 0;
}
