#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

long long gcd(long long a, long long b)
{
  if (a < 0) {
    return gcd(-a, b);
  } else if (b < 0) {
    return gcd(a, -b);
  }
  while (b) {
    long long r = a % b;
    a = b;
    b = r;
  }
  return a;
}

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

int solve(long long x1, long long y1, long long x2, long long y2)
{
  // handle vertical and horizontal cases
  if (x1 == x2) {
    if (x1 % 10 != 0) return 0;
    if (y2 < y1) swap(y1, y2);
    while (y1 % 10 != 0) y1++;
    while (y2 % 10 != 0) y2--;
    if (y2 < y1) return 0;
    return y2/10 - y1/10 + 1;
  } else if (y1 == y2) {
    return solve(y1, x1, y2, x2);
  }

  if (x2 < x1) {
    swap(x1, x2);
    swap(y1, y2);
  }

  // all interesting locations of x must be x1 + (-x1 mod 10) + 10*k
  //
  // and 0 <= k <= (x2 - x1 - (-x1 mod 10)) / 10
  long long x1inv = x1 % 10;
  if (x1inv < 0) {
    x1inv += 10;
  }
  x1inv = (10 - x1inv) % 10;
  long long k_upper = (int)floor((double)((x2 - x1) - x1inv) / 10);
  if (k_upper < 0) return 0;

  long long rise = y2 - y1;
  long long run = x2 - x1;
  long long g = gcd(rise, run);
  rise /= g;
  run /= g;
  if (run < 0) {
    run *= -1;
    rise *= -1;
  }

  // y-coordinates are:
  //
  // y1 + (rise/run) * (x1inv + 10*k) = 0  mod 10
  //
  // so:
  //
  // y1*run + rise*x1inv + 10*rise*k = 10*run*l        for some k and l
  // run*l - rise*k = (y1*run + rise*x1inv)/10 
  
  // RHS not integer: no solution
  if ((y1 * run + rise * x1inv) % 10 != 0) {
    return 0;
  }
  long long rhs = (y1 * run + rise * x1inv) / 10;
  long long l, k;
  gcd(run, -rise, l, k);         // gcd(run,rise) == 1
  k *= rhs;

  // all solutions of k are:
  //
  // 0 <= k <= k_upper, where
  //
  // 0 <= k + t*run <= k_upper, so
  //
  //    -k/run <=  t <= (k_upper - k)/run
  
  long long t_lower = ceil((double)(-k)/run);
  long long t_upper = floor((double)(k_upper - k)/run);

  return max(t_upper - t_lower + 1, 0LL);
}

int main(void)
{
  int N;
  cin >> N;
  while (N-- > 0) {
    double xx1, yy1, xx2, yy2;
    cin >> xx1 >> yy1 >> xx2 >> yy2;

    long long x1 = floor(xx1 * 10 + 0.5);
    long long x2 = floor(xx2 * 10 + 0.5);
    long long y1 = floor(yy1 * 10 + 0.5);
    long long y2 = floor(yy2 * 10 + 0.5);

    cout << solve(x1, y1, x2, y2) << endl;
  }
  return 0;
}
