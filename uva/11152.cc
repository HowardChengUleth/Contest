#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double PI = acos(-1.0);

int main()
{
  double a, b, c;
  while (cin >> a >> b >> c) {
    double s = (a+b+c)/2.0;
    double tri = sqrt(s*(s-a)*(s-b)*(s-c));
    double incircle = (s-a)*(s-b)*(s-c)*PI/s;
    double outcircle = (a*a*b*b*c*c)*PI/(16*s*(s-a)*(s-b)*(s-c));

    cout << fixed << setprecision(4) << outcircle - tri << ' '
	 << tri - incircle << ' ' << incircle << endl;
  }
  return 0;
}
