#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-8;
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

enum Orientation {CCW, CW, CNEITHER};

//------------------------------------------------------------------------------
// Colinearity test
bool colinear(Point a, Point b, Point c) { return dEqual(cross(b-a,c-b),0); }

bool on_segment(Point p, Point a, Point b)
{
  return colinear(a, p, b) && min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x)
    && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

//------------------------------------------------------------------------------
// Orientation test  (When pts are colinear: ccw: a-b-c  cw: c-a-b  neither: a-c-b)
Orientation ccw(Point a, Point b, Point c) { // 
  Point d1 = b - a, d2 = c - b;
  if (dEqual(cross(d1,d2),0))
    if (d1.x * d2.x < 0 || d1.y * d2.y < 0) 
      return (d1 * d1 >= d2*d2 - EPS) ? CNEITHER : CW;
    else return CCW;
  else return (cross(d1,d2) > 0) ? CCW : CW;
}

//------------------------------------------------------------------------------
// Signed Area of Polygon
double area_polygon(Point p[], int n) {
  double sum = 0.0;
  for (int i = 0; i < n; i++)  sum += cross(p[i],p[(i+1)%n]);
  return sum/2.0;
}

//------------------------------------------------------------------------------
// Point in Polygon Test
const bool BOUNDARY = true;  // is boundary in polygon?
bool point_in_poly(Point poly[], int n, Point p) {
  int i, j, c = 0;
  for (i = 0; i < n; i++) 
    if (poly[i] == p || ccw(poly[i], poly[(i+1)%n], p) == CNEITHER) return BOUNDARY;
  
  for (i = 0, j = n-1; i < n; j = i++) 
    if (((poly[i].y <= p.y && p.y < poly[j].y) ||
         (poly[j].y <= p.y && p.y < poly[i].y)) &&
        (p.x < (poly[j].x - poly[i].x) * (p.y - poly[i].y) /
         (poly[j].y - poly[i].y) + poly[i].x))
      c = !c;
  return c;
}

//------------------------------------------------------------------------------
// Intersection of lines (line segment or infinite line)
//      (1 == 1 intersection pt, 0 == no intersection pts, -1 == infinitely many
int intersect_line(Point a, Point b, Point c, Point d, Point &p,bool segment) {
  double num1 = cross(d-c,a-c), num2 = cross(b-a,a-c),denom = cross(b-a,d-c);
  if (!dEqual(denom, 0)) {
    double r = num1 / denom, s = num2 / denom;
    if (!segment || (0-EPS <= r && r <= 1+EPS && 0-EPS <= s && s <= 1+EPS)) {
      p = a + r*(b-a); return 1;
    } else return 0;
  }
  if(!segment) return dEqual(num1,0) ? -1 : 0; // For infinite lines, this is the end
  if (!dEqual(num1, 0)) return 0;
  if(b < a) swap(a,b); if(d < c) swap(c,d);
  if (a.x == b.x) {
    if (b.y == c.y) { p = b; return 1; }
    if (a.y == d.y) { p = a; return 1; }
    return (b.y < c.y || d.y < a.y) ? 0 : -1;
  } else if (b.x == c.x) { p = b; return 1; }
  else if (a.x == d.x) { p = a; return 1; }
  else if (b.x < c.x || d.x < a.x) return 0;
  return -1;
}

const int MAX_N = 100000;
Point polygon[MAX_N];

int main()
{
  int N;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> polygon[i].x >> polygon[i].y;
  }

  Point bug, signal;
  cin >> bug.x >> bug.y;
  cin >> signal.x >> signal.y;

  bool inside = false, outside = false;
  for (int i = 0; i < N; i++) {
    Point p = polygon[i], q = polygon[(i+1)%N];
    Point bug2 = bug;

    if (!on_segment(bug2, p, q)) continue;
    if (bug2 == p || bug2 == q) {
      bug2 = 0.5 * (p + q);
    }

    if (colinear(p, bug2, signal)) {
      inside = outside = true;
      continue;
    }
    
    double mult = 1.0;
    Point signal2, dummy;
    while (true) {
      signal2 = bug2 + mult * (signal - bug2);
      bool intersect = false;
      for (int j = 0; j < N && !intersect; j++) {
	if (i == j) continue;
	intersect |= (intersect_line(polygon[j], polygon[(j+1)%N],
				     bug2, signal2, dummy, true) != 0);
      }
      if (!intersect) break;
      mult *= 0.5;
    }

    if (point_in_poly(polygon, N, signal2)) {
      inside = true;
    } else {
      outside = true;
    }
  }

  if (inside == outside) {
    cout << "?" << endl;
  } else if (inside) {
    cout << "inside" << endl;
  } else {
    cout << "outside" << endl;
  }
  
  return 0;
}
