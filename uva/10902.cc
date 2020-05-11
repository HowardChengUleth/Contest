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

#include <algorithm>

int main(void)
{
  int n;
  while (cin >> n && n > 0) {
    int top[1000];
    int top_num = 0;

    Point line[100000][2];
    for (int i = 0; i < n; i++) {
      cin >> line[i][0].x >> line[i][0].y
	  >> line[i][1].x >> line[i][1].y;
    }

    bool covered[100000];
    fill(covered, covered+n, false);

    for (int i = 0; i < n; i++) {
      bool good = true;
      for (int j = i+1; j < n; j++) {
	if (intersect(line[i][0], line[i][1], line[j][0], line[j][1])) {
	  good = false;
	  break;
	}
      }
      if (good) {
	top[top_num++] = i+1;
      }
    }

    cout << "Top sticks:";
    for (int i = 0; i < top_num; i++) {
      cout << ' ' << top[i];
      if (i < top_num-1) {
	cout << ',';
      }
    }
    cout << '.' << endl;
  }
  
  return 0;
}
