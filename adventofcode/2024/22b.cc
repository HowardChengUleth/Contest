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

vector<ll> seed;
void read_seed()
{
  ll x;
  while (cin >> x) {
    seed.push_back(x);
  }
}

typedef tuple<ll,ll,ll,ll> ti4;
map<ti4, ll> total;

ostream &operator<<(ostream &os, ti4 t)
{
  os << get<0>(t) << ' ';
  os << get<1>(t) << ' ';
  os << get<2>(t) << ' ';
  os << get<3>(t) << ' ';

  return os;
}

void generate(ll seed)
{
  RNG rng(seed);

  map<ti4, ll> price;
  ti4 change;
  
  ll prev = seed % 10;
  for (int i = 0; i < 2000; i++) {
    ll val = rng.next() % 10;
    ll diff = val - prev;
    get<0>(change) = get<1>(change);
    get<1>(change) = get<2>(change);
    get<2>(change) = get<3>(change);
    get<3>(change) = diff;
    if (i >= 3 && price.find(change) == price.end()) {
      price[change] = val;
      //      cout << "i = " << i << ": " << change << ' ' << val << endl;
    }
    
    prev = val;
  }
  //  cout << "========" << endl;

  for (auto [c, p] : price) {
    total[c] += p;
  }
}

int main()
{
  read_seed();

  for (auto s : seed) {
    generate(s);
  }

  ll ans = 0;
  for (auto [c, p] : total) {
    ans = max(ans, p);
  }

  cout << ans << endl;
  
  
  return 0;
}
