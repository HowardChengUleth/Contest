#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll read()
{
  ll n1, n2;
  char c;
  cin >> n1 >> c >> n2;
  return n1 * 100 + n2;
}

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

int main()
{
  ll pt = read();
  ll p1 = read();
  ll p2 = read();

  ll s, t;
  ll g = gcd(p1, p2, s, t);

  vector<pair<ll, ll>> ans;
  if (pt % g ==  0) {
    s *= pt/g;
    t *= pt/g;

    //    s - k * p2/g >= 0
    //    s*g/p2 >= k
    //    t + k * p1/g >= 0

    ll k = s*g;
    if (k >= 0) {
      k /= p2;
    } else {
      k = -((-k+p2-1)/p2);
    }
    
    s -= k * p2/g;
    t += k * p1/g;


    while (s >= 0 && t >= 0) {
      ans.emplace_back(s, t);
      s += p2/g;
      t -= p1/g;
    }
  }

  sort(begin(ans), end(ans));
  if (ans.size() == 0) {
    cout << "none" << endl;
  } else {
    for (auto [n1, n2] : ans) {
      cout << n1 << ' ' << n2 << endl;
    }
  }

  return 0;
}
