#include <bits/stdc++.h>

using namespace std;

int main()
{
  string s, t;

  while (getline(cin, t)) {
    s += t;
  }

  long long ans = 0;
  regex pattern("mul\\(([0-9]{1,3}),([0-9]{1,3})\\)");

  auto matches_begin = sregex_iterator(begin(s), end(s), pattern);
  auto matches_end = sregex_iterator();

  for (auto it = matches_begin; it != matches_end; ++it) {
    auto match = *it;
    int x = stoi(match[1]);
    int y = stoi(match[2]);
    cout << match.str() << ' ' << x << ' ' << y << endl;
    ans += x*y;
  }
  
  cout << ans << endl;
  
  return 0;
}
