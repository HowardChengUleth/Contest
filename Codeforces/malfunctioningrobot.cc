#include <bits/stdc++.h>

using namespace std;

void solve()
{
  int x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;

  long long dx = abs(x1-x2), dy = abs(y1-y2);
  if (dx < dy) swap(dx, dy);

  if (dx == 0) {
    cout << 0 << endl;
    return;
  }
  
  // number of R == dx
  // number of U/D: U - D == dy, U + D == dx or U + D == dx-1 depending on parity of dx+dy
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
