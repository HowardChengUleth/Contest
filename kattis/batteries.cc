#include <bits/stdc++.h>

using namespace std;


// the idea is that once you decide where to test the first one, you
// have to consider two cases: if it explodes then you have one
// battery left and the only thing you can do is to test 1, 2, ... up
// to the last known explosion.
//
// if it does not explode, you still have two batteries left to measure
// a range of n-i, and we can recurse.

int ans[5000];

// n > 1
int solve(int n)
{
  if (n == 1) return 0;
  if (ans[n] >= 0) return ans[n];
  
  int res = n-1;  // just test them from 1, 2, 3, ..., n-1

  // try to test the first battery at level i
  for (int i = 1; i < n; i++) {
    // if it breaks at level i, we need to use the remaining battery to
    // measure i-1 levels
    //
    // if it doesn't break, we still have two batteries to measure n-i levels

    res = min(res, 1 + max(i-1, solve(n-i)));
  }

  return ans[n] = res;
}

int main()
{
  fill(ans, ans+5000, -1);
  
  int n;
  while (cin >> n && n) {
    cout << solve(n) << endl;
  }

  return 0;
}
