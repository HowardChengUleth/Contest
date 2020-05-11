#include <iostream>
#include <cmath>

using namespace std;

const double EPS = 1e-8;

struct Point
{
  double x, y, z;

  Point(double xx = 0, double yy = 0, double zz = 0)
    : x(xx), y(yy), z(zz) { }
};

istream &operator>>(istream &is, Point &p)
{
  return is >> p.x >> p.y >> p.z;
}

Point operator-(Point a, Point b)
{
  Point c;
  c.x = a.x - b.x;
  c.y = a.y - b.y;
  c.z = a.z - b.z;
  return c;
}

double dot(Point a, Point b)
{
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

double norm(Point a)
{
  return sqrt(dot(a,a));
}

bool cansee(Point sat, Point dep)
{
  Point u = dep - sat, v = Point(0,0,0) - sat;

  // project
  double coeff = dot(u, v) / dot(u, u);

  if (coeff < 0 || coeff > 1) {
    // projection out of line segment, and both end points
    // are outside of sphere
    return true;
  }

  double dist = sqrt(pow(norm(v), 2) -
		     pow(coeff*norm(u), 2));
  return dist >= 40000-EPS;
  
}

bool solve()
{
  int k, m;
  cin >> k >> m;
  if (!k && !m) {
    return false;
  }

  Point sat[100], dep[100];

  for (int i = 0; i < k; i++) {
    cin >> sat[i];
  }
  for (int i = 0; i < m; i++) {
    cin >> dep[i];
  }

  int hit = 0;
  for (int i = 0; i < m; i++) {
    bool found = false;
    for (int j = 0; !found && j < k; j++) {
      found = cansee(sat[j], dep[i]);
    }
    if (found) {
      hit++;
    }
  }

  cout << hit << endl;

  return true;
}

int main()
{
  while (solve())
    ;
  
  return 0;
}
