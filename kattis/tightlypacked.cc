#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll sqrt(ll n)
{
  if (n == 1) return 1;
  
  ll lo = 1, hi = 1;
  while (hi*hi <= n) {
    hi *= 2;
  }

  while (lo + 1 != hi) {
    ll mid = lo + (hi-lo)/2;
    if (mid*mid == n) {
      return mid;
    } else if (mid*mid < n) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  return lo;
}

int main()
{
  ll n;
  cin >> n;

  ll root = sqrt(n);
  if (root*root == n) {
    cout << 0 << endl;
    return 0;
  }

  root++;
  ll lo = root, hi = root;
  ll ans = n;
  while (2*lo >= hi) {
    ans = min(ans, lo*hi - n);
    lo--;
    if (!lo) break;
    hi = (n + lo-1)/lo;
  }
  cout << ans << endl;
  
  
  return 0;
}
