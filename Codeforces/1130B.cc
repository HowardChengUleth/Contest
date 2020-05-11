#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n;
vector<int> pos[100000];

typedef pair<int,int> pii;
map<pii, ll> memo;

ll f(pii p, int k)
{
  if (k == n) return 0;
  if (memo.find(p) != memo.end()) {
    return memo[p];
  }

  pii nextp[2] = {{pos[k][0], pos[k][1]}, {pos[k][1], pos[k][0]}};

  ll ans = 2*n*n;
  for (int i = 0; i < 2; i++) {
    ll t = abs(nextp[i].first - p.first) + abs(nextp[i].second - p.second);
    t += f(nextp[i], k+1);
    ans = min(ans, t);
  }

  return memo[p] = ans;
}

int main()
{
  cin >> n;

  for (int i = 0; i < 2*n; i++) {
    int x;
    cin >> x;
    pos[x-1].push_back(i);
  }

  ll ans = min(f(pii(pos[0][0], pos[0][1]), 1),
	       f(pii(pos[0][1], pos[0][0]), 1));
  cout << ans + pos[0][0] + pos[0][1] << endl;
  return 0;
}
