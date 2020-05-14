#include <bits/stdc++.h>

using namespace std;

//
// First, to know if a chunk is divisible by 3, check if the sum of digits is
// divisible by 3.
//
// We use dynamic programming here.
//
// f(n) = the answer for the first n digits.
//
// For the recursion, we look at the n-th digit.  The last digit is going
// to be included in the last chunk.  How big is this chunk?  It can be 1,
// 2, 3, ..., n digits.  If the last chunk has size k, then that partition
// will result in f(n-k) + 1 if the last chunk is divisible by 3, or f(n-k)
// otherwise.  Trying all chunk size in this way will result in O(n) time to
// compute each f(n), O(n^2) overall which is too slow.
//
// Now an observation: look at the partial sum ps[n] = sum(s[j], j = 1..n).
// If ps[n-k1] = ps[n-k2] mod 3 and k1 < k2, then there is no point looking
// at k2: the last chunk with k1 digits is guaranteed to be better than
// a chunk of k2 digits, because you can always form one more chunk of size
// k2-k1 that is divisible by 3.
//
// Since there are only 3 possible remainders, we just have to remember for
// each remainder what is the largest index so far that has a partial sum
// of that remainder.  So instead of trying all last chunks of 1, 2, ..., n,
// you only need to try the smallest chunks indicated by the last index
// such that the partial sum = 0, 1, 2 mod 3.

int main()
{
  string s;
  cin >> s;

  int n = s.length();

  int f[200001];
  f[0] = 0;

  int ps[200001] = {0};
  int last[3] = {-1,-1,-1};
  for (int i = 1; i <= n; i++) {
    int d = s[i-1] - '0';
    ps[i] = (ps[i-1] + d) % 3;

    f[i] = ps[i] == 0;     // can always decide to not cut
    for (int j = 0; j < 3; j++) {
      if (last[j] < 0) continue;
      f[i] = max(f[i], f[last[j]] + (ps[i] == ps[last[j]]));
    }

    last[ps[i]] = i;
  }

  cout << f[n] << endl;
  
  return 0;
}
