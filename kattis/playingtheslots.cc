/*
 * Distance from a point to an (infinite) line.
 *
 * Author: Howard Cheng
 * Reference:
 *   http://www.exaflop.org/docs/cgafaq/cga1.html
 *
 * This routine computes the shortest distance from a point to a line.
 * ie. distance from point to its orthogonal projection onto the line.
 * Works even if the projection is not on the line (i.e. treat the line
 * as infinite line).
 *
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>

using namespace std;

struct Point {
  double x, y;
};

/* computes the distance from "c" to the line defined by "a" and "b" */
double dist_line(Point a, Point b, Point c)
{
  double L2, s;

  L2 = (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);
  assert(L2 > 0);
  s = ((a.y-c.y)*(b.x-a.x)-(a.x-c.x)*(b.y-a.y)) / L2;

  return fabs(s*sqrt(L2));
}

int main(void)
{
  Point poly[20];
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> poly[i].x >> poly[i].y;
  }

  double ans = 1e10;
  for (int i = 0; i < N; i++) {
    Point p1 = poly[i], p2 = poly[(i+1)%N];
    double max_d = 0;
    for (int j = 0; j < N; j++) {
      max_d = max(max_d, dist_line(p1, p2, poly[j]));
    }
    ans = min(ans, max_d);
  }
  cout << fixed << setprecision(10) << ans << endl;
  return 0;
}
