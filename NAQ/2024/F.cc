#include <bits/stdc++.h>

using namespace std;

// You can do this with closed form formulas...but I will do binary search
// instead...
//
// To find the smallest x, find some x that is guaranteed to be too
// far outside (lo) and some x that is guaranteed inside (hi).  Then
// we repeatedly test mid = (lo+hi)/2 to see if it is inside and outside.
// We do this by asking: if we fix the line x = mid and look for the y
// minimizing D = d((x,y), (x1,y1)) + d((x,y), (x2,y2)).  If that D is <= a,
// then the line x = mid cuts the ellipse so it is still too large.
// Otherwise mid is too small.  Update lo or hi approriately and repeat.
//
// To find the y minimizing D, it turns out that this is a function that
// has one global minimum.  We can use ternary search to find that.  See
//
//   https://cp-algorithms.com/num_methods/ternary_search.html
//
//
// To find the largest x, smallest and largest y, we can just reflect the
// coordinates and find the smallest x, and reflect the result appropriately.


const double EPS = 1e-10;
bool dEqual(double x,double y) { return fabs(x-y) < EPS; }

struct Point {
  double x, y;
  bool operator==(const Point &p) const { return dEqual(x, p.x) && dEqual(y, p.y); }
  bool operator<(const Point &p) const { return y < p.y || (y == p.y && x < p.x); }
};

Point operator-(Point p,Point q){ p.x -= q.x; p.y -= q.y; return p; }
Point operator+(Point p,Point q){ p.x += q.x; p.y += q.y; return p; }
Point operator*(double r,Point p){ p.x *= r; p.y *= r; return p; }
double operator*(Point p,Point q){ return p.x*q.x + p.y*q.y; }
double len(Point p){ return sqrt(p*p); }
double cross(Point p,Point q){ return p.x*q.y - q.x*p.y; }
Point inv(Point p){ Point q = {-p.y,p.x}; return q; }

double best_dist_x(double x, Point p1, Point p2)
{
  double lo = -1e6, hi = 1e6;

  Point p;
  p.x = x;

  p.y = lo;
  double flo = len(p1-p) + len(p2-p);
  
  p.y = hi;
  double fhi = len(p1-p) + len(p2-p);

  while (hi - lo > EPS) {
    p.y = lo + (hi-lo)/3;
    double f1 = len(p1-p) + len(p2-p);

    p.y = lo + 2*(hi-lo)/3;
    double f2 = len(p1-p) + len(p2-p);

    if (f1 > f2) {
      lo = lo + (hi-lo)/3;
      flo = f1;
    } else {
      hi = lo + 2*(hi-lo)/3;
      fhi = f2;
    }
  }

  return flo;
}

double best_dist_y(double y, Point p1, Point p2)
{
  swap(p1.x, p1.y);
  swap(p2.x, p2.y);
  return best_dist_x(y, p1, p2);
}

double find_xlo(Point p1, Point p2, double a)
{
  if (p1.x > p2.x) {
    swap(p1, p2);
  }

  double lo = p1.x - 10*a;
  double hi = p1.x;

  while (hi - lo > EPS) {
    double mid = (lo + hi) / 2;
    double d = best_dist_x(mid, p1, p2);
    if (d <= a) {
      hi = mid;
    } else {
      lo = mid;
    }
  }
  return lo;
}

double find_xhi(Point p1, Point p2, double a)
{
  p1.x *= -1;
  p2.x *= -1;
  return -find_xlo(p1, p2, a);
}

double find_ylo(Point p1, Point p2, double a)
{
  swap(p1.x, p1.y);
  swap(p2.x, p2.y);
  return find_xlo(p1, p2, a);
}

double find_yhi(Point p1, Point p2, double a)
{
  p1.y *= -1;
  p2.y *= -1;
  return -find_ylo(p1, p2, a);
}




int main()
{
  Point p1, p2;
  double a;

  cin >> p1.x >> p1.y >> p2.x >> p2.y >> a;

  double x_lo = find_xlo(p1, p2, a);
  double y_lo = find_ylo(p1, p2, a);
  double x_hi = find_xhi(p1, p2, a);
  double y_hi = find_yhi(p1, p2, a);

  cout << setprecision(10) << fixed
       << x_lo << ' '
       << y_lo << ' '
       << x_hi << ' '
       << y_hi << endl;
  

  return 0;
}
