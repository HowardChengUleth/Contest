#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double compute(int a, int b, double w)
{
  double l = w * a / b;
  double r = sqrt(l*l + w*w)/2;
  double theta = 2*asin(w/2/r);
  return 2*l + 2*theta*r;
}

int main(void)
{
  int a, b;
  char c;
  int case_num = 1;
  
  while (cin >> a >> c >> b) {
    double lo = 0;
    double hi = 1;

    while (compute(a, b, hi) < 400) {
      hi *= 2;
    }

    while (hi - lo >= 1e-8) {
      double mid = (lo+hi)/2.0;
      if (compute(a, b, mid) < 400) {
	lo = mid;
      } else {
	hi = mid;
      }
    }

    double w = (lo+hi)/2.0;
    cout << "Case " << case_num++ << ": " << fixed << setprecision(10)
	 << w*a/b << ' ' << w << endl;
  }
  return 0;
}
