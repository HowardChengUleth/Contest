#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

set<ll> find_all(const vector<ll> &arg, int n)
{
  if (n == 1) {
    set<ll> S;
    S.insert(arg[0]);
    return S;
  }

  set<ll> S = find_all(arg, n-1);
  set<ll> T;
  for (auto s : S) {
    T.insert(s + arg[n-1]);
    T.insert(s * arg[n-1]);

    ll ten = 1;
    while (ten <= arg[n-1]) {
      ten *= 10;
    }
    T.insert(s * ten + arg[n-1]);
  }

  return T;
}
		  
ll check(string line)
{
  istringstream iss(line);
  ll target;
  char colon;
  iss >> target >> colon;

  vector<ll> arg;
  ll x;
  while (iss >> x) {
    arg.push_back(x);
  }

  set<ll> answers = find_all(arg, arg.size());

  if (answers.count(target) > 0) {
    return target;
  } else {
    return 0;
  }
}

int main()
{
  string line;

  ll ans = 0;
  while (getline(cin, line)) {
    ans += check(line);
  }

  cout << ans << endl;

  return 0;
}
