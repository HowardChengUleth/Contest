/* @JUDGE_ID: 1102NT 10585 C++ "" */

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

const double pi = atan(1.0)*4;

struct Point {
  double x, y;
  double r, theta;
  bool matched;

  Point() { 
    matched = false; 
  }

  void toPolar(const Point &center) {
    double xx = x - center.x, yy = y - center.y;
    r = sqrt(xx*xx + yy*yy);
    theta = atan2(yy, xx);
    if (theta == -pi) {
      theta = pi;
    }
  }

  friend istream &operator>>(istream &is, Point &p);
};

istream &operator>>(istream &is, Point &p)
{
  is >> p.x >> p.y;
  return is;
}

bool operator<(const Point &p, const Point &q)
{
  if (p.r != q.r) {
    return p.r < q.r;
  } else {
    return p.theta < q.theta;
  }
}

int main(void)
{
  const int max_n = 10000;
  int c;

  cin >> c;
  while (c-- > 0) {
    int n;
    Point point[max_n], center;

    center.x = center.y = 0.0;
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> point[i];
      center.x += point[i].x;
      center.y += point[i].y;
    }
    center.x /= n;
    center.y /= n;
    
    for (int i = 0; i < n; i++) {
      point[i].toPolar(center);
    }

    sort(point, point+n);

    bool ans = true;
    for (int i = 0; i < n && ans; i++) {
      if (point[i].r == 0 || point[i].matched) continue;
      ans = false;
      for (int j = i+1; j < n && !ans && fabs(point[i].r - point[j].r) < 1e-8; 
	   j++) {
	double t = point[i].theta+pi;
	if (t > pi) t -= 2*pi;
	if (fabs(point[j].theta - t) < 1e-8) {
	  point[j].matched = true;
	  ans = true;
	}
      }
    }
    cout << (ans ? "yes" : "no") << endl;
  }
  return 0;
}
