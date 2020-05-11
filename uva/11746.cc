//
// we have P = p_i * d_i^2 for each i = 1, 2, 3.
//
// We set p_1 * d_1^2 = p2 * d_2^2 and
//        p_2 * d_2^2 = p3 * d_3^3,
//
// and solve for x and y.
//
// If p1 == p2, the first equation becomes an equation of a line.  Otherwise,
// it is an equation of a circle (after some manipulation).
// Similar for the second equation.
//
// So this is a (not-so-simple) matter of determining the intersection between
// two circles, a line and a circle, or two lines.
//

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <vector>

using namespace std;


/* how close to call equal */
const double EPSILON = 1E-6;

struct Point {
  double x, y;
  
  Point(double xx = 0, double yy = 0) : x(xx), y(yy) {}
  bool operator<(const Point &p) const {
    if (x != p.x) return x < p.x;
    return y < p.y;
  }
};

/* returns 1 if intersect at a point, 0 if not, -1 if the lines coincide */
int intersect_iline(Point a, Point b, Point c, Point d, Point &p)
{
  double r;
  double denom, num1, num2;

  assert((a.x != b.x || a.y != b.y) && (c.x != d.x || c.y != d.y));

  num1 = (a.y - c.y)*(d.x - c.x) - (a.x - c.x)*(d.y - c.y);
  num2 = (a.y - c.y)*(b.x - a.x) - (a.x - c.x)*(b.y - a.y);
  denom = (b.x - a.x)*(d.y - c.y) - (b.y - a.y)*(d.x - c.x);

  if (fabs(denom) >= EPSILON) {
    r = num1 / denom;
    p.x = a.x + r*(b.x - a.x);
    p.y = a.y + r*(b.y - a.y);
    return 1;
  } else {
    if (fabs(num1) >= EPSILON) {
      return 0;
    } else {
      return -1;
    }
  }
}



class Circle {
public:
  double x, y, rsq;

  Circle() { }
  Circle(double x1, double y1, double p1, double x2, double y2, double p2)
  {
    // let d_i = (x - x_i)^2 + (y - y_i)^2
    //
    // transform the equation p_1 * d_1 - p_2 * d_2 = 0 into the
    // form x^2 + ax + y^2 + by + c = 0.

    double a, b, c;

    a = (2*(p2*x2 - p1*x1))/(p1-p2);
    b = (2*(p2*y2 - p1*y1))/(p1-p2);
    c = (p1*x1*x1 - p2*x2*x2 + p1*y1*y1 - p2*y2*y2)/(p1-p2);

    // complete the squares to get the circle
    x = -a/2;
    y = -b/2;
    rsq = a*a/4 + b*b/4 - c;
  }
};

class Line {
public:
  Point p, q;      // two endpoints
  double a, b, c;  // ax+by+c = 0

  Line() { }
  Line(double x1, double y1, double p1, double x2, double y2, double p2)
  {
    assert(p1 == p2);

    // convert to form ax+by+c = 0
    a = 2*(p2*x2 - p1*x1);
    b = 2*(p2*y2 - p1*y1);
    c = p1*x1*x1 - p2*x2*x2 + p1*y1*y1 - p2*y2*y2;
    assert(fabs(a) > EPSILON || fabs(b) > EPSILON);

    if (fabs(a) <= EPSILON) {
      p.x = 0;
      q.x = 10;
      p.y = q.y = -c/b;
    } else if (fabs(b) <= EPSILON) {
      p.y = 0;
      q.y = 10;
      p.x = q.x = -c/a;
    } else {
      p.x = 0;
      q.x = 10;
      p.y = (-c - a*p.x)/b;
      q.y = (-c - a*q.x)/b;
    }
  }
};

void add(vector<Point> &sol, Point p)
{
  if (0 <= p.x && p.x <= 1000 && 0 <= p.y && p.y <= 1000) {
    sol.push_back(p);
  }
}

void intersect(vector<Point> &sol, Circle circle, Line line)
{
  if (fabs(line.a) > EPSILON) {
    // solve for x in a*x+b*y+c = 0, substitute into circle eqn and solve
    // for y
    double a, b, c;
    a = 1 + (line.b*line.b)/(line.a*line.a);
    b = (2 * line.b * circle.x)/line.a - 2 * circle.y + 
      2*line.b*line.c/(line.a*line.a);
    c = 2*line.c*circle.x/line.a + circle.x*circle.x +
      line.c*line.c/(line.a*line.a) + circle.y*circle.y - circle.rsq;

    double disc = b*b-4*a*c;
    assert(disc >= 0);
    double y1 = (-b + sqrt(disc)) / (2*a);
    double y2 = (-b - sqrt(disc)) / (2*a);
    double x;

    x = -(line.b * y1 + line.c)/line.a;
    add(sol, Point(x, y1));
    if (fabs(y1-y2) > EPSILON) {
      x = -(line.b * y2 + line.c)/line.a;
      add(sol, Point(x, y2));
    }
  } else {
    // a = 0
    double y = -line.c/line.b;
    double x_sq = circle.rsq - (y - circle.y)*(y - circle.y);
    assert(x_sq >= 0);
    double x1 = sqrt(x_sq) + circle.x;
    double x2 = -sqrt(x_sq) + circle.x;
    add(sol, Point(x1, y));
    if (fabs(x1 - x2) > EPSILON) {
      add(sol, Point(x2, y));
    }
  }
}

void intersect(vector<Point> &sol, Line a, Line b)
{
  Point c;
  int ret = intersect_iline(a.p, a.q, b.p, b.q, c);
  assert(ret == 1);
  add(sol, c);
}

void intersect(vector<Point> &sol, Circle a, Circle b)
{
  Line line;
  line.a = 2*(b.x - a.x);
  line.b = 2*(b.y - a.y);
  line.c = a.x*a.x - b.x*b.x + a.y*a.y - b.y*b.y + b.rsq - a.rsq;
  intersect(sol, a, line);
}

void do_case(void)
{
  int x1, x2, x3, y1, y2, y3, p1, p2, p3;
  
  cin >> x1 >> y1 >> p1;
  cin >> x2 >> y2 >> p2;
  cin >> x3 >> y3 >> p3;

  Circle circle[2];
  Line line[2];
  int num_circle = 0;
  int num_line = 0;
  if (p1 != p2) {
    circle[num_circle++] = Circle(x1, y1, p1, x2, y2, p2);
  } else {
    line[num_line++] = Line(x1, y1, p1, x2, y2, p2);
  }
  if (p2 != p3) {
    circle[num_circle++] = Circle(x2, y2, p2, x3, y3, p3);
  } else {
    line[num_line++] = Line(x2, y2, p2, x3, y3, p3);
  }


  vector<Point> sol;
  if (num_circle == 2) {
    intersect(sol, circle[0], circle[1]);
  } else if (num_circle == 1) {
    intersect(sol, circle[0], line[0]);
  } else {
    intersect(sol, line[0], line[1]);
  }
  sort(sol.begin(), sol.end());

  cout << sol.size();
  for (vector<Point>::const_iterator it = sol.begin(); it != sol.end(); ++it) {
    cout << ' ' << fixed << setprecision(2) << it->x << ' ' << it->y;
  }
  cout << endl;
}


int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    do_case();
  }
  return 0;
}
