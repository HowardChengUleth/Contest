#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

int N;
int d[100000], a[100000];

ld check(ld vel)
{
  ld total = 0.0;
  for (int i = 0; i < N; i++) {
    // f''(t) = a[i]
    // f'(t) = a[i] * t + vel
    // f(t) = a[i]/2 * t^2 + vel * t

    // f(t) = d[i] => a[i]/2 * t^2 + vel * t - d[i] = 0
    ld A = a[i]/2.0, B = vel, C = -d[i];
    ld disc = B*B - 4*A*C;
    if (disc < 0) return -1;
    ld t1 = (-B + sqrt(disc)) / (2*A), t2 = (-B - sqrt(disc)) / (2*A);
    if (t1 < 0) t1 = 1e100;
    if (t2 < 0) t2 = 1e100;
    ld t = min(t1, t2);
    if (t == 1e100) {
      return -1;
    }
    total += t;
    vel += a[i] * t;
    assert(vel >= 0.0);
  }
  return total;
}

int main()
{
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> d[i] >> a[i];
  }

  ld lo = 0, hi = 1;
  ld ans = 0.0;

  if (check(lo) >= 0) {
    ans = lo;
  }
  while (check(hi) < 0) {
    hi *= 2;
  }
  while (hi - lo > 1e-10) {
    ld mid = (lo+hi)/2.0;
    if (check(mid) < 0) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  ans = hi;

  cout << fixed << setprecision(10) << ans << ' ' << check(ans) << endl;

  return 0;
}
