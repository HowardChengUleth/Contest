#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<string> towel;

void read_towel()
{
  string line;
  getline(cin, line);
  replace(begin(line), end(line), ',', ' ');
  istringstream iss(line);

  string t;
  while (iss >> t) {
    towel.push_back(t);
  }
}

ll ways(const string &s, int n, vector<ll> &memo, int index)
{
  if (index >= n) {
    assert(index == n);
    return 1;
  }

  if (memo[index] != -1) {
    return memo[index];
  }

  memo[index] = 0;
  for (auto t : towel) {
    if (index + t.length() > n) continue;
    if (t != s.substr(index, t.length())) continue;
    memo[index] += ways(s, n, memo, index + t.length());
  }

  return memo[index];
}

ll ways(const string &s)
{
  int n = s.length();
  vector<ll> memo(n, -1);

  return ways(s, n, memo, 0);
}

int main()
{
  read_towel();

  ll ans = 0;
  
  string design;
  while (cin >> design) {
    ans += ways(design);
  }

  cout << ans << endl;

  return 0;
}
