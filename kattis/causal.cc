#include <bits/stdc++.h>

using namespace std;

struct Point {
  int x, t;

  bool operator<(const Point &p) const
  {
    return x + t < p.x + p.t;;
  }
};

Point event[100000];

int n, m;

bool check(int t)
{
  int cause = 1;
  int last_x = event[0].x + event[0].t - t;

  for (int i = 1; i < n; i++) {
    if (event[i].x - event[i].t <= last_x - t) continue;
    cause++;
    last_x = event[i].x + event[i].t - t;
  }
  return cause <= m;
}

void solve()
{
  cin >> n >> m;

  int mint = INT_MAX;
  for (int i = 0; i < n; i++) {
    cin >> event[i].t >> event[i].x;
    mint = min(event[i].t, mint);
  }
  sort(event, event+n);

  int lo = -2000000, hi = mint;

  if (check(hi)) {
    cout << hi << endl;
    return;
  }

  while (hi - lo > 1) {
    int mid = lo + (hi-lo)/2;
    if (check(mid)) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  cout << lo << endl;
}

int main()
{
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cout << "Case " << i+1 << ": ";
    solve();
  }
  
  return 0;
}
