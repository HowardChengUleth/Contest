#include <bits/stdc++.h>

using namespace std;

int myhash(const string &s)
{
  int ans = 0;
  for (auto c : s) {
    ans += (int)c;
    ans *= 17;
    ans %= 256;
  }
  return ans;

}

int main()
{
  string line;
  cin >> line;
  replace(begin(line), end(line), ',', ' ');

  int ans = 0;
  istringstream iss(line);
  string s;
  while (iss >> s) {
    ans += myhash(s);
  }

  cout << ans << endl;

  return 0;
}
