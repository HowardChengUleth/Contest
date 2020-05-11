#include <iostream>
#include <algorithm>
#include <bitset>

using namespace std;

const int MAX_N = 20000000;
bitset<MAX_N+1> isprime;
int prime[1300000];
int np = 0;

int val(int n, int p)
{
  int ans = 0;
  long long b = p;
  while (b <= n) {
    ans += n/b;
    b *= p;
  }
  return ans;
}

int solve(int n, int m)
{
  int ans = 1;
  for (int i = 0; i < np && prime[i] <= n; i++) {
    int e = (val(n, prime[i]) - val(n-m, prime[i])) % 4;
    int b = prime[i] % 10;
    while (e--) {
      ans = (ans * b) % 10;
    }
  }

  int e2 = val(n, 2) - val(n-m, 2);
  int e5 = val(n, 5) - val(n-m, 5);
  int minus = min(e2, e5);

  e2 -= minus;
  e5 -= minus;
  
  if (e2 > 0) {
    e2 %= 4;
    if (e2 == 0) e2 = 4;
    while (e2--) {
      ans = (ans * 2) % 10;
    }
  }

  if (e5 > 0) {
    ans = (ans * 5) % 10;
  }

  return ans;
}

int main(void)
{
  isprime.set();
  for (long long i = 2; i <= MAX_N; i++) {
    if (!isprime.test(i)) continue;
    if (i != 2 && i != 5) {
      prime[np++] = i;
    }
    for (long long int j = i*i; j <= MAX_N; j += i) {
      isprime.reset(j);
    }
  }

  int n, m;
  while (cin >> n >> m) {
    cout << solve(n, m) << endl;
  }
  
  return 0;
}
