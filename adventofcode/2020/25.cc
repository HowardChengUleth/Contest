#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

//ll key[2] = { 5764801, 17807724 };
ll key[2] = {10943862, 12721030};

ll mod = 20201227;

long long fast_exp_mod(long long b, long long n, long long m) {
  if (n == 0) return 1 % m;
  if (n % 2 == 0) return fast_exp_mod((b*b)%m, n/2, m);
  return (fast_exp_mod(b, n-1, m) * b) % m;
}

// Discrete Log Solver -- O(sqrt(p))
ll discrete_log(ll p,ll b,ll n){
  map<ll,ll> M; ll jump = ceil(sqrt(p));
  for(int i=0;i<jump && i<p;i++) M[fast_exp_mod(b,i,p)] = i+1;
  for(int i=0;i<p-1;i+=jump){
    ll x = (n*fast_exp_mod(b,p-i-1,p)) % p;
    if(M.find(x) != M.end()) return (i+M[x]-1) % (p-1);
  }
  return -1;
}


int main()
{
  ll loop[2];
  for (int i = 0; i < 2; i++) {
    loop[i] = discrete_log(mod, 7, key[i]);
    cout << loop[i] << endl;
  }

  cout << "A = " << fast_exp_mod(key[0], loop[1], mod) << endl;

  return 0;
}
