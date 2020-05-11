#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double PI = acos(-1);

int main(void)
{
  double l, w, h, theta;
  while (cin >> l >> w >> h >> theta) {
    theta *= PI/180.0;

    double A;
    if (l * tan(theta) <= h) {
      A = h*l - l*l*tan(theta)/2;
    } else {
      A = h*h*tan(PI/2-theta)/2;
    }
    cout << fixed << setprecision(3) << A*w << " mL" << endl;
  }

  return 0;
}
