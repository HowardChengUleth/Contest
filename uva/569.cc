#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstdio>

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
// Convex hull: Contains co-linear points. To remove colinear points:
//   Change ("< -EPS" and "> EPS") to ("< EPS" and "> -EPS")
int convex_hull(Point P[], int n, Point hull[]){
  sort(P,P+n); n = unique(P,P+n) - P;  vector<Point> L,U;
  if(n <= 2) { copy(P,P+n,hull); return n; }
  for(int i=0;i<n;i++){
    while(L.size()>1 && cross(P[i]-L.back(),L[L.size()-2]-P[i]) < -EPS) L.pop_back();
    while(U.size()>1 && cross(P[i]-U.back(),U[U.size()-2]-P[i]) >  EPS) U.pop_back();
    L.push_back(P[i]); U.push_back(P[i]);
  }
  copy(L.begin(),L.end(),hull); copy(U.rbegin()+1,U.rend()-1,hull+L.size());
  return L.size()+U.size()-2;
}

//------------------------------------------------------------------------------
// Point in Polygon Test
const bool BOUNDARY = true;  // is boundary in polygon?
bool point_in_poly(Point poly[], int n, Point p) {
  int i, j, c = 0;
  for (i = 0; i < n; i++) 
    if (poly[i] == p ||	ccw(poly[i], poly[(i+1)%n], p) == CNEITHER) return BOUNDARY;
  
  for (i = 0, j = n-1; i < n; j = i++) 
    if (((poly[i].y <= p.y && p.y < poly[j].y) ||
	 (poly[j].y <= p.y && p.y < poly[i].y)) &&
        (p.x < (poly[j].x - poly[i].x) * (p.y - poly[i].y) /
	 (poly[j].y - poly[i].y) + poly[i].x))
      c = !c;
  return c;
}

//------------------------------------------------------------------------------
// Computes the distance from "c" to the infinite line defined by "a" and "b" 
double dist_line(Point a, Point b, Point c) { return fabs(cross(b-a,a-c)/len(b-a)); }

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

//------------------------------------------------------------------------------
// Intersect 2 circles: 3 -> infinity, or 0-2 intersection points
// Does not deal with radius of 0 (AKA points)
#define SQR(X) ((X) * (X))
struct Circle{ Point c; double r; };
int intersect_circle_circle(Circle c1,Circle c2,Point& ans1,Point& ans2) {
  if(c1.c == c2.c && dEqual(c1.r,c2.r)) return 3;
  double d = len(c1.c-c2.c);
  if(d > c1.r + c2.r + EPS || d < fabs(c1.r-c2.r) - EPS) return 0;
  double a = (SQR(c1.r) - SQR(c2.r) + SQR(d)) / (2*d);
  double h = sqrt(abs(SQR(c1.r) - SQR(a)));
  Point P = c1.c + a/d*(c2.c-c1.c);
  ans1 = P + h/d*inv(c2.c-c1.c); ans2 = P - h/d*inv(c2.c-c1.c);
  return dEqual(h,0) ? 1 : 2;
}

//------------------------------------------------------------------------------
// Intersect circle and line
// -> # of intersection points, in ans1 (and ans2)
struct Line{  Point a,b;  }; // distinct  points
int intersect_iline_circle(Line l,Circle c, Point& ans1, Point& ans2) {
  Point a = l.a - c.c, b = l.b - c.c; Point d = b - a;
  double dr = d*d, D = cross(a,b); double desc = SQR(c.r)*dr - SQR(D);
  if(dEqual(desc,0)){ ans1 = -D/dr*inv(d); return 1; }
  if(desc < 0) return 0; double sgn = (d.y < -EPS ? -1 : 1);
  Point f = (sgn*sqrt(desc)/dr)*d; d = c.c-D/dr*inv(d);
  ans1 = d + f; ans2 = d - f; return 2;
}

//------------------------------------------------------------------------------
// Circle From Points
bool circle3pt(Point a, Point b, Point c, Point &center, double &r) {
  double g = 2*cross((b-a),(c-b)); if (dEqual(g, 0)) return false; // colinear points
  double e = (b-a)*(b+a)/g, f = (c-a)*(c+a)/g;
  center = inv(f*(b-a) - e*(c-a));
  r = len(a-center);
  return true;
}


double dist(Point a, Point b)
{
  return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

Point post;

int toucher(Point a, Point b)
{
  Point p1, p2;
  double dx, dy;

  dx = b.x - a.x;
  dy = b.y - a.y;

  p1.x = a.x + dy;
  p1.y = a.y - dx;
  p2.x = a.x - dy;
  p2.y = a.y + dx;

  if (9 <= dist(a, post) && dist(a, post) <= 11) {
    return (ccw(p2, p1, post) == CCW || dist(post, p1) <= 1 || 
	    dist(post, p2) <= 1);
  }
  return 0;
}
int ringer(Point a, Point b)
{
  Point p1, p2;
  double dx, dy;

  dx = b.x - a.x;
  dy = b.y - a.y;

  p1.x = a.x + dy;
  p1.y = a.y - dx;
  p2.x = a.x - dy;
  p2.y = a.y + dx;
  
  return (!toucher(a, b) && dist(a, post) < 10 && 
	  (ccw(p2, p1, post) == CCW));
}


int swinger(Point a, Point b)
{
  return (dist(b, post) <= sqrt(2)*10+1);
}

int getscore(Point a, Point b)
{
  /* check for ringer */
  if (ringer(a, b)) {
    /*    printf("ringer\n"); */
    return 5;
  }

  if (toucher(a, b)) {
    /*    printf("toucher\n"); */
    return 2;
  }
  
  if (swinger(a, b)) {
    /*    printf("swinger\n"); */
    return 1;
  }
  /*  printf("none\n"); */
  return 0;
}

int main(void)
{
  Point a, b;
  int turn = 1;
  int score;
  int i;

  post.x = post.y = 0;

  printf("Turn Score\n");
  while (scanf("%lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y) == 4) {
    score = getscore(a, b);
    for (i = 0; i < 3; i++) {
      scanf("%lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y);
      score += getscore(a, b);
    }
    printf("%4d    %2d\n", turn++, score);
  }

  return 0;
}
