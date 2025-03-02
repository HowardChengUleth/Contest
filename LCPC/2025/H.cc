#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

int main()
{
  int n;
  cin >> n;

  vector<pii> v(n);
  for (int i = 0; i < n; i++) {
    cin >> v[i].first >> v[i].second;
  }

  set<int> S;
  int ans = 0;
  for (auto [r, f] : v) {
    int h = r + f;
    if (S.count(h) == 0) {
      ans++;
      S.insert(h);
    }
  }

  cout << ans << endl;

  return 0;
}
