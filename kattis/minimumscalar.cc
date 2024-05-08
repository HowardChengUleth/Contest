#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void solve()
{
  int n;
  cin >> n;

  vector<ll> x(n), y(n);
  for (auto &t : x) {
    cin >> t;
  }
  for (auto &t : y) {
    cin >> t;
  }


  // suppose x1 < x2 and y1 < y2
  //
  // Then we look at
  //
  //   (x1*y2 + x2*y1) - (x1*y1 + x2*y2)
  // = x1*(y2-y1) - x2*(y2-y1)
  // = (x1-x2) * (y2-y1)
  // < 0
  //
  // so if we look at a list of x and y values and see any pair of adjacent values that
  // is "in order", then we want to swap the y values to get a smaller result
  //
  // applying this repeatedly to adjacent pairs, we want to have x in increasing order
  // and y in decreasing order.  So we just have to sort the lists

  sort(begin(x), end(x));
  sort(begin(y), end(y));

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ans += x[i] * y[n-1-i];
  }

  cout << ans << endl;

}

int main()
{
  int T;
  cin >> T;

  for (int i = 1; i <= T; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }

  return 0;
}
