#include <bits/stdc++.h>

using namespace std;

struct Loc {
  int x, y;

  void read()
  {
    cin >> x >> y;
  }
};

int sqdist(Loc a, Loc b)
{
  int dx = a.x - b.x, dy = a.y - b.y;
  return dx*dx + dy*dy;
}

int n, m, p;
Loc judge[1000], tar[1000], feather[1000];

typedef tuple<int,int,int> ti3;

ti3 dist[1000000];
double match(Loc A[], int nA, Loc B[], int nB)
{
  int n_dist = 0;
  for (int i = 0; i < nA; i++) {
    for (int j = 0; j < nB; j++) {
      dist[n_dist++] = ti3(sqdist(A[i], B[j]), i, j);
    }
  }
  sort(dist, dist+n_dist);

  double ans = 0.0;
  bool usedA[1000] = {false}, usedB[1000] = {false};
  for (int i = 0; i < n_dist; i++) {
    auto [d, ai, bi] = dist[i];
    if (usedA[ai] || usedB[bi]) continue;
    ans += sqrt(d);
    usedA[ai] = usedB[bi] = true;
  }

  return ans;
}

int main()
{
  cin >> n >> m >> p;
  for (int i = 0; i < n; i++) {
    judge[i].read();
  }
  for (int i = 0; i < m; i++) {
    tar[i].read();
  }
  for (int i = 0; i < p; i++) {
    feather[i].read();
  }

  double ans1 = match(judge, n, tar, m);
  double ans2 = match(judge, n, feather, p);
  cout << fixed << setprecision(10) << ans1+ans2 << endl;

  return 0;
}
