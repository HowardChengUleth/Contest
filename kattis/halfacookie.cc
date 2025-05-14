#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1.0);

bool solve()
{
  double r, x, y;
  if (!(cin >> r >> x >> y))
    return false;

  double d2 = x*x + y*y;
  if (d2 > r*r) {
    cout << "miss" << endl;
  } else {
    double area_circle = PI * r * r;
    double d = sqrt(d2);
    double theta = acos(d / r) * 2;
    double sector = (1 - theta/(2*PI)) * area_circle;
    double wedge = sqrt(r*r - d*d) * d;
    double p1 = sector + wedge;
    double p2 = area_circle - p1;

    if (p1 < p2) {
      swap(p1, p2);
    }

    cout << fixed << setprecision(10) << p1 << ' ' << p2 << endl;
  }
  
  return true;
}

int main()
{
  while (solve())
    ;
  
  return 0;
}
