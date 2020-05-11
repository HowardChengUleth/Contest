#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll H, n;
ll d[200000];
ll ps[200000];

int main()
{
  cin >> H >> n;
  for (int i = 0; i < n; i++) {
    cin >> d[i];
  }
  partial_sum(d, d+n, ps);
  ll ans = -1;
  ll total = ps[n-1];
  for (int i = 0; i < n; i++) {
    if (H + ps[i] <= 0) {
      cout << i+1 << endl;
      return 0;
    }

    if (total < 0) {
      ll k = (H + ps[i] - total - 1) / (-total);
      ll t = i+1 + k*n;
      if (ans < 0 || t < ans) {
	ans = t;
      }
    }
  }
  cout << ans << endl;

  return 0;
}
