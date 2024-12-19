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

bool possible(const string &s, int n, vector<int> &memo, int index)
{
  if (index >= n)
    return true;

  if (memo[index] != -1) {
    return memo[index];
  }

  memo[index] = false;
  for (auto t : towel) {
    if (index + t.length() > n) continue;
    if (t != s.substr(index, t.length())) continue;
    if (possible(s, n, memo, index + t.length())) {
      return memo[index] = true;
    }
  }

  return memo[index];
}

bool possible(const string &s)
{
  int n = s.length();
  vector<int> memo(n, -1);

  return possible(s, n, memo, 0);
}

int main()
{
  read_towel();

  int ans = 0;
  
  string design;
  while (cin >> design) {
    if (possible(design)) {
      ans++;
    }
  }

  cout << ans << endl;

  return 0;
}
