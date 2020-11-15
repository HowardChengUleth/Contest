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
