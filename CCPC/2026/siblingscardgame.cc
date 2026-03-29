//
// Basically, we are asking how many of the binomial coefficients C(n,k)
// are odd for k = 1, 2, ..., n.
//
// Luca's theorem says that we can look at the binary expansion of n and k,
// C(n,k) is odd if and only if the 1's in k's binary expansion is a subset
//   of those in the 1's in n's expansion
//
// So we look at how many 1s are in the binary expansion of n, and then
// the binary expansions can have 1s only in those spots.  So we choose a
// non-empty subset of those positions for 1s in k.  If n has t 1s, then
// there are 2^t - 1 of them.
#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  // look at binary expansion of n

  int ones = __builtin_popcount(n);
  cout << (1 << ones)-1 << endl;


  return 0;
}
