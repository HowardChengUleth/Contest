#include <bits/stdc++.h>

using namespace std;

const string s = "welcome to code jam";

int count(string line, int li, int si)
{
  if (si == s.length()) return 1;
  if (li == line.length()) return 0;

  int ans = 0;
  if (line[li] == s[si]) {
    ans += count(line, li+1, si+1);
  }
  ans += count(line, li+1, si);
  return ans % 10000;
}

void solve()
{
  string line;
  getline(cin, line);
  
  int ans = count(line, 0, 0);
  cout << setw(4) << setfill('0') << ans << endl;
}

int main()
{
  int T;
  cin >> T;
  cin.ignore();
  for (int i = 1; i <= T; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
  return 0;
}

