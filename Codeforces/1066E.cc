#include <bits/stdc++.h>

using namespace std;

// Note that b is being shifted to the right each step, and each time it is
// bitwise-ANDed with a.
//
// We are going to look at the contribution of each power of 2 (or
// bit) that goes into the final answer.  Of course, for a bit to
// matter, that bit must be 1 in a.  How many times would that bit in
// 1 go into the final answer?  That depends on how many 1's are in b at
// that position or to the left.
//
// So the algorithm is: for each 1 bit in a, look at how many
// positions to the left of that (and including that position) in b
// are 1.  This can be done easily computed with a prefix sum.

typedef long long ll;

const ll MOD = 998244353;
const int MAX = 200000;

int main()
{
  int n, m;
  int a[MAX] = {0}, b[MAX] = {0};
  char ch;

  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> ch;
    a[MAX-n+i] = (ch == '1');
  }
  for (int i = 0; i < m; i++) {
    cin >> ch;
    b[MAX-m+i] = (ch == '1');
  }

  ll ps[MAX];
  partial_sum(b, b+MAX, ps);

  ll power2[MAX];
  power2[0] = 1;
  for (int i = 1; i < MAX; i++) {
    power2[i] = (power2[i-1]*2) % MOD;
  }
  
  long long ans = 0;
  for (int i = 0; i < MAX; i++) {
    if (!a[i]) continue;
    ans += (ps[i] * power2[MAX-i-1]) % MOD;
    ans %= MOD;
  }
  cout << ans << endl;

  return 0;
}
