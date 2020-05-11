#include <bits/stdc++.h>

using namespace std;

double L, K, T1, T2, H;

double observe(double amount)
{
  double rate = amount / T1;
  
  if (rate * T1 <= L) {
    return rate * T1;
  }

  double fill_time = L / rate;

  return max(L, L + (T1 - fill_time) * max(rate - K, 0.0) - T2 * K);
}

int main()
{
  cin >> L >> K >> T1 >> T2 >> H;

  double lo = 0, hi = 1;
  while (observe(hi) <= H) {
    hi *= 2;
  }
  for (int i = 0; i < 10000000; i++) {
    double mid = (lo+hi)/2;

    if (observe(mid) < H) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  cout << fixed << setprecision(10) << lo << ' ';
  
  lo = 0, hi = 1;
  while (observe(hi) <= H) {
    hi *= 2;
  }
  for (int i = 0; i < 10000000; i++) {
    double mid = (lo+hi)/2;

    if (observe(mid) <= H) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  cout << fixed << setprecision(10) << lo << endl;

  
  return 0;
}
