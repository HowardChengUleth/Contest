#include <bits/stdc++.h>

using namespace std;

// f(a) = a + s - a * cosh(d/(2*a))
//
// we could substitute b = d/2a just to simplify things, so that
//
// f(b) = d/2b + s - d/2b cosh(b) = s + d/2b(1 - cosh(b))
//
// b is now "inverse" of a.  So if f(b) is decreasing, then f(a) is increasing
//
// f'(b) = d/2b^2 (cosh(b) - 1 - b*sinh(b))
//
// d/2b^2 > 0, so we only have to find the sign of (cosh(b) - 1 - b*sinh(b))
// It turned out that it is negative...with calculus
//
// so f(b) is decreasing and hence f(a) is increasing
double f(double a, double s, double d)
{
  return a + s - a * cosh(d/(2*a));
}

int main()
{
  int d, s;
  cin >> d >> s;

  double lo = 1, hi = 1;

  while (f(lo, s, d) >= 0) {
    lo *= 0.5;
  }
  while (f(hi, s, d) < 0) {
    hi *= 2;
  }

  // now f(lo) < 0 and f(hi) >= 0
  while (hi - lo > 1e-10) {
    double mid = (lo+hi)/2;
    if (f(mid, s, d) < 0) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  double ans = 2 * hi * sinh(d/2.0/hi);
  cout << fixed << setprecision(10) << ans << endl;
  return 0;
}
