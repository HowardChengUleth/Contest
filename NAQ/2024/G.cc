#include <bits/stdc++.h>

using namespace std;

map<int, vector<int>> G;

// we separate all the gears by teeth size.  Gears of different teeth sizes
// do not interact with each other.
//
// among those of the same teeth size, sort the gears by number of teeth
// in decreasing order.  Then we want to use the largest one to turn the
// smallest one, 2nd largest to turn 2nd smallest, etc.
//
// You can work out the product of fractions to see that this is the best
// possible.
//
// and the log of product of ratios can be computed by adding log of the
// numerators and subtracting log of denominators

int main()
{
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    int s, c;
    cin >> s >> c;
    G[s].push_back(c);
  }

  double ans = 0;
  for (auto [k, v]: G) {
    sort(rbegin(v), rend(v));
    int s = 0, e = v.size() - 1;
    while (s < e) {
      ans += log(v[s++]) - log(v[e--]);
    }
  }

  cout << fixed << setprecision(10) << ans << endl;
  

  return 0;
}
