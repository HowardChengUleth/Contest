#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
  int a1, b1, c1;
  int a2, b2, c2;
  while (cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2 &&
	 (a1 || b1 || c1 || a2 || b2 || c2)) {
    int det = a1*b2 - b1*a2;
    if (det == 0) {
      cout << "No fixed point exists." << endl;
    } else {
      int nx = c1*b2 - c2*b1;
      int ny = a1*c2 - a2*c1;

      // deal with -0.00 problem
      double x = (nx) ? (double)(nx)/det : 0;
      double y = (ny) ? (double)(ny)/det : 0;
      cout << "The fixed point is at " << fixed << setprecision(2)
	   << x << ' ' << y << '.' << endl;
    }

  }
  return 0;
}
