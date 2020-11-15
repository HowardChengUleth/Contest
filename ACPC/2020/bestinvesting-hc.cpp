#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

// how much balance do I need to withdraw w for each of the next yleft years
ld need(ld rate, ld yleft, int w)
{
  return (w * (pow(rate, yleft)-1) / (rate-1)) / pow(rate, yleft-1);
}

int main()
{
  int r, y, d, w;
  cin >> r >> y >> d >> w;

  ld ans = 0.0;
  ld bal = 0.0;
  ld rate = 1 + r/100.0;
  for (int yy = 0; yy <= y; yy++) {
    ld next_need = need(rate, y-yy, w);
    ld curr_change = next_need/rate - bal;

    if (curr_change > 0) {
      ld dep = min(ld(d), curr_change);
      bal += dep;
      ans -= dep;
    } else if (curr_change < 0) {
      ld with = min(bal, min(ld(w), -curr_change));
      bal -= with;
      ans += with;
    }
    bal *= rate;
  }

  cout << fixed << setprecision(10) << ans << endl;
  return 0;
}
