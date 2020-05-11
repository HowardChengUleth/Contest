#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double PI = acos(-1.0), EPS = 1e-8;

struct Vector {
  double x, y, z;

  Vector(double xx = 0, double yy = 0, double zz = 0) : x(xx), y(yy), z(zz) { }
  Vector(const Vector &p1, const Vector &p2)
    : x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z) { }
  Vector(const Vector &p1, const Vector &p2, double t)
    : x(p1.x + t*p2.x), y(p1.y + t*p2.y), z(p1.z + t*p2.z) { }
  double norm() const { return sqrt(x*x + y*y + z*z); }
  bool operator==(const Vector&p) const{
    return abs(x - p.x) < EPS && abs(y - p.y) < EPS && abs(z - p.z) < EPS;
  }
};

double dot(Vector p1, Vector p2) { return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z; }
double angle(Vector p1,Vector p2) {  return acos(dot(p1, p2)/p1.norm()/p2.norm()); }
Vector cross(Vector p1, Vector p2) {
  return Vector(p1.y*p2.z-p2.y*p1.z, p2.x*p1.z-p1.x*p2.z, p1.x*p2.y-p2.x*p1.y); }
Vector operator+(Vector p1,Vector p2){ return Vector(p1.x+p2.x,p1.y+p2.y,p1.z+p2.z); }
Vector operator-(Vector p1,Vector p2){ return Vector(p1.x-p2.x,p1.y-p2.y,p1.z-p2.z); }
Vector operator*(double c,Vector v){ return Vector(c*v.x, c*v.y, c*v.z); }

double dist_pt_to_pt(Vector p1,Vector p2) { return Vector(p1, p2).norm(); }

istream &operator>>(istream &is, Vector &v)
{
  return is >> v.x >> v.y >> v.z;
}

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

//------------------------------------------------------------------------------
// Signed Area of Polygon
double area_polygon(Point p[], int n) {
  double sum = 0.0;
  for (int i = 0; i < n; i++)  sum += cross(p[i],p[(i+1)%n]);
  return sum/2.0;
}

bool solve()
{
  int n;
  cin >> n;
  if (!n) return false;

  Vector v[1024];
  for (int i = 0; i < n; i++) {
    cin >> v[i];
  }

  // find two vectors in plane
  Vector v1(v[1], v[0]), v2(v[2], v[0]);

  // normal
  Vector normal = cross(v1, v2);

  // now find orthonormal basis in plane
  Vector e1 = cross(v1, normal), e2 = cross(e1, normal);
  e1 = 1.0/e1.norm() * e1;
  e2 = 1.0/e2.norm() * e2;

  // now project every point 
  Point p[1024];
  for (int i = 0; i < n; i++) {
    p[i].x = dot(v[i], e1);
    p[i].y = dot(v[i], e2);
  }

  cout << fixed << setprecision(3) << fabs(area_polygon(p, n)) << endl;
  
  return true;
}

int main()
{
  while (solve())
    ;

  return 0;
}
