#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool check_expr(const vector<ll> &arg, int n, ll target)
{
  if (n == 1) {
    return arg[0] == target;
  }

  return (arg[n-1] <= target && check_expr(arg, n-1, target - arg[n-1])) ||
    (target % arg[n-1] == 0 && check_expr(arg, n-1, target / arg[n-1]));
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

  if (check_expr(arg, arg.size(), target)) {
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
