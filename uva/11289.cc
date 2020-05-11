#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Point
{
  double x, y, z;

  void read()
  {
    cin >> x >> y >> z;
  }

  double sqnorm() const
  {
    return x*x + y*y + z*z;
  }

  double dot(const Point &p) const
  {
    return x*p.x + y*p.y + z*p.z;
  }
};

Point operator*(double s, const Point &p)
{
  Point q = p;
  q.x *= s;
  q.y *= s;
  q.z *= s;
  return q;
}

Point operator+(const Point &a, const Point &b)
{
  Point c = a;
  c.x += b.x;
  c.y += b.y;
  c.z += b.z;
  return c;
}

Point p[200];
int n;
int y[200];          // +1 = empire, -1 = alliance

int classify(const Point &x, const Point &w, double b)
{
  return (w.dot(x) + b > 0) ? 1 : -1;
}

void perceptron(Point &w, double &b)
{
  // initial guess
  w.x = w.y = w.z = 0;
  b = 0;

  double R2 = 0;
  for (int i = 0; i < n; i++) {
    R2 = max(R2, p[i].sqnorm());
  }

  bool done = false;
  while (!done) {
    done = true;
    for (int i = 0; i < n; i++) {
      if (y[i] != classify(p[i], w, b)) {
	w = w + 0.5 * y[i] * p[i];
	b = b + 0.5 * y[i] * R2;
	done = false;
      }
    }
  }
}

bool solve()
{
  int n1, n2;
  cin >> n1;
  if (n1 == -1) return false;

  for (int i = 0; i < n1; i++) {
    p[i].read();
    y[i] = -1;
  }
  cin >> n2;
  for (int i = 0; i < n2; i++) {
    p[i+n1].read();
    y[i+n1] = 1;
  }
  n = n1+n2;

  Point w;
  double b;
  perceptron(w, b);
  cout << fixed << setprecision(6) << w.x << ' ' << w.y << ' '
       << w.z << ' ' << b << endl;

  return true;
}

int main()
{
  while (solve())
    ;
  return 0;
}
