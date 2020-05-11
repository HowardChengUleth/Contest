#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

struct Point {
  int x, y;
  
  Point(int xx = 0, int yy = 0) : x(xx), y(yy) { }

  Point &operator-=(const Point &p)
  {
    x -= p.x;
    y -= p.y;
    return *this;
  }

  bool operator==(const Point &p) const
  {
    return x == p.x && y == p.y;
  }

  int dot(const Point &p) const
  {
    return x*p.x + y*p.y;
  }

  int length_sq() const
  {
    return x*x + y*y;
  }

  double length() const
  {
    return sqrt(length_sq());
  }

  int dist_sq(const Point &p) const
  {
    Point temp(*this);
    temp -= p;
    return p.length_sq();
  }
    
};



/* counterclockwise, clockwise, or undefined */
enum {CCW, CW, CNEITHER};

int ccw(Point a, Point b, Point c)
{
  int dx1 = b.x - a.x;
  int dx2 = c.x - b.x;
  int dy1 = b.y - a.y;
  int dy2 = c.y - b.y;
  int t1 = dy2 * dx1;
  int t2 = dy1 * dx2;

  if (t1 == t2) {
    if (dx1 * dx2 < 0 || dy1 * dy2 < 0) {
      if (dx1*dx1 + dy1*dy1 >= dx2*dx2 + dy2*dy2) {
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

const double pi = acos(-1.0);

ostream &operator<<(ostream &os, const Point &p)
{
  return os << "(" << p.x << ", " << p.y << ")";
}

double proportion(int n, const Point polygon[], const Point &p)
{
  // see if it is on the boundary
  for (int i = 0; i < n; i++) {
    int next = (i+1) % n;
    if (ccw(polygon[i], polygon[next], p) == CNEITHER) {
      return 0.5;
    }
  }

  // now see if it's inside
  bool inside = false;
  for (int i = 0, j = n-1; i < n; j = i++) {
    if (((polygon[i].y <= p.y && p.y < polygon[j].y) ||
	 (polygon[j].y <= p.y && p.y < polygon[i].y)) &&
        (p.x < (polygon[j].x - polygon[i].x) * (p.y - polygon[i].y)
         / (polygon[j].y - polygon[i].y) + polygon[i].x))
      inside = !inside;
  }

  if (inside) {
    // now we want to make sure the circle is completely within the 
    // polygon

    // first, check that the end points of each edge is far enough
    // from the circle
    for (int i = 0; i < n; i++) {
      if (4*p.dist_sq(polygon[i]) < 1) {
	return 0.0;
      }
    }

    // now project the point on each edge
    for (int i = 0; i < n; i++) {
      int next = (i+1) % n;

      Point edge = polygon[next];
      edge -= polygon[i];

      Point pvec = p;
      pvec -= polygon[i];

      int proj = pvec.dot(edge);
      if (!(0 <= proj && proj <= edge.length_sq())) {
	// the projection falls out of the line, must be completely inside
	continue;
      }

      if (4*(edge.length_sq() * pvec.length_sq() - proj*proj) < 
	  edge.length_sq()) {
	// not completely inside
	return 0.0;
      }
    }

    // must be completely inside
    return 1.0;
  }

  return 0.0;
}

double solve(int n, Point polygon[])
{
  // make it counterclockwise
  reverse(polygon, polygon+n);

  // sum of the interior angles for an n-gon is known
  double area = (n-2)/2.0 * pi * 0.5 * 0.5;

  int min_x, min_y, max_x, max_y;
  max_x = min_x = polygon[0].x;
  max_y = min_y = polygon[0].y;
  for (int i = 1; i < n; i++) {
    max_x = max(max_x, polygon[i].x);
    max_y = max(max_y, polygon[i].y);
    min_x = min(min_x, polygon[i].x);
    min_y = min(min_y, polygon[i].y);
  }

  for (int x = min_x; x <= max_x; x++) {
    for (int y = min_y; y <= max_y; y++) {
      if (find(polygon, polygon+n, Point(x,y)) == polygon+n) {
	area += proportion(n, polygon, Point(x,y)) * pi * 0.5 * 0.5;
      }
    }
  }
  return area;
}

istream &operator>>(istream &is, Point &p)
{
  return is >> p.x >> p.y;
}

int read_polygon(Point polygon[])
{
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> polygon[i];
  }
  assert(n == 0 || (3 <= n && n <= 100));
  return n;
}

int main(void)
{
  int shape_no = 1;
  Point polygon[100];
  int n;

  while ((n = read_polygon(polygon)) > 0) {
    continue;
    cout << "Shape " << shape_no++ << endl;
    cout << "Insulating area = " << fixed << setprecision(3) 
	 << solve(n, polygon) << " cm^2" << endl;
  }

  return 0;
}
