#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll gcd(ll a, ll b, ll &s, ll &t) { // a*s+b*t = g
  if (b==0) { t = 0; s = (a < 0) ? -1 : 1; return (a < 0) ? -a : a;
  } else { ll g = gcd(b, a%b, t, s);  t -= a/b*s;  return g; }
}

// solve x = a[i] mod m[i] where gcd(m[i],m[j]) | a[i]-a[j]
// x0 in [0, lcm(m's)], x = x0 + t*lcm(m's) for all t.
ll cra(int n, ll m[], ll a[]) {
  ll u = a[0], v = m[0], p, q, r, t;
  for (int i = 1; i < n; i++) {
    r = gcd(v, m[i], p, q);  t = v;
    if ((a[i] - u) % r != 0) { }   // no solution!
    v = v/r * m[i];          u = ((a[i]-u)/r * p * t + u) % v;
  }
  if (u < 0) u += v;
  return u;
}


ll a, b, c, d, e, f, g;

void findbox(ll a, ll b, ll m[])
{
  priority_queue<ll> vol;
  for (int s = 1; true; s++) {
    ll width = a - 2*s;
    ll len = b - 2*s;
    ll height = s;
    if (width <= 0 || height <= 0) break;
    vol.push(width*len*height);
  }

  for (int i = 0; i < 3; i++) {
    m[i] = vol.top();
    vol.pop();
  }
}

int main()
{
  cin >> a >> b >> c >> d >> e >> f >> g;

  ll m[3];
  ll rhs[3] = { c, d, e };
  findbox(a, b, m);

  ll ans = cra(3, m, rhs);
  
  ll period = m[0] * (m[1]/gcd(m[0], m[1]));
  period = period * (m[2]/gcd(period, m[2]));

  ll k = (g - ans) / period;
  ans += k * period;

  cout << ans << endl;
  
  return 0;
}
