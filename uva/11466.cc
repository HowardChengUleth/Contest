#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

typedef long long ll;

const int MAX = 31622776;
bitset<MAX+1> isprime;
vector<ll> primes;


ll largestprime(ll n)
{
  ll ans = 0;
  for (vector<ll>::const_iterator it = primes.begin();
       it != primes.end() && (*it)*(*it) <= n;
       ++it) {
    while (n % *it == 0) {
      n /= *it;
      ans = *it;
    }
  }
  if (n > 1) {
    ans = n;
  }
  return ans;
}

int main(void)
{
  isprime.reset(); isprime.flip();
  isprime.set(0, false); isprime.set(1, false);
  for (ll i = 2; i <= MAX; i++) {
    if (isprime.test(i)) {
      for (ll j = i*i; j <= MAX; j += i) {
	isprime.set(j, false);
      }
      primes.push_back(i);
    }
  }

  ll N;
  while (cin >> N && N) {
    if (N < 0) {
      N *= -1;
    }

    ll best = -1;
    ll count = 0;
    for (vector<ll>::const_iterator it = primes.begin();
	 it != primes.end() && (*it)*(*it) <= N;
	 ++it) {
      if ((N % *it) == 0) {
	count++;
	ll temp = largestprime(N/(*it));
	best = max(best, max(*it, temp));
	if (temp != *it) {
	  count++;
	}
      }
    }
    if (count == 1) {
      best = -1;
    }
    cout << best << endl;
  }
  return 0;
}
