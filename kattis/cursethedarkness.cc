#include <bits/stdc++.h>

using namespace std;

void solve()
{
  double bx, by;
  cin >> bx >> by;

  int n;
  cin >> n;

  bool found = false;
  for (int i = 0; i < n; i++) {
    double cx, cy;
    cin >> cx >> cy;

    double dist2 = (bx-cx)*(bx-cx) + (by-cy)*(by-cy);
    found |= (dist2 <= 64);
  }

  if (found) {
    cout << "light a candle" << endl;
  } else {
    cout << "curse the darkness" << endl;
  }
}

int main()
{
  int m;
  cin >> m;

  while (m--) {
    solve();
  }

  return 0;
}
