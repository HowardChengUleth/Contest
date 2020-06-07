#include <bits/stdc++.h>

using namespace std;

// If we know how to compute the number of multiples of v in [1,X] for
// any X, then the answer are the multiples in [1,L] - those in [1,r]
// + those in [1,r-1].  The number of multiples of v in [1,X] is X/v.

void solve()
{
  int L, v, l, r;
  cin >> L >> v >> l >> r;

  // number of points divisible by v in [1, L] is L/v
  int total = L/v;

  // get rid of points divisible by v in [1, r]
  total -= r/v;

  // add back points divisible by v in [1,l-1]
  total += (l-1)/v;

  cout << total << endl;
  

}

int main()
{
  int t;
  cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}
