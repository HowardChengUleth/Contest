#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int sides[5] = { 4, 6, 8, 12, 20 };
const ll MOD = 1000000009;
ll inv[21];

ll gcd(ll a, ll b, ll &s, ll &t)
{
  ll r, r1, r2, a1, a2, b1, b2, q;
  ll A = a;
  ll B = b;

  /* unnecessary if a, b >= 0 */
  if (a < 0) {
    r = gcd(-a, b, s, t);
    s *= -1;
    return r;
  }
  if (b < 0) {
    r = gcd(a, -b, s, t);
    t *= -1;
    return r;
  }

  a1 = b2 = 1;
  a2 = b1 = 0;

  while (b) {
    assert(a1*A + a2*B == a);
    q = a / b;
    r = a % b;
    r1 = a1 - q*b1;
    r2 = a2 - q*b2;
    a = b;
    a1 = b1;
    a2 = b2;
    b = r;
    b1 = r1;
    b2 = r2;
  }

  s = a1;
  t = a2;
  assert(a >= 0);
  return a;
}

ll binom(ll n, ll k)
{
  ll ans = 1;
  for (int i = 1; i <= k; i++) {
    ans *= n--;
    ans %= MOD;
    ans *= inv[i];
    ans %= MOD;
  }
  return ans;
}

// number of ways to roll n dice, where each dice is allowed to roll
// s+1 different types of faces
ll ways_single(ll n, ll s)
{
  return binom(n + s - 1, s);
}

ll num[5];

ll memo[5][21];

ll ways_all(int index, int low)
{
  if (index >= 5)
    return 1;

  if (num[index] == 0) {
    return ways_all(index+1, low);
  }

  if (memo[index][low] >= 0) {
    return memo[index][low];
  }
  
  ll ans = 0;
  for (int hi = low; hi <= sides[index]; hi++) {
    ans += (ways_single(num[index], hi-low) * ways_all(index+1, hi)) % MOD;
    ans %= MOD;
  }

  return memo[index][low] = ans;
}

int main()
{
  for (int i = 1; i <= 20; i++) {
    ll s, t;
    gcd(i, MOD, s, t);
    while (s < 0) {
      s += MOD;
    }
    inv[i] = s % MOD;
  }

  for (int i = 0; i < 5; i++) {
    cin >> num[i];
    fill(memo[i], memo[i]+21, -1);
  }

  cout << ways_all(0, 1) << endl;
  
  return 0;
}
