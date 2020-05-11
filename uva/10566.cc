//
// We are going to call the ladder lengths l1 and l2 instead, with l1 being
// x and l2 being y.  Assuming that the base of left building is (0,0), then
// the equations of the lines for the two ladders are:
//
// y = -sqrt(l1^2 - w^2)/w * x + sqrt(l1^2 - w^2)
// y = sqrt(l2^2 - w^2)/w * x
//
// At the point of intersection, y = c.  Solving each equation for x,
// equating the two sides give the relation:
//
//  f(w) = c/sqrt(l1^2 - w^2) + c/sqrt(l2^2 - w^2) - 1 = 0
//
// Notice that 0 < w < min(l1, l2), and that f is strictly increasing in
// this range.  So we can solve with bisection

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

double f(double l1, double l2, double c, double w)
{
  return c/sqrt(l1*l1 - w*w) + c/sqrt(l2*l2 - w*w) - 1;
}

double solve(double l1, double l2, double c)
{
  double lo = 1e-5;
  double hi = min(l1, l2) - 1e-5;

  while (hi - lo >= 1e-5) {
    double mid = (lo + hi) / 2;
    if (f(l1, l2, c, mid) < 0) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  return (lo+hi)/2;
}

int main(void)
{
  double l1, l2, c;
  while (cin >> l1 >> l2 >> c) {
    cout << fixed << setprecision(3) << solve(l1, l2, c) << endl;
  }
  return 0;
}
