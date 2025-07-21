#include <bits/stdc++.h>

using namespace std;

// Basically you want to do as many problems as possible to improve skills.
//
// This seems harder and it looks...the idea is that if you can do a problem,
// always do it.
//
// Why is skipping a problem you can do not going to be any better?  Let's
// say you can do the first problem (it doesn't matter which problem you
// look at).
//
// If the "optimal" solution does not require doing the first problem (p0),
// that means the first problem (pk) you do in the optimal
// solution is also good for the current skill level.  If you simply
// do the p0 instead of pk and leave the rest unchanged, you will still be
// able to achieve the same optimal solution.  So there is no reason to skip
// any problem you can do.
//

int main()
{
  int n, s;
  cin >> n >> s;

  for (int i = 0; i < n; i++) {
    int l, r;
    cin >> l >> r;
    if (l <= s && s <= r)
      s++;
  }

  cout << s << endl;
  

  return 0;
}
