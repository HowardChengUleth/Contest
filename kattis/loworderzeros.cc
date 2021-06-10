#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAX = 1000000;

vector<ll> primes;
bool sieve[MAX+1] = {0};

void init()
{
  fill(sieve+2, sieve+MAX+1, true);
  for (ll i = 2; i <= MAX; i++) {
    if (!sieve[i]) continue;
    for (ll j = i*i; j <= MAX; j += i) {
      sieve[j] = false;
    }
    primes.push_back(i);
  }
}

int find_power(int N, int p)
{
  long long ans = 0, pp = p;
  
  while (N/pp > 0) {
    ans += N/pp;
    pp *= p;
  }
  return ans;
}

int powmod(int b, int k)
{
  if (k == 0) {
    return 1;
  }

  if (k % 2 == 1) {
    return (b * powmod(b, k-1)) % 10;
  }

  int b2 = powmod(b, k/2);
  return (b2*b2) % 10;
}

int lastdigit(int N)
{
  int p2, p5;
  int ans = 1;

  /* first find powers of 2, 5 */
  p2 = find_power(N,2);
  p5 = find_power(N,5);

  ans = (ans * powmod(2, p2-p5)) % 10;
  
  for (auto p : primes) {
    if (p == 2 || p == 5) continue;
    int e = find_power(N, p);
    if (!e) break;
    ans *= powmod(p,e);
    ans %= 10;
  }

  return ans;
}

int main(void)
{
  int N;

  init();
  while (cin >> N && N) {
    cout << lastdigit(N) << endl;
  }
  return 0;
}
