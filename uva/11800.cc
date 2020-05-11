#include <iostream>
#include <algorithm>

using namespace std;

/*
 * Line Intersection
 *
 * Author: Howard Cheng
 * Reference:
 *   CLRS, "Introduction to Algorithms", 2nd edition, pages 936-939.
 *
 * Given two lines specified by their endpoints (a1, a2) and (b1, b2),
 * returns true if they intersect, and false otherwise.  The intersection
 * point is not known.
 *
 */

#include <iostream>
#include <cmath>

using namespace std;

struct Point {
  int x, y;
};

bool operator<(const Point &p1, const Point &p2)
{
  return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

int direction(Point p1, Point p2, Point p3)
{
  int x1 = p3.x - p1.x;
  int y1 = p3.y - p1.y;
  int x2 = p2.x - p1.x;
  int y2 = p2.y - p1.y;
  return x1*y2 - x2*y1;
}

int on_segment(Point p1, Point p2, Point p3)
{
  return ((p1.x <= p3.x && p3.x <= p2.x) || (p2.x <= p3.x && p3.x <= p1.x)) &&
    ((p1.y <= p3.y && p3.y <= p2.y) || (p2.y <= p3.y && p3.y <= p1.y));
}

int intersect(Point a1, Point a2, Point b1, Point b2)
{
  int d1 = direction(b1, b2, a1);
  int d2 = direction(b1, b2, a2);
  int d3 = direction(a1, a2, b1);
  int d4 = direction(a1, a2, b2);

  if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
      ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
    return 1;
  } else {
    return (d1 == 0 && on_segment(b1, b2, a1)) ||
      (d2 == 0 && on_segment(b1, b2, a2)) ||
      (d3 == 0 && on_segment(a1, a2, b1)) ||
      (d4 == 0 && on_segment(a1, a2, b2));
  }
}

bool selfIntersect(Point P[])
{
  for (int i = 0; i < 4; i++) {
    if (intersect(P[i], P[(i+1)%4], P[(i+2)%4], P[(i+3)%4])) {
      return true;
    }
  }
  return false;
}

#define SQR(x) ((x)*(x))

int sqlen(const Point &p1, const Point &p2)
{
  return SQR(p1.x - p2.x) + SQR(p1.y - p2.y);
}

ostream &operator<<(ostream &os, const Point &p)
{
  os << "(" << p.x << ", " << p.y << ")";
  return os;
}

int dot(const Point &p1, const Point &p2, const Point &q1, const Point &q2)
{
  int dx1 = p2.x - p1.x;
  int dy1 = p2.y - p1.y;
  int dx2 = q2.x - q1.x;
  int dy2 = q2.y - q1.y;
  return dx1*dx2 + dy1*dy2;
}

bool isSquare(Point P[])
{
  sort(P, P+4);
  do {
    if (selfIntersect(P)) continue;
    int len = sqlen(P[0], P[1]);
    if (len != sqlen(P[1], P[2]) ||
	len != sqlen(P[2], P[3]) ||
	len != sqlen(P[3], P[0])) continue;
    bool good = true;
    for (int i = 0; good && i < 4; i++) {
      good &= (dot(P[i], P[(i+1)%4], P[i], P[(i+3)%4]) == 0);
    }
    if (good) return true;
  } while (next_permutation(P, P+4));
 
  return false;
}

bool isRect(Point P[])
{
  sort(P, P+4);
  do {
    if (selfIntersect(P)) continue;
    int len1 = sqlen(P[0], P[1]);
    int len2 = sqlen(P[1], P[2]);
    if (sqlen(P[2], P[3]) != len1 || sqlen(P[0],P[3]) != len2) continue;
    bool good = true;
    for (int i = 0; good && i < 4; i++) {
      good &= (dot(P[i], P[(i+1)%4], P[i], P[(i+3)%4]) == 0);
    }
    if (good) return true;
  } while (next_permutation(P, P+4));
 
  return false;
}

bool isRhombus(Point P[])
{
  sort(P, P+4);
  do {
    if (selfIntersect(P)) continue;
    int len = sqlen(P[0], P[1]);
    if (len != sqlen(P[1], P[2]) ||
	len != sqlen(P[2], P[3]) ||
	len != sqlen(P[3], P[0])) continue;
    bool good = true;
    for (int i = 0; good && i < 4; i++) {
      good &= (dot(P[i], P[(i+1)%4], P[i], P[(i+3)%4]) != 0);
    }
    if (good) return true;
  } while (next_permutation(P, P+4));
 
  return false;
}

bool isPara(Point P[])
{
  sort(P, P+4);
  do {
    if (selfIntersect(P)) continue;
    int len1 = sqlen(P[0], P[1]);
    int len2 = sqlen(P[1], P[2]);
    if (sqlen(P[2], P[3]) != len1 || sqlen(P[0],P[3]) != len2) continue;
    bool good = true;
    for (int i = 0; good && i < 4; i++) {
      good &= (dot(P[i], P[(i+1)%4], P[i], P[(i+3)%4]) != 0);
    }
    if (good) return true;
  } while (next_permutation(P, P+4));
 
  return false;
}

bool isTrap(Point P[])
{
  sort(P, P+4);
  do {
    if (selfIntersect(P)) continue;
    
    // check if opposite sides are parallel
    long long dp = dot(P[0], P[1], P[3], P[2]);
    dp = SQR(dp);
    if (dp != (long long)sqlen(P[0], P[1]) * sqlen(P[2], P[3])) continue;

    // check if the other two sides are not parallel
    dp = dot(P[1], P[2], P[0], P[3]);
    dp = SQR(dp);
    if (dp == (long long)sqlen(P[1], P[2]) * sqlen(P[0], P[3])) continue;
    return true;
  } while (next_permutation(P, P+4));
  return false;
}

void solve()
{
  Point P[4];
  for (int i = 0; i < 4; i++) {
    cin >> P[i].x >> P[i].y;
  }

  if (isSquare(P)) {
    cout << "Square" << endl;
  } else if (isRect(P)) {
    cout << "Rectangle" << endl;
  } else if (isRhombus(P)) {
    cout << "Rhombus" << endl;
  } else if (isPara(P)) {
    cout << "Parallelogram" << endl;
  } else if (isTrap(P)) {
    cout << "Trapezium" << endl;
  } else {
    cout << "Ordinary Quadrilateral" << endl;
  }
}

int main(void)
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": ";
    solve();
  }
  return 0;
}
