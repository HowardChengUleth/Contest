#include <iostream>
#include <cassert>
#include <cmath>
#include <algorithm>

using namespace std;

long long gcd(long long a, long long b, long long &s, long long &t)
{
  long long r, r1, r2, a1, a2, b1, b2, q;

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

bool check(long long L, long long R, long long l, long long r, long long n)
{
  long long page = 1;

  while (L + R > 0) {
    long long old_LR = L + R;
    // flip left as much as we can
    long long times = min((page - 1) / l, L);
    L -= times;
    page -= times * l;

    // flip right as much as we can
    times = min((n - page) / r, R);
    R -= times;
    page += times * r;
    
    if (L + R == old_LR) {
      return false;
    }
  }
  return true;
}

long long solve(long long n, long long l, long long r, long long t)
{
  long long g, L, R;

  g = gcd(-l, r, L, R);
  if ((t-1) % g != 0) {
    return -1;
  }
  L *= (t-1)/g;
  R *= (t-1)/g;

  long long k = (long long)(ceil(max((double)(-g*L)/r, (double)(-g*R)/l)));
  L += k * r/g;
  R += k * l/g;
  while (L - r/g >= 0 && R - l/g >= 0) {
    L -= r/g;
    R -= l/g;
  }

  do {
    if (check(L, R, l, r, n)) {
      return L+R;
    }
    L += r/g;
    R += l/g;
  } while (L + R <= n);      // each flip must lead to a new page
  return -1;
}

void do_case()
{
  long long n, l, r, t;
  cin >> n >> l >> r >> t;

  long long steps = solve(n, l, r, t);
  if (steps < 0) {
    cout << "uh-oh!" << endl;
  } else {
    cout << steps << endl;
  }
}

int main(void)
{
  int cases;
  cin >> cases;
  while (cases-- > 0) {
    do_case();
  }
  
  return 0;
}
