#include <bits/stdc++.h>

using namespace std;

vector<pair<double,double>> p;

double f(double x)
{
  double ans = 0.0;
  for (auto [px, py] : p) {
    ans = max(ans, hypot(x-px, py));
  }

  return ans;
}

bool solve()
{
  int n;
  cin >> n;
  if (!n) {
    return false;
  }

  p.resize(n);
  for (auto &[px, py] : p) {
    cin >> px >> py;
  }

  double lo = -1e6, hi = 1e6;
  while (hi - lo > 1e-6) {
    double width = hi-lo;
    double m1 = lo + width / 3;
    double m2 = lo + 2 * width / 3;

    double f1 = f(m1), f2 = f(m2);
    if (f1 > f2) {
      lo = m1;
    } else {
      hi = m2;
    }
  }

  cout << fixed << setprecision(12) << lo << ' ' << f(lo) << endl;

  
  return true;
}
    

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  while (solve())
    ;

  return 0;
}
