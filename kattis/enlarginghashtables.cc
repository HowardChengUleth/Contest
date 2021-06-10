#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAX = 100000;

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

bool isprime(int n)
{
  if (n <= MAX) {
    return sieve[n];
  }
  for (auto p : primes) {
    if (p*p > n) {
      return true;
    }
    if (n % p == 0) {
      return false;
    }
  }

  assert(false);
}

void solve(int n)
{
  int ans = 2*n+1;
  while (!isprime(ans)) {
    ans += 2;
  }
  cout << ans;
  if (!isprime(n)) {
    cout << " (" << n << " is not prime)";
  }
  cout << endl;
}

int main()
{
  init();

  int n;
  while (cin >> n && n) {
    solve(n);
  }
  
  return 0;
}
