//
// Another way to see if C(n,k) is odd: count the number of powers of 2s
// in numerator and denominator.
//
// For any number t, the number of power of 2's dividing t is the number of
// 0s counting from the right in binary expansion.
//
// Since binomial coefficients can be written as a product of a range of
// numbers in numerator and denominator, we need a quick way to count the
// number of power of 2's in a range.  That can be done with a partial sum
// array of the individual power of 2's

#include <bits/stdc++.h>

using namespace std;

int main()
{
  unsigned int n;
  cin >> n;

  vector<int> pow2(n+1, 0);
  for (unsigned int i = 1; i <= n; i++) {
    pow2[i] = countr_zero(i);
  }

  vector<int> psum(n+1, 0);
  partial_sum(begin(pow2), end(pow2), begin(psum));

  int ans = 1;      // C(n,n) = 1

  for (int k = 1; k < n; k++) {
    // C(n,k) = n * (n-1) * ... * (n-k+1) / (k * (k-1) * (k-2) ... * 1)

    int top = psum[n] - psum[n-k];
    int bot = psum[k];

    if (top <= bot) {
      ans++;
    }
  }

  cout << ans << endl;
  
  return 0;
}
