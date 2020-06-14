#include <bits/stdc++.h>

using namespace std;

// last 2 digits must be 00, 25, 50, or 75.  Try each one and see.
// To test each one, you can greedily move the rightmost numbers to that
// spot and see how many swaps it takes

int check(string n, string suff)
{
  auto i1 = n.rfind(suff[1]);
  if (i1 == string::npos)
    return INT_MAX;

  auto last = string::npos;
  if (suff[0] == suff[1]) {
    last = i1-1;
  }
  auto i2 = n.rfind(suff[0], last);
  if (i2 == string::npos) {
    return INT_MAX;
  }

  int swaps = 0;
  if (min(i1, i2) == 0 && max(i1, i2) > 1 && n[1] == '0') {
    // we have to be a bit careful here because we can't just swap
    swaps = -1;
    for (int i = 2; i < n.length(); i++) {
      if (n[i] != '0') {
	swaps = i-1;
	break;
      }
    }
    if (swaps < 0) {
      return INT_MAX;
    }
  }

  if (i1 > i2) {
    return swaps + (n.length()-1 - i1) + (n.length()-2 - i2);
  } else {
    return swaps + (n.length()-1 - i2) + (n.length()-1 - i1);
  }
}

int main()
{
  string n;
  cin >> n;

  int ans = INT_MAX;
  ans = min(ans, check(n, "00"));
  ans = min(ans, check(n, "25"));
  ans = min(ans, check(n, "50"));
  ans = min(ans, check(n, "75"));

  if (ans == INT_MAX) {
    cout << -1 << endl;
  } else {
    cout << ans << endl;
  }


  return 0;
}
