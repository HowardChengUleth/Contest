#include <bits/stdc++.h>

using namespace std;

int getint()
{
  int x = 0;
  char ch;
  while (true) {
    cin.get(ch);
    x = x * 10 + ch - '0';
    cin.get(ch);
    if (ch == '\n')
      break;
  }
  return x;
}

void writeint(int x, bool last = true)
{
  if (x == 0) {
    if (last) {
      cout << x << endl;
    }
    return;
  }

  writeint(x / 10, false);
  cout << x % 10;
  cout << (last ? '\n' : ' ');
}

void solve()
{
  int x = getint();
  x += getint();
  writeint(x);
}

int main()
{
  int t;
  cin >> t;
  cin.ignore(1);
  while (t--) {
    solve();
  }

  return 0;
}
