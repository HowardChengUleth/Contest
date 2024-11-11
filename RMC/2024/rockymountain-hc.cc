#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
bool dEqual(ll x, ll y) { return x == y; }

struct Point {
  ll x, y;
  bool operator==(const Point &p) const { return dEqual(x, p.x) && dEqual(y, p.y); }
  bool operator<(const Point &p) const { return y < p.y || (y == p.y && x < p.x); }
};

Point operator-(Point p,Point q){ p.x -= q.x; p.y -= q.y; return p; }
Point operator+(Point p,Point q){ p.x += q.x; p.y += q.y; return p; }
Point operator*(ll r,Point p){ p.x *= r; p.y *= r; return p; }
ll operator*(Point p,Point q){ return p.x*q.x + p.y*q.y; }
double len(Point p){ return sqrt(p*p); }
ll cross(Point p,Point q){ return p.x*q.y - q.x*p.y; }
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
      return (d1 * d1 >= d2 * d2) ? CNEITHER : CW;
    else return CCW;
  else return (cross(d1,d2) > 0) ? CCW : CW;
}

// find leftmost point that works
Point find_left(const vector<Point> &p, int peak_i)
{
  assert(peak_i > 0);
  int best = peak_i - 1;   // this always works
  int can_see = best;
  for (int i = best-1; i >= 0; i--) {
    if (colinear(p[peak_i], p[can_see], p[i]) ||
	ccw(p[peak_i], p[can_see], p[i]) == CW) {
      can_see = i;
      if (p[i].y <= p[best].y) {
	best = i;
      }
    }
  }
  return p[best];
}

ostream &operator<<(ostream &os, Point p)
{
  return os << p.x << ' ' << p.y;
}

int main()
{
  int N;
  cin >> N;

  vector<Point> p(N);
  int peak_i = 0;
  for (int i = 0; i < N; i++) {
    cin >> p[i].x >> p[i].y;
    if (p[i].y > p[peak_i].y) {
      peak_i = i;
    }
  }

  Point left = find_left(p, peak_i);
  reverse(begin(p), end(p));
  peak_i = N - 1 - peak_i;
  for (int i = 0; i < N; i++) {
    p[i].x = 2*p[peak_i].x - p[i].x;
  }
  Point right = find_left(p, peak_i);
  right.x = 2*p[peak_i].x - right.x;

  cout << left << endl;
  cout << right << endl;

  return 0;
}
