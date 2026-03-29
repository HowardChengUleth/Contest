//
// basically, we are asking to pick two cheapest linear independent vectors
//
// so just normalize each pair by dividing by gcd and making sure the first
// non-zero component is positive.  Then pick the cheapest two.
#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
typedef pair<int,pii> pipii;

int main()
{
  int N;
  cin >> N;

  vector<pipii> v(N);
  for (int i = 0; i < N; i++) {
    int c, x, y;
    cin >> c >> x >> y;

    int g = gcd(x, y);
    x /= g;
    y /= g;
    if (x < 0 || (x == 0 && y < 0)) {
      x *= -1;
      y *= -1;
    }
    v[i] = make_pair(c, make_pair(x, y));
  }
  sort(begin(v), end(v));

  set<pii> dirs;
  int ans = 0;
  for (int i = 0; i < N && dirs.size() < 2; i++) {
    if (dirs.count(v[i].second) > 0) continue;
    ans += v[i].first;
    dirs.insert(v[i].second);
  }

  if (dirs.size() == 2) {
    cout << ans << endl;
  } else {
    cout << "IMPOSSIBLE" << endl;
  }

  return 0;
}
