#include <bits/stdc++.h>

using namespace std;

long long fast_exp(long long b, long long n)
{
  long long res = 1;
  long long x = b;

  while (n > 0) {
    if (n & 0x01) {
      n--;
      res *= x;
    } else {
      n >>= 1;
      x *= x;
    }
  }

  return res;
}

long long eulerphi(long long n)
{
  long long ans = 1;
  long long p = 2;
  long long k;

  if (n == 1) {
    return 0;
  }

  for (k = 0; n % 2 == 0; k++) {
    n /= 2;
  }
  if (k) {
    ans *= fast_exp(2, k-1);
  }

  for (p = 3; p*p <= n; p += 2) {
    for (k = 0; n % p == 0; k++) {
      n /= p;
    }
    if (k) {
      ans *= fast_exp(p, k-1) * (p-1);
    }
  }
  if (n > 1) {
    ans *= n-1;
  }
  
  return ans;
}

int main(void)
{
  long long n;
  
  while (cin >> n && n) {
    cout << eulerphi(n) << endl;
  }

  return 0;
}
