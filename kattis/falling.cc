#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll isqrt(ll sq)
{
  if (sq <= 1) return sq;
  ll lo = 1, hi = sq;
  while (lo < hi) {
    ll mid = lo + (hi-lo)/2;
    ll msq = mid * mid;
    if (msq == sq) return mid;
    if (msq < sq) {
      lo = mid+1;
    } else {
      hi = mid;
    }
  }
  return -1;
}

int main()
{
  ll D;
  cin >> D;
  for (ll n1 = 0; n1 <= D; n1++) {
    ll n2sq = D + n1*n1;
    ll n2 = isqrt(n2sq);
    if (n2 >= 0) {
      cout << n1 << ' ' << n2 << endl;
      return 0;
    }
  }
  cout << "impossible" << endl;
  return 0;
}
