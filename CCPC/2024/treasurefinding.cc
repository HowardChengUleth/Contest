#include <bits/stdc++.h>
#include <gmpxx.h>
#include <cassert>

using namespace std;

typedef mpz_class ll;

struct Polynomial
{
  int deg;
  ll coeff[6];

  ll eval(ll x) const
  {
    ll ans = 0;
    for (int i = deg; i >= 0; i--) {
      ans *= x;
      ans += coeff[i];
    }
    return ans;
  }

  Polynomial derivative() const
  {
    Polynomial d;
    d.deg = deg-1;
    for (int i = 1; i <= deg; i++) {
      d.coeff[i-1] = i * coeff[i];
    }
    return d;
  }
};

istream &operator>>(istream &is, Polynomial &p)
{
  is >> p.deg;
  for (int i = 0; i <= p.deg; i++) {
    is >> p.coeff[i];
  }
  assert(p.coeff[p.deg] != 0);
  return is;
}


int sign(ll x)
{
  if (x == 0) return 0;
  if (x > 0) return 1;
  return -1;
}

ll find_root_binary(const Polynomial &p, ll lo, ll hi)
{
  ll flo = p.eval(lo), fhi = p.eval(hi);
  int slo = sign(flo), shi = sign(fhi);

  if (slo == 0) return lo;
  if (shi == 0) return hi;

  assert(lo != hi && slo * shi < 0);

  // binary search
  while (lo < hi) {
    ll mid = lo + (hi - lo)/2;
    ll fmid = p.eval(mid);
    int smid = sign(fmid);

    if (smid == 0) return mid;
    if (slo * smid < 0) {
      hi = mid;
    } else {
      assert(smid * shi < 0);
      lo = mid;
    }
  }

  assert(false);
  return INT_MAX;
}

ll find_root(const Polynomial &p, int lo = -10000, int hi = 10000)
{
  if (p.coeff[0] == 0) return 0;
  
  ll flo = p.eval(lo), fhi = p.eval(hi);
  int slo = sign(flo), shi = sign(fhi);

  if (slo == 0) return lo;
  if (shi == 0) return hi;

  if (slo * shi < 0) {
    return find_root_binary(p, lo, hi);
  }

  // try Newton's method
  Polynomial pprime = p.derivative();
  ll x = lo + (hi-lo)/2;

  while (p.eval(x) != 0) {
    ll fx = p.eval(x);
    ll fxp = pprime.eval(x);
    
    int sx = sign(fx);
    if (slo * sx < 0) {
      // switch to binary search as soon as we can
      return find_root_binary(p, lo, x);
    }

    ll dx;
    if (fxp != 0) {
      dx = fx / fxp;

      // force to perturb if dx == 0
      if (dx == 0) {
	if (fx * fxp > 0) {
	  dx = 1;
	} else {
	  dx = -1;
	}
      }
    } else {
      dx = (fx > 0) ? 1 : 1;
    }
    x -= dx;
  }
  return x;
}

void solve()
{
  Polynomial p;
  cin >> p;
  
  ll root = find_root(p);
  cout << root << endl;
}
  


int main()
{
  int n;
  cin >> n;
  while (n--) {
    solve();
  }
  return 0;
}

