#include <bits/stdc++.h>

using namespace std;

int main()
{
  int ans = 0;
  while (true) {
    string s[11];
    for (int i = 0; i < 11; i++) {
      if (!(cin >> s[i])) goto out;
      sort(begin(s[i]), end(s[i]));
    }
    string out[4];
    for (int i = 0; i < 4; i++) {
      cin >> out[i];
      int n = out[i].length();
      if (n == 2 || n == 4 || n == 3 || n == 7) {
	ans++;
      }
    }
  }
 out:
  cout << ans << endl;

  return 0;
}
