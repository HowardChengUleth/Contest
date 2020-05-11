/*
 * Orientation analysis
 *
 * Author: Howard Cheng
 * Reference:
 *   http://wilma.cs.brown.edu/courses/cs016/packet/node18.html
 *
 * Given three points a, b, c, it returns whether the path from a to b to c
 * is counterclockwise, clockwise, or undefined.
 *
 * Undefined is returned if the 3 points are colinear, and c is between
 * a and b.
 */

#include <iostream>
#include <cmath>

using namespace std;

#include <algorithm>

using namespace std;

typedef long long ll;

struct Point
{
  ll x, y;
};

/* counterclockwise, clockwise, or undefined */
enum Orientation {CCW, CW, CNEITHER};

Orientation ccw(Point a, Point b, Point c)
{
  ll dx1 = b.x - a.x;
  ll dx2 = c.x - b.x;
  ll dy1 = b.y - a.y;
  ll dy2 = c.y - b.y;
  ll t1 = dy2 * dx1;
  ll t2 = dy1 * dx2;

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

bool colinear(Point a, Point b, Point c)
{
  ll dx1 = b.x - a.x;
  ll dx2 = c.x - b.x;
  ll dy1 = b.y - a.y;
  ll dy2 = c.y - b.y;
  ll t1 = dy2 * dx1;
  ll t2 = dy1 * dx2;

  return t1 == t2;
}

bool operator<(const Point &p1, const Point &p2)
{
  return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

istream &operator>>(istream &is, Point &p)
{
  return is >> p.x >> p.y;
}

ostream &operator<<(ostream &os, const Point &p)
{
  return os << p.x << ' ' << p.y;
}

Point p[100000];
int num_p;

Point p_min, p_max;

bool cmp_angle(const Point &p1, const Point &p2)
{
  return (ccw(p_min, p1, p2) == CCW);
}

bool cmp_sort(const Point &p1, const Point &p2)
{
  if (colinear(p_min, p1, p_max) && colinear(p_min, p2, p_max)) {
    // p0 -> p1 and p0 -> p2 colinear with p0 -> p_max, farther one comes first
    ll dx1 = abs(p_min.x - p1.x);
    ll dx2 = abs(p_min.x - p2.x);
    ll dy1 = abs(p_min.y - p1.y);
    ll dy2 = abs(p_min.y - p2.y);
    return dx1 > dx2 || (dx1 == dx2 && dy1 > dy2);
  } else {
    return (ccw(p_min, p1, p2) == CCW);
  }
}

void do_case()
{
  int n;
  cin >> n;

  num_p = 0;
  for (int i = 0; i < n; i++) {
    char c;
    cin >> p[num_p] >> c;
    if (c == 'Y') {
      num_p++;
    }
  }

  // find the min
  int min_index = 0;
  for (int i = 1; i < num_p; i++) {
    if (p[i] < p[min_index]) {
      min_index = i;
    }
  }
  swap(p[0], p[min_index]);
  p_min = p[0];
  
  // find the maximum "angle" wrt to p[0] and positive x-axis
  int max_index = 1;
  for (int i = 2; i < num_p; i++) {
    if (cmp_angle(p[max_index], p[i])) {
      max_index = i;
    }
  }
  p_max = p[max_index];

  
  sort(p+1, p+num_p, cmp_sort);

  // output
  cout << num_p << endl;
  for (int i = 0; i < num_p; i++) {
    cout << p[i] << endl;
  }


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
