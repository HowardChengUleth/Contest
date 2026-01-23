#include <bits/stdc++.h>

using namespace std;

bool check(const string &guess, const string &s1, const string &s2)
{
  int matched = 0;
  for (int i = 0; i < 4; i++) {
    if (guess[i] == s1[i] || guess[i] == s2[i]) {
      matched++;
    }
  }

  return matched == 4;
}

int main()
{
  string s1, s2;
  cin >> s1 >> s2;

  int ans = 0;
  for (int i = 0; i < 10000; i++) {
    ostringstream oss;
    oss << setw(4) << setfill('0') << i;
    if (check(oss.str(), s1, s2)) {
      ans++;
    }
  }

  cout << ans << endl;

  return 0;
}
