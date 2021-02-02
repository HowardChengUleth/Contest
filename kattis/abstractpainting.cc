#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;


using namespace std;

ll fast_exp(ll b, ll n, ll m)
{
  ll res = 1;
  long long x = b;

  while (n > 0) {
    if (n & 0x01) {
      n--;
      res = (res * x) % m;
    } else {
      n >>= 1;
      x = (x * x) % m;
    }
  }

  return res;
}

int main()
{
  int T;
  cin >> T;

  while (T--) {
    int R, C;
    cin >> R >> C;
    ll ans = fast_exp(3, (R+C), MOD) * fast_exp(2, (R*C), MOD) % MOD;
    cout << ans << endl;
  }
  
  return 0;
}
