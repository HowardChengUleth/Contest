#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

int main()
{
  int n, k;
  cin >> n >> k;

  vector<pii> song;
  for (int i = 0; i < n; i++) {
    int t, b;
    cin >> t >> b;
    song.emplace_back(b, t);
  }
  sort(song.rbegin(), song.rend());

  ll total = 0, ans = 0;
  multiset<int> len;
  for (auto p : song) {
    len.insert(p.second);
    total += p.second;
    if (len.size() > k) {
      int t = *begin(len);
      total -= t;
      len.erase(begin(len));
    }
    ans = max(ans, total * p.first);
  }
  cout << ans << endl;
  
  return 0;
}
