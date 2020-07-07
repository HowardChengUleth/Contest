#include <bits/stdc++.h>

using namespace std;

// we will run the standard bracket matching algorithm from left to right,
// +1 for opening and -1 for closing.  When we do get a negative number,
// it means we have to move an opening bracket from later on to the front
// (this always exists).  It's always best to move the rightmost open bracket.
//
// Equivalently we can just prepend "(" until we no longer get a negative
// balance.  That is the answer.

void solve()
{
  int n;
  cin >> n;

  string s;
  cin >> s;

  
  for (int i = 0; i <= n; i++) {
    int bal = 0;
    bool good = true;
    for (auto c : s) {
      if (c == '(') bal++;
      else bal--;
      good &= (bal >= 0);
    }
    if (good) {
      cout << i << endl;
      return;
    }
    s = "(" + s;
  }
}

int main()
{
  int t;
  cin >> t;
  while (t--)
    solve();
  
  return 0;
}
