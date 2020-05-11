// idea:
//
// if f(x,y) = # of (s,t) such that gcd(s,t) = 1, 1 <= s <= x, 1 <= t <= y,
// then the answer we seek is f(b,d) - f(a-1,d) - f(b,c-1) + f(a-1,c-1)
//
// how to compute f(x,y)?
//
// For each prime p, the number of pairs (s,t) such that p divides both
// s and t would be (x/p)*(y/p).  But those that are divisible by two
// primes (including repeated ones) will be double counted, those divisible
// by three primes will be triple counted, etc.  So we need some kind of
// inclusion-exclusion, and it turns out that the mobius function will give
// the right sign.


#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 10000000;
int mu[MAX+1];
int primediv[MAX+1];
bool sq[MAX+1] = {false};

void init()
{
  mu[1] = 1;
  for (ll i = 2; i <= MAX; i++) {
    if (sq[i]) {
      mu[i] = 0;
    } else if (primediv[i]) {
      mu[i] = (primediv[i] % 2 == 0) ? 1 : -1;
    } else {
      mu[i] = -1;
    }
    if (primediv[i]) continue;
    for (ll j = 2*i; j <= MAX; j += i) {
      primediv[j]++;
    }
    for (ll j = i*i; j <= MAX; j += i*i) {
      sq[j] = true;
    }
  }
}

ll f(ll x, ll y)
{
  ll sum = 0;
  for (ll d = 1; d <= min(x,y); d++) {
    sum += mu[d] * (x/d) * (y/d);
  }
  return sum;
}

int main()
{
  init();

  int a, b, c, d;
  cin >> a >> b >> c >> d;

  cout << f(b,d) - f(a-1,d) - f(b,c-1) + f(a-1,c-1) << endl;
  
  return 0;
}
