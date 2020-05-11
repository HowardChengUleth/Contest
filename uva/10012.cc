#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <cstdio>

using namespace std;

const double EPS = 0;

double solve_perm(double r[], int n)
{
  double x[8];
  const double rightmost = *max_element(r, r+n) * 2 * 10;
  
  x[0] = r[0];
  for (int i = 1; i < n; i++) {
    x[i] = rightmost;
    for (int j = 0; j < i; j++) {
      double c = r[j] + r[i];
      double a = abs(r[j]-r[i]);
      double b = sqrt(c*c - a*a);
      
      double xi = x[j] + b;
      bool good = true;
      for (int k = 0; k < i; k++) {
	if (j == k) continue;
	double lhs = (x[k]-xi)*(x[k]-xi) + (r[i]-r[k])*(r[i]-r[k]);
	double rhs = (r[i]+r[k])*(r[i]+r[k]);
	if (lhs < rhs + EPS) {
	  good = false;
	}
      }
      if (good) {
	x[i] = min(x[i], xi);
      }
    }
  }
  
  double left = rightmost,  right = 0.0;
  for (int i = 0; i < n; i++) {
    left = min(left, x[i] - r[i]);
    right = max(right, x[i] + r[i]);
  }
  return right-left;
}

int main()
{
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    assert(0 < n && n <= 8);
    double r[8];
    for (int i = 0; i < n; i++) {
      cin >> r[i];
    }

    double best = solve_perm(r, n);
    sort(r, r+n);
    do {
      best = min(best, solve_perm(r, n));
    } while (next_permutation(r, r+n));

    cout << fixed << setprecision(3) << best << endl;
  }
  return 0;
}
