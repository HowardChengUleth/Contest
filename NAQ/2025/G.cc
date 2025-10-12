#include <bits/stdc++.h>

using namespace std;


// linearity of expectation means that we can just figure out the chance
// that a certain player is the winner...and then add up all the winners

typedef int64_t ll;

const ll MOD = 998244353;

/*
 * Extended Euclidean Algorithm
 *
 * Author: Howard Cheng
 *
 * Given two integers, return their gcd and the cofactors to form the
 * gcd as a linear combination.
 *
 * a*s + b*t = gcd(a,b)
 *
 */

#include <iostream>
#include <cassert>

using namespace std;

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

ll frac(ll a, ll b)
{
  ll s, t;
  gcd(b, MOD, s, t);
  a *= s;
  a %= MOD;

  if (a < 0) {
    a += MOD;
  }

  return a;
}

ll expmod(ll b, ll n)
{
  if (n == 0) {
    return 1;
  } else if (n % 2 == 0) {
    return expmod((b*b) % MOD, n/2);
  } else {
    return (expmod(b, n-1) * b) % MOD;
  }
}

int main()
{
  int n, k;
  cin >> n >> k;

  // for one player to win, the other 2k players (k on either side) have
  // to go to the other rooms
  ll a, b;

  a = 2*k;
  b = 2*k+1;

  a = expmod(a, 2*k);
  b = expmod(b, 2*k);

  a = (a * n) % MOD;

  cout << frac(a, b) << endl;

  return 0;
}
