#include <bits/stdc++.h>
#include <gmpxx.h>

using namespace std;

typedef mpz_class ll;

ll gcd(ll a, ll b, ll &s, ll &t) { // a*s+b*t = g
  if (b==0) { t = 0; s = (a < 0) ? -1 : 1; return (a < 0) ? -a : a;
  } else { ll g = gcd(b, a%b, t, s);  t -= a/b*s;  return g; }
}

ll myceil(ll num, ll den)
{
  ll sign = (num < 0 ? -1 : 1) * (den < 0 ? -1 : 1);
  num = abs(num);
  den = abs(den);
  if (sign > 0) {
    return (num + (den-1))/den;
  } else {
    return -(num/den);
  }
}

ll myfloor(ll num, ll den)
{
  ll sign = (num < 0 ? -1 : 1) * (den < 0 ? -1 : 1);
  num = abs(num);
  den = abs(den);
  if (sign > 0) {
    return num/den;
  } else {
    return -((num + (den-1))/den);
  }
}

int main()
{
  ll N, A, B;
  cin >> N >> A >> B;

  ll g, s, t;
  g = gcd(A, B, s, t);
  if (N % g != 0) {
    cout << -1 << endl;
    return 0;
  }

  s *= N/g;
  t *= N/g;

  // A*s + B*t = N      for particular solution
  //
  // all solutions are:
  //
  //  (s', t') = (s + k * (B/g), t - k * (A/g))  for integer k
  //
  // there are 3 cases:
  //
  //        (i)   s' >= 0 and t' <= 0
  //        (ii)  s' <= 0 and t' >= 0
  //        (iii) s' >= 0 and t' >= 0
  //
  // (i)   k >= -s*g/B, t*g/A
  // (ii)  k <= -s*g/B, t*g/A
  // (iii) t*g/A >= k >= -s*g/B, 

  ll k1 = max(myceil(-s*g, B) , myceil(t*g, A));
  ll k2 = min(myfloor(-s*g, B), myfloor(t*g, A));
  ll lower3 = myceil(-s*g, B), upper3 = myfloor(t*g, A);
  if (lower3 <= upper3) {
    cout << N << endl;
  } else {
    ll s1 = s + k1*(B/g);
    ll s2 = s + k2*(B/g);
    ll t1 = t - k1*(A/g);
    ll t2 = t - k2*(A/g);
    
    ll time1 = max(abs(s1)*A, abs(t1)*B);
    ll time2 = max(abs(s2)*A, abs(t2)*B);
    
    cout << min(time1, time2) << endl;
  }
  
  return 0;
}
