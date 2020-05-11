/*
 * Point-in-polygon test
 *
 * Author: Howard Cheng
 * Reference:
 *   http://www.exaflop.org/docs/cgafaq/cga2.html
 *
 * Given a polygon as a list of n vertices, and a point, it returns
 * whether the point is in the polygon or not.
 *
 * One has the option to define the behavior on the boundary.
 *
 */

#include <iostream>
#include <cmath>
#include <cassert>
#include <string>

using namespace std;

/* how close to call equal */
const double EPSILON = 1E-8;

/* what should be returned on the boundary? */
const bool BOUNDARY = true;

struct Point {
  double x, y;
};

/* counterclockwise, clockwise, or undefined */
enum Orientation {CCW, CW, CNEITHER};

Orientation ccw(Point a, Point b, Point c)
{
  double dx1 = b.x - a.x;
  double dx2 = c.x - b.x;
  double dy1 = b.y - a.y;
  double dy2 = c.y - b.y;
  double t1 = dy2 * dx1;
  double t2 = dy1 * dx2;

  if (fabs(t1 - t2) < EPSILON) {
    if (dx1 * dx2 < 0 || dy1 * dy2 < 0) {
      if (dx1*dx1 + dy1*dy1 >= dx2*dx2 + dy2*dy2 - EPSILON) {
        return CNEITHER;
      } else {
        return CW;
      }
    } else {
      return CCW;
    }
  } else if (t1 > t2) {
    return CCW;
  } else {
    return CW;
  }
}

bool point_in_poly(Point poly[], int n, Point p)
{
  int i, j, c = 0;

  /* first check to see if point is one of the vertices */
  for (i = 0; i < n; i++) {
    if (fabs(p.x - poly[i].x) < EPSILON && fabs(p.y - poly[i].y) < EPSILON) {
      return BOUNDARY;
    }
  }

  /* now check if it's on the boundary */
  for (i = 0; i < n-1; i++) {
    if (ccw(poly[i], poly[i+1], p) == CNEITHER) {
      return BOUNDARY;
    }
  }
  if (ccw(poly[n-1], poly[0], p) == CNEITHER) {
    return BOUNDARY;
  }

  /* finally check if it's inside */
  for (i = 0, j = n-1; i < n; j = i++) {
    if (((poly[i].y <= p.y && p.y < poly[j].y) ||
        (poly[j].y <= p.y && p.y < poly[i].y)) &&
        (p.x < (poly[j].x - poly[i].x) * (p.y - poly[i].y)
         / (poly[j].y - poly[i].y) + poly[i].x))
      c = !c;
  }
  return c;
}

double area(Point triangle[])
{
  return fabs(0.5*(
	      (triangle[2].y - triangle[0].y)*(triangle[1].x - triangle[0].x)
	      - (triangle[1].y - triangle[0].y)*(triangle[2].x - triangle[0].x)));
}

int main(void)
{
  int N;
  Point p[15];

  while (cin >> N && N > 0) {
    for (int i = 0; i < N; i++) {
      char c;
      cin >> c >> p[i].x >> p[i].y;
    }

    Point triangle[3];
    double best_area;
    string best_tri = "   ";
    for (int i = 0; i < N; i++) {
      triangle[0] = p[i];
      for (int j = i+1; j < N; j++) {
	triangle[1] = p[j];
	for (int k = j+1; k < N; k++) {
	  triangle[2] = p[k];
	  double A = area(triangle);
	  if (best_tri != "   " && A <= best_area) continue;
	  int m;
	  for (m = 0; m < N; m++) {
	    if (m == i || m == j || m == k) continue;
	    if (point_in_poly(triangle, 3, p[m])) break;
	  }
	  if (m >= N) {
	    best_area = A;
	    best_tri[0] = i + 'A';
	    best_tri[1] = j + 'A';
	    best_tri[2] = k + 'A';
	  }
	}
      }
    }
    
    cout << best_tri << endl;

  }

  return 0;
}
