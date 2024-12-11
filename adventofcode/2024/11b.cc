#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,int> pli;
map<pli, ll> memo;

ll expand(ll x, int steps)
{
  if (steps == 0) {
    return 1;
  }
  if (memo.find(pli(x, steps)) != memo.end()) {
    return memo[pli(x, steps)];
  }

  ll &ans = memo[pli(x, steps)];
  ans = 0;
  if (x == 0) {
    ans = expand(1, steps-1);
  } else {
    string s = to_string(x);
    if (s.length() % 2 == 0) {
      ans += expand(stoll(s.substr(0, s.length()/2)), steps-1);
      ans += expand(stoll(s.substr(s.length()/2)), steps-1);
    } else {
      ans = expand(x * 2024, steps-1);
    }
  }
  return ans;
}

int main()
{
  ll ans = 0;
  int c = 0;
  
  int x;
  while (cin >> x) {
    ans += expand(x, 75);
  }

  cout << ans << endl;


  return 0;
}
