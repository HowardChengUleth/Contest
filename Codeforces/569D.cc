#include <bits/stdc++.h>

using namespace std;

//
// For a relation to be symmetric and transitive but not reflexive, it means
// that there are some "isolated" elements that are not related to anything
// while the remaining elements form an equivalence relation.
//
// So to get such a relation of n elements, we need k isolated elements
// (k = 1, ..., n) and the remaining must form an equivalence relation.
// So we need to find sum C(n,k) * E(n-k), k = 1, ..., n, where E(n)
// is the number of equivalence relations of n items.
// This is because we have C(n,k) ways of choosing which ones are isolated
// and then the rest is an equivalent relation.
//
// How do we compute E(n)?  An equivalence relation can be identified by its
// equivalence classes, so we just have to figure out how many ways we can
// divide n elements into some number (m) of equivalence classes where
// m = 1, ..., n.  This can in turn be computed with dynamic programming

typedef long long ll;

const ll MOD = 1000000007;

ll C[4001][4001];

void initC()
{
  for (int n = 0; n <= 4000; n++) {
    C[n][0] = C[n][n] = 1;
    for (int k = 1; k < n; k++) {
      C[n][k] = (C[n-1][k-1] + C[n-1][k]) % MOD;
    }
  }
}

ll memo[4001][4001];
ll E[4001];

ll ways(int n, int m)
{
  assert(m <= n);
  if (m == 1 || n == m) {
    return 1;
  }
  if (memo[n][m] >= 0) {
    return memo[n][m];
  }

  // we can either start a new class with the last element,
  // or add the last element to one of the existing classes
  return memo[n][m] = (ways(n-1,m-1) + (ways(n-1,m)*m) % MOD) % MOD;
}

void initE()
{
  for (int n = 0; n <= 4000; n++) {
    fill(memo[n], memo[n]+4001, -1);
  }
  
  E[0] = 1;
  for (int n = 1; n <= 4000; n++) {
    E[n] = 0;
    for (int m = 1; m <= n; m++) {
      E[n] += ways(n,m);
      E[n] %= MOD;
    }
  }
}

int main()
{
  initC();
  initE();
  int n;
  cin >> n;

  ll ans = 0;
  for (int k = 1; k <= n; k++) {
    ans += (C[n][k] * E[n-k]) % MOD;
    ans %= MOD;
  }
  cout << ans << endl;
  
  return 0;
}
