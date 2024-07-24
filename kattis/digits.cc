#include <bits/stdc++.h>

using namespace std;

void solve(const string &s)
{
  int i = 1;
  int x = s.length();

  // deal with special case that it ends right away
  if (s == "1") {
    cout << 1 << endl;
    return;
  }

  while (true) {
    i++;
    int x2 = to_string(x).length();
    if (x2 == x) {
      cout << i << endl;
      return;
    }
    x = x2;
  }
}

int main()
{
  string s;
  while (cin >> s && s != "END") {
    solve(s);
  }

  return 0;
}
