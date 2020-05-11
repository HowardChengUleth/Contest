#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct Point
{
  double x, y;
  
  Point(double xx = 0.0, double yy = 0.0)
    : x(xx), y(yy) {}

  double dist(const Point &p)
  {
    return sqrt((p.x-x)*(p.x-x) + (p.y-y)*(p.y-y));
  }
};

int layer(int n)
{
  return (int)(floor(sqrt(n)) + 0.5);
}

Point convert(int n)
{
  int l = layer(n);
  int offset = n - l*l;

  double x = 0.5*(-l + offset);
  double y;
  if (offset % 2 == 0) {
    y = l * sqrt(3)/2;
  } else {
    y = (l-1) * sqrt(3)/2 + 1/sqrt(3);
  }
  return Point(x,y);
}

int main(void)
{
  int n1, n2;
  while (cin >> n1 >> n2) {
    Point p1 = convert(n1), p2 = convert(n2);
    cout << fixed << setprecision(3) << p1.dist(p2) << endl;
  }

  return 0;
}
