#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000009;

int main()
{
  ll K, W;
  
  cin >> K >> W;

  ll big_side = (W + (W*2)/K) % MOD;
  ll big_sq = (big_side * big_side) % MOD;

  ll complete = W/K;
  ll ceil = (K+1)/2;
  ll floor = K/2;
  
  ll even = 0;
  ll odd = 0;
  
  if (complete > 0) {
    even = (((ceil * complete) % MOD) * (complete-1)) % MOD;
    odd = ((((floor * complete) % MOD) * (complete-1)) % MOD +
	   (floor * complete) % MOD) % MOD;
  }
  
  ll rem = W % K;
  if (rem > 0) {
    ll width = min(ceil, rem);
    even = (even + (width * complete * 2) % MOD) % MOD;
  }
  rem -= ceil;
  if (rem > 0) {
    ll width = min(floor, rem);
    odd = (odd + (width * (complete * 2 + 1)) % MOD) % MOD;
  }
  
  ll remove = (4*(even + odd))% MOD;
  big_sq = (big_sq + (MOD - remove)) % MOD;

  cout << big_sq << endl;

  return 0;
}
