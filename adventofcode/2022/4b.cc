#include <bits/stdc++.h>

using namespace std;

bool overlap(string s)
{
  replace(begin(s), end(s), '-', ' ');
  replace(begin(s), end(s), ',', ' ');
  istringstream iss(s);

  int s1, e1, s2, e2;
  iss >> s1 >> e1 >> s2 >> e2;

  if (s1 > s2) {
    swap(s1, s2);
    swap(e1, e2);
  }
  return !(s2 > e1);
}

int main()
{
  int ans = 0;

  string s;
  while (cin >> s) {
    if (overlap(s)) {
      ans++;
    }
  }
  cout << ans << endl;
  return 0;
}
