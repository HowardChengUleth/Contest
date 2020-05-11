#include <bits/stdc++.h>

using namespace std;

void solve()
{
  int n;
  string s;
  cin >> n >> s;

  if (n == 2 && s[0] >= s[1]) {
    cout << "NO" << endl;
    return;
  }
  cout << "YES" << endl;
  cout << 2 << endl;
  cout << s[0] << ' ' << s.substr(1) << endl;

}

int main()
{
  int q;
  cin >> q;
  while (q--)
    solve();
  
  return 0;
}
