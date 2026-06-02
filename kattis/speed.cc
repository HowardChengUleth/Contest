#include <bits/stdc++.h>

using namespace std;

double trip_time(const vector<int> &d, const vector<int> &s,
		 int n, double c)
{
  double total = 0.0;
  for (int i = 0; i < n; i++) {
    double real_s = s[i] + c;
    if (real_s <= 0.0) {
      // return infinity...can't get there
      return numeric_limits<double>::infinity();
    }
    total += d[i] / real_s;
  }
  return total;
}

int main()
{
  int n, t;
  cin >> n >> t;

  vector<int> d(n), s(n);
  for (int i = 0; i < n; i++) {
    cin >> d[i] >> s[i];
  }

  // find lower bound...could just find the min c to make s+c >= 0 for all
  // s...
  double lo = -1;
  while (trip_time(d, s, n, lo) < t) {
    // slow down
    lo *= 2;
  }

  // find upper bound
  double hi = 1;
  while (trip_time(d, s, n, hi) > t) {
    // speed up
    hi *= 2;
  }

  // invariant: trip_time(lo) >= t
  //            trip_time(hi) <= t
  while (hi - lo > 1e-8) {
    double mid = (lo + hi)/2;
    if (trip_time(d, s, n, mid) >= t) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  cout << fixed << setprecision(10) << hi << endl;

  return 0;
}
