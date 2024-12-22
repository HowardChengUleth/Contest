#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct RNG
{
  ll secret;

  RNG(ll seed)
    : secret(seed)
  {
  }
  
  void mix(ll val)
  {
    secret ^= val;
  }

  void prune()
  {
    const ll MOD = 16777216;
    secret %= MOD;
  }
  
  ll next()
  {
    mix(secret * 64);
    prune();

    mix(secret / 32);
    prune();

    mix(secret * 2048);
    prune();

    return secret;
  }

  ll value() const
  {
    return secret;
  }
};

int main()
{
  ll seed;
  ll ans = 0;
  while (cin >> seed) {
    RNG rng(seed);

    for (int i = 0; i < 2000; i++) {
      rng.next();
    }
    ans += rng.value();
  }

  cout << ans << endl;
  
  return 0;
}
