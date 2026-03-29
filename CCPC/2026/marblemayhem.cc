// just do the calculations of the time using the formulas and sort them
//
// we could do everything with exact arithmetic but there is a guarantee
// that the times cannot be too close together, so it really doesn't matter
#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  vector<int> h(n), l(n);
  for (int i = 0; i < n; i++) {
    cin >> h[i] >> l[i];
  }

  vector<pair<double, int>> timing(n);
  for (int i = 0; i < n; i++) {
    timing[i].second = i+1;

    // h = height of triangle = opposite side
    // l = ramp = hypotenuse
    // sin(theta) = h/l

    const double g = 9.81;

    // vertical acceleration is g * sin(theta)^2 = g * h^2 / l^2
    // h = 1/2 * vert_acc * t^2
    //
    // t^2 = 2*h / g / (h^2 / l^2) = 2*l^2 / (g*h)

    double t2 = 2.0 * l[i] * l[i] / g / h[i];
    timing[i].first = t2;
  }

  // could actually get rid of /g and 2.0 to make everything rational and
  // exact since we are just comparing.  No need to get exact time

  sort(begin(timing), end(timing));
  for (auto [t, index] : timing) {
    cout << index << endl;
  }

  return 0;
}
