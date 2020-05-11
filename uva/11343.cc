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
#include <numeric>

using namespace std;

struct Point {
  int x, y;
};

int direction(Point p1, Point p2, Point p3)
{
  int x1 = p3.x - p1.x;
  int y1 = p3.y - p1.y;
  int x2 = p2.x - p1.x;
  int y2 = p2.y - p1.y;
  return x1*y2 - x2*y1;
}

int on_segment(Point p1, Point p2, Point p3)
{
  return ((p1.x <= p3.x && p3.x <= p2.x) || (p2.x <= p3.x && p3.x <= p1.x)) &&
    ((p1.y <= p3.y && p3.y <= p2.y) || (p2.y <= p3.y && p3.y <= p1.y));
}

int intersect(Point a1, Point a2, Point b1, Point b2)
{
  int d1 = direction(b1, b2, a1);
  int d2 = direction(b1, b2, a2);
  int d3 = direction(a1, a2, b1);
  int d4 = direction(a1, a2, b2);

  if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
      ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
    return 1;
  } else {
    return (d1 == 0 && on_segment(b1, b2, a1)) ||
      (d2 == 0 && on_segment(b1, b2, a2)) ||
      (d3 == 0 && on_segment(a1, a2, b1)) ||
      (d4 == 0 && on_segment(a1, a2, b2));
  }
}

int main(void)
{
  int N;
  cin >> N;

  while (N-- > 0) {
    int M;
    cin >> M;

    Point line[100][2];
    for (int i = 0; i < M; i++) {
      cin >> line[i][0].x >> line[i][0].y;
      cin >> line[i][1].x >> line[i][1].y;
    }

    int isolated[100];
    fill(isolated, isolated+M, 1);

    for (int i = 0; i < M; i++) {
      for (int j = 0; j < M; j++) {
	if (i != j &&
	    intersect(line[i][0], line[i][1], line[j][0], line[j][1])) {
	  isolated[i] = isolated[j] = 0;
	}
      }
    }

    cout << accumulate(isolated, isolated+M, 0) << endl;
  }

  return 0;
}

