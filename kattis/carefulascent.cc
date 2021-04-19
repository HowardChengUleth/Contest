#include <bits/stdc++.h>

using namespace std;

double x, y;
int n;

struct Shield
{
  double L, U, f;

  void read()
  {
    cin >> L >> U >> f;
  }
  
  bool operator<(const Shield &s) const {
    return L < s.L;
  }
};

Shield sh[100];

double getx(double v)
{
  double xx = 0.0, yy = 0.0;
  for (int i = 0; i < n; i++) {
    xx += v * (sh[i].L - yy);
    xx += v * sh[i].f * (sh[i].U - sh[i].L);
    yy = sh[i].U;
  }

  xx += v * (y - yy);
  return xx;
}

int main()
{
  cin >> x >> y;
  cin >> n;
  for (int i = 0; i < n; i++) {
    sh[i].read();
  }
  sort(sh, sh+n);

  double lo = -1.0, hi = 1.0;
  while (getx(lo) > x) {
    lo *= 2;
  }
  while (getx(hi) < x) {
    hi *= 2;
  }

  while (hi - lo > 1e-10) {
    double mid = (lo+hi)/2.0;
    double x2 = getx(mid);
    if (x2 < x) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  cout << fixed << setprecision(10) << lo << endl;
  
  return 0;
}
