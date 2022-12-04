#include <bits/stdc++.h>

using namespace std;

bool contain(int s1, int e1, int s2, int e2)
{
  // [s1,e1] in [s2,e2]
  return s2 <= s1 && e1 <= e2;
}

bool contain(string s)
{
  replace(begin(s), end(s), '-', ' ');
  replace(begin(s), end(s), ',', ' ');
  istringstream iss(s);

  int s1, e1, s2, e2;
  iss >> s1 >> e1 >> s2 >> e2;

  return contain(s1, e1, s2, e2) || contain(s2, e2, s1, e1);
}

int main()
{
  int ans = 0;

  string s;
  while (cin >> s) {
    if (contain(s)) {
      ans++;
    }
  }
  cout << ans << endl;
  return 0;
}
