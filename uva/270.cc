/* @JUDGE_ID: 1102NT 270 C++ "" */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct Point {
  long long x, y;
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

void solve(Point *points, int n)
{
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
  cout << best+1 << endl;
}

int main(void)
{
  int cases;
  string line;
  Point points[700];
  int n;
  
  cin >> cases;
  cin.ignore();
  getline(cin, line);

  while (cases-- > 0) {
    n = 0;

    getline(cin, line);
    while (line != "") {
      istringstream ss(line);
      long long x, y;

      ss >> x >> y;
      points[n].x = x;
      points[n++].y = y;
      getline(cin, line);
    }

    solve(points, n);

    if (cases) {
      cout << endl;
    }
  }

  return 0;
}
