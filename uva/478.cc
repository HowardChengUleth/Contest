#include <iostream>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

class Shape {
public:
  virtual bool inside(double x, double y) = 0;
};

class Rectangle : public Shape {
protected:
  double x1, x2, y1, y2;
public:
  Rectangle(double ulx, double uly, double lrx, double lry)
    : x1(ulx), x2(lrx), y1(lry), y2(uly)
  {
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);
  }

  bool inside(double x, double y)
  {
    return (x1 < x && x < x2 && y1 < y && y < y2);
  }
};

class Circle : public Shape {
protected:
  double cx, cy, r;
public:
  Circle(double x, double y, double rad)
    : cx(x), cy(y), r(rad)
  {
  }

  bool inside(double x, double y)
  {
    return (x-cx)*(x-cx) + (y-cy)*(y-cy) < r*r;
  }
};

/* how close to call equal */
const double EPSILON = 1E-8;

/* what should be returned on the boundary? */
const bool BOUNDARY = false;

struct Point {
  double x, y;
  
  Point() : x(0.0), y(0.0) { }
  Point(double xx, double yy) : x(xx), y(yy) { }
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

  
class Triangle : public Shape {
protected:
  Point p[3];
public:
  Triangle(double x1, double y1, double x2, double y2, double x3, double y3)
  {
    p[0] = Point(x1,y1);
    p[1] = Point(x2,y2);
    p[2] = Point(x3,y3);
  }
  
  bool inside(double x, double y)
  {
    return point_in_poly(p, 3, Point(x,y));
  }
};



int main(void)
{
  Shape *figs[10];
  int num_figs = 0;

  char c;

  while (cin >> c && c != '*') {
    if (c == 'r') {
      double ulx, uly, lrx, lry;
      cin >> ulx >> uly >> lrx >> lry;
      figs[num_figs++] = new Rectangle(ulx, uly, lrx, lry);
    } else if (c == 'c') {
      double x, y, rad;
      cin >> x >> y >> rad;
      figs[num_figs++] = new Circle(x, y, rad);
    } else {
      double x1, y1, x2, y2, x3, y3;
      cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
      figs[num_figs++] = new Triangle(x1, y1, x2, y2, x3, y3);
    }
  }

  double x, y;
  int point_num = 0;
  while (cin >> x >> y && !(x == 9999.9 && y == 9999.9)) {
    point_num++;
    bool found = false;
    for (int i = 0; i < num_figs; i++) {
      if (figs[i]->inside(x, y)) {
	cout << "Point " << point_num << " is contained in figure "
	     << i+1 << endl;
	found = true;
      }
    }
    if (!found) {
      cout << "Point " << point_num << " is not contained in any figure"
	   << endl;
    }
  }

  return 0;
}
