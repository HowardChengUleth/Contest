#include <bits/stdc++.h>

using namespace std;

void solve()
{
  string s;
  cin >> s;

  int sum = 0;
  reverse(begin(s), end(s));
  for (int i = 0; i < s.length(); i++) {
    int d = s[i] - '0';
    if (i % 2 == 1) {
      d *= 2;
      if (d > 9) {
	d = d%10 + d/10;
      }
    }

    sum += d;
    sum %= 10;
  }

  if (sum == 0) {
    cout << "PASS" << endl;
  } else {
    cout << "FAIL" << endl;
  }
}

int main()
{
  int T;
  cin >> T;

  for (int i = 0; i < T; i++) {
    solve();
  }
  
  return 0;
}
