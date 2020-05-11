#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
  double x, y;
  
  Point(double xx = 0, double yy = 0)
    : x(xx), y(yy) {}

  double sqdist(const Point &p) const {
    double dx = x - p.x;
    double dy = y - p.y;
    return dx*dx + dy*dy;
  }

  double dist(const Point &p) const {
    return sqrt(sqdist(p));
  }
};

Point P[10000];

istream &operator>>(istream &is, Point &p) {
  return is >> p.x >> p.y;
}

bool sortx(int i, int j)
{
  return P[i].x < P[j].x;
}

bool sorty(int i, int j)
{
  return P[i].y < P[j].y;
}


double base_case(const int *X, int n)
{
  if (n <= 1) {
    return 0;
  }
  double sqdist = P[X[0]].sqdist(P[X[1]]);
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      if (P[X[i]].sqdist(P[X[j]]) < sqdist) {
	sqdist = P[X[i]].sqdist(P[X[j]]);
      }
    }
  }
  return sqdist;
}

double sqdist(double x1, double x2)
{
  return (x1-x2)*(x1-x2);
}

double closest_pair(const int *X, const int *Y, int n)
{
  if (n <= 3) {
    return base_case(X, n);
  }

  int YL[10000], YR[10000];
  const int *XL = X, *XR = X+n/2;

  bool left[10000];

  /* divide into two halves */
  fill(left, left+10000, false);
  for (int i = 0; i < n/2; i++) {
    left[X[i]] = true;
  }

  int YLi = 0, YRi = 0;
  for (int i = 0; i < n; i++) {
    if (left[Y[i]]) {
      YL[YLi++] = Y[i];
    } else {
      YR[YRi++] = Y[i];
    }
  }
  
  /* recurse */
  double sqdelta_l = closest_pair(XL, YL, n/2);
  double sqdelta_r = closest_pair(XR, YR, n-n/2);
  double sqdelta = min(sqdelta_l, sqdelta_r);

  /* combine */
  int Yprime[10000], Ypsize = 0;
  double bisect_x = P[X[n/2]].x;

  for (int i = 0; i < n; i++) {
    if (sqdist(P[Y[i]].x, bisect_x) < sqdelta) {
      Yprime[Ypsize++] = Y[i];
    }
  }

  for (int i = 0; i < Ypsize; i++) {
    for (int j = i+1; j < i+8 && j < Ypsize; j++) {
      if (P[Yprime[i]].sqdist(P[Yprime[j]]) < sqdelta) {
	sqdelta = P[Yprime[i]].sqdist(P[Yprime[j]]);
      }
    }
  }

  return sqdelta;
}

void solve(int n)
{
  int X[10000], Y[10000];

  for (int i = 0; i < n; i++) {
    X[i] = Y[i] = i;
  }

  sort(X, X+n, sortx);
  sort(Y, Y+n, sorty);

  double sqdist = closest_pair(X, Y, n);
  if (n > 1 && sqdist < 10000*10000) {
    cout << setprecision(4) << fixed << sqrt(sqdist) << endl;
  } else {
    cout << "INFINITY" << endl;
  }
}

bool do_case(void)
{
  int n;

  cin >> n;
  if (!n) {
    return false;
  }

  for (int i = 0; i < n; i++) {
    cin >> P[i];
  }

  solve(n);

  return true;
}

int main(void)
{
  while (do_case()) 
    ;

  return 0;
}
