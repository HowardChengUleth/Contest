#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <utility>

using namespace std;

void solve()
{
  int n;
  cin >> n;

  pair<int,int> p[100];
  for (int i = 0; i < n; i++) {
    cin >> p[i].first >> p[i].second;
  }
  sort(p, p+n);

  int lo = 0, hi = 8848;
  double total = 0.0;
  for (int i = n-2; i >= 0; i--) {
    if (p[i].second <= p[i+1].second) continue;
    int ylo = max(lo, p[i+1].second);
    int yhi = min(hi, p[i].second);
    if (ylo >= yhi) continue;

    total += hypot(p[i].first-p[i+1].first, p[i].second-p[i+1].second) *
      (yhi - ylo) / (p[i].second - p[i+1].second);
    
    lo = max(yhi, lo);
  }
  cout << fixed << setprecision(2) << total << endl;
}

int main(void)
{
  int C;
  cin >> C;
  while (C--) {
    solve();
  }
  return 0;
}
