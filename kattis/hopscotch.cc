#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll p = 1000000007;

ll fact[2000001];

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
  return a;
}

ll inv(ll x)
{
  ll s, t;
  gcd(x, p, s, t);
  if (s < 0) s += p;
  return s;
}

ll solns(ll N, ll X, ll k)
{
  ll top = N - X*k;

  return ((fact[top+k-1] * inv(fact[k-1])) % p * inv(fact[top])) % p;
}

int main()
{
  fact[0] = 1;
  for (int i = 1; i <= 2000000; i++) {
    fact[i] = (i * fact[i-1]) % p;
  }

  ll N, X, Y;
  cin >> N >> X >> Y;

  ll ans = 0;
  for (int k = 1; k*X <= N && k*Y <= N; k++) {
    ans += (solns(N, X, k) * solns(N, Y, k)) % p;
    ans %= p;
  }

  cout << ans << endl;
  
  return 0;
}
