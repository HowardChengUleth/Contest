#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct Point {
  long long x, y;
  bool operator<(const Point &p) const
  {
    return x < p.x || (x == p.x && y < p.y);
  }
  bool operator==(const Point &p) const
  {
    return x == p.x && y == p.y;
  }
};

struct Slope {
  long long dx, dy;

  void set(long long xx, long long yy) {
    dx = xx; 
    dy = yy; 
    if (dy < 0) {
      dx *= -1;
      dy *= -1;
    }
  }
  
  bool operator<(const Slope &b) const {
    return b.dx * dy < b.dy * dx;
  }

  bool operator==(const Slope &b) const {
    return b.dx * dy == b.dy * dx;
  }
};

istream &operator>>(istream &is, Point &p)
{
  int t;
  is >> p.x;
  is.ignore(1);
  p.x *= 100;
  is >> t;
  p.x += t;

  is >> p.y;
  is.ignore(1);
  p.y *= 100;
  is >> t;
  p.y += t;
  return is;
}

void solve(int n)
{
  Point points[100];

  for (int i = 0; i < n; i++) {
    cin >> points[i];
  }
  sort(points, points+n);
  n = unique(points, points+n) - points;
  if (n == 1) {
    cout << "a single gnu." << endl;
    return;
  }
  
  int best = 0;
  int nn;

  for (int i = 0; i < n; i++) {
    Slope slopes[700];
    nn = 0;
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      slopes[nn++].set(points[i].x - points[j].x, points[i].y - points[j].y);
    }
    sort(slopes, slopes+nn);

    int j, k;
    j = 0;
    while (j < nn) {
      for (k = j; k < nn && slopes[k] == slopes[j]; k++)
        ;
      if (best < k-j) {
        best = k-j;
      }
      j = k;
    }
  }

  cout << n << " gnus, out of which a maximum of " << best+1
       << " are aligned." << endl;
}

int main(void)
{
  int cases;
  cin >> cases;
  for (int i = 1; i <= cases; i++) {
    int N;
    cin >> N;
    cout << "Data set #" << i << " contains ";
    solve(N);
  }
  return 0;
}

