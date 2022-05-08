#include <bits/stdc++.h>

using namespace std;

void solve()
{
  int x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;

  long long dx = abs(x1-x2), dy = abs(y1-y2);
  if (dx < dy) swap(dx, dy);

  // number of R == dx
  // number of U/D: U - D == dy, U + D == dx or U + D == dx-1 depending on parity of dx+dy
  //
  // in the first case, U = (dx+dy)/2 and D = (dx-dy)/2 >= 0 because dx >= dy
  // in the second case, U = (dx-1 + dy)/2 and D = (dx-1-dy)/2 >= 0, because dx > 0 if dx + dy is
  //   odd
  // Note that this works even if dx == 0, because dy will also be 0 and we are in the even case.
  
  long long ans = dx;
  if ((dx + dy) % 2 == 0) {
    ans += dx;
  } else {
    ans += dx-1;
  }
  cout << ans << endl;
}

int main()
{
  int T;
  cin >> T;

  while (T--)
    solve();

  return 0;
}
