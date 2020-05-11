/*
 * Parameters of circle from 3 points
 *
 * Author: Howard Cheng
 * Reference:
 *   http://www.exaflop.org/docs/cgafaq/
 *
 * This routine computes the parameters of a circle (center and radius)
 * from 3 points.  Returns non-zero if successful, zero if the three
 * points are colinear.
 *
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>

using namespace std;

/* how close to call equal */
const double EPSILON = 1E-5;

struct Point {
  double x, y;
};

int circle(Point p1, Point p2, Point p3, Point &center, double &r)
{
  double a,b,c,d,e,f,g;

  a = p2.x - p1.x;
  b = p2.y - p1.y;
  c = p3.x - p1.x;
  d = p3.y - p1.y;
  e = a*(p1.x + p2.x) + b*(p1.y + p2.y);
  f = c*(p1.x + p3.x) + d*(p1.y + p3.y);
  g = 2.0*(a*(p3.y - p2.y) - b*(p3.x - p2.x));
  if (fabs(g) < EPSILON) {
    return 0;
  }
  center.x = (d*e - b*f) / g;
  center.y = (a*f - c*e) / g;
  r = sqrt((p1.x-center.x)*(p1.x-center.x) + (p1.y-center.y)*(p1.y-center.y));
  return 1;
}

const double PI = acos(-1.0);

// angle between ab and ac
double angle(Point a, Point b, Point c)
{
  b.x -= a.x; b.y -= a.y;
  c.x -= a.x; c.y -= a.y;
  double dot = b.x*c.x + b.y*c.y;
  double blen = sqrt(b.x*b.x + b.y*b.y);
  double clen = sqrt(c.x*c.x + c.y*c.y);
  double arg = dot/(blen*clen);
  arg = max(-1.0, arg);
  arg = min(1.0, arg);
  return acos(arg);
}

double distInt(double x)
{
  return fabs(floor(x+0.5) - x);
}

void solve()
{
  Point a, b, c, center;
  double r;

  cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
  circle(a, b, c, center, r);

  double ang1 = angle(center, a, b);
  double ang2 = angle(center, b, c);

  for (int n = 3; n <= 200; n++) {
    double dist1 = distInt(ang1/(2*PI/n));
    double dist2 = distInt(ang2/(2*PI/n));
    if (dist1 < EPSILON && dist2 < EPSILON) {
      cout << n << endl;
      return;
    }
  }
}

int main()
{
  int n;
  cin >> n;
  while (n--) {
    solve();
  }
  return 0;
}

