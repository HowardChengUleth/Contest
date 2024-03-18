#include <bits/stdc++.h>

using namespace std;

/*
 * Line Intersection
 *
 * Author: Howard Cheng
 * Reference:
 *   CLRS, "Introduction to Algorithms", 2nd edition, pages 936-939.
 *
 * Given two lines specified by their endpoints (a1, a2) and (b1, b2),
 * returns true if they intersect, and false otherwise.  The intersection
 * point is not known.
 *
 */

#include <iostream>
#include <cmath>

using namespace std;

/* how close to call equal */
const double EPSILON = 1E-8;

struct Point {
  double x, y;

  Point(double xx, double yy) : x{xx}, y{yy} {}
};

double direction(Point p1, Point p2, Point p3)
{
  double x1 = p3.x - p1.x;
  double y1 = p3.y - p1.y;
  double x2 = p2.x - p1.x;
  double y2 = p2.y - p1.y;
  return x1*y2 - x2*y1;
}

int on_segment(Point p1, Point p2, Point p3)
{
  return ((p1.x <= p3.x && p3.x <= p2.x) || (p2.x <= p3.x && p3.x <= p1.x)) &&
    ((p1.y <= p3.y && p3.y <= p2.y) || (p2.y <= p3.y && p3.y <= p1.y));
}

int intersect(Point a1, Point a2, Point b1, Point b2)
{
  double d1 = direction(b1, b2, a1);
  double d2 = direction(b1, b2, a2);
  double d3 = direction(a1, a2, b1);
  double d4 = direction(a1, a2, b2);

  if (((d1 > EPSILON && d2 < -EPSILON) || (d1 < -EPSILON && d2 > EPSILON)) &&
      ((d3 > EPSILON && d4 < -EPSILON) || (d3 < -EPSILON && d4 > EPSILON))) {
    return 1;
  } else {
    return (fabs(d1) < EPSILON && on_segment(b1, b2, a1)) ||
      (fabs(d2) < EPSILON && on_segment(b1, b2, a2)) ||
      (fabs(d3) < EPSILON && on_segment(a1, a2, b1)) ||
      (fabs(d4) < EPSILON && on_segment(a1, a2, b2));
  }
}

int main()
{
  int x1, x2, y1, y2;
  cin >> x1 >> x2 >> y1 >> y2;

  int xs, ys, xr, yr;
  cin >> xs >> ys >> xr >> yr;

  int dx = xr - xs, dy = yr - ys;

  int mult = 2;
  while (x1 <= xr && xr <= x2 && y1 <= yr && yr <= y2) {
    xr = xs + mult*dx;
    yr = ys + mult*dy;
    mult *= 2;
  }

  Point a(xs, ys), b(xr, yr);
  bool bottom = intersect(a, b, Point(x1,y1), Point(x2,y1));
  bool top = intersect(a, b, Point(x1,y2), Point(x2,y2));
  bool left = intersect(a, b, Point(x1,y1), Point(x1,y2));
  bool right = intersect(a, b, Point(x2,y1), Point(x2,y2));

  if (top) {
    cout << "top";
  } else if (bottom) {
    cout << "bottom";
  }

  if ((top || bottom) && (left || right)) {
    cout << "-";
  }
  
  if (left) {
    cout << "left";
  } else if (right) {
    cout << "right";
  }

  cout << endl;
  
  return 0;
}
