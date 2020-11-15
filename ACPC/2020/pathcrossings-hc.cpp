// A brute force O(n^2) algorithm to compare all pairs of points is too slow,
// but you are told that there are not many pings in a time window.  So if
// you sort the pings by time, then for each ping you only have to look back
// at most 5 pings to see how many are close.  Other than that you just have
// to do the usual squared distance comparison instead of taking square
// roots to avoid rounding errors.

#include <bits/stdc++.h>

using namespace std;

struct Ping
{
  int p;
  int x, y, t;

  bool operator<(const Ping &p) const
  {
    return t < p.t;
  }
};

istream &operator>>(istream &is, Ping &p)
{
  return is >> p.p >> p.x >> p.y >> p.t;
}

Ping ping[200000];
int P, N;

int main()
{
  cin >> P >> N;
  for (int i = 0; i < N; i++) {
    cin >> ping[i];
  }
  sort(ping, ping+N);

  set<pair<int,int>> ans;
  for (int i = 0; i < N; i++) {
    for (int j = max(0,i-4); j < i; j++) {
      if (ping[i].p == ping[j].p) continue;
      if (ping[i].t - ping[j].t > 10) continue;
      int dx = ping[i].x - ping[j].x, dy = ping[i].y - ping[j].y;
      if (dx*dx + dy*dy <= 1000000) {
	ans.emplace(min(ping[i].p, ping[j].p),
		    max(ping[i].p, ping[j].p));
      }
    }
  }

  cout << ans.size() << endl;
  for (auto p : ans) {
    cout << p.first << ' ' << p.second << endl;
  }

  return 0;
}
