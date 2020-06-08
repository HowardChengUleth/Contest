// This is a somewhat unsatisfying problem...basically grab the code
// library routine for factoring large integers and that is all you need.


// Gives the prime factorization of natural numbers (Uses probability)
//
// Author: Darcy Best
// Date  : January 7, 2010
//
// This should be used for factoring large integers. If you're
//   dealing with are small integers (N < 2^31), this is going
//   overboard. -- The normal sieve of Sieve of Eratosthenes is
//   usually good even for values up to 2^40.
//
// This implementation should only be used if you have numbers
//   larger than 2^40 (10^12) to factor.
//
// Notes:
//    - You need to handle N < 2 separately.
//    - Uses Miller-Rabin Primality Test
//         - This is a probabilistic test, there is a (1/4)^K
//             probability that a composite will return prime.
//             (K = 10 or 15 should be reasonably reliable).
//    - Uses Pollard's Rho algorithm to factor composites.
//         - I have also added Brent's improvement
//    - This program writes a number as a product of its primes,
//         with normal exponents (ie. "60 = 2^2 * 3 * 5")

#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

typedef long long int ll;

const ll MAX_NUM = 1e16;
const ll CB_RT = ll(pow(1.0*MAX_NUM,1.0/3)) + 2;
vector<ll> primes;
ll numPrimes;
ll c = 2;
const ll K = 10;

set<ll> lgPrimes;
map<ll,ll> semiPrimes;

ll gcd(ll a,ll b){
  ll r;
  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  return a;
}

ll mult_mod(ll x,ll y,ll n){
  ll res = 0;
  while(y){
    if(y % 2){
      y--;
      res += x;
      if(res >= n)
	res -= n;
    } else {
      x <<= 1;
      y >>= 1;
      if(x >= n)
	x -= n;
    }
  }
  return res;
}

ll fast_exp_mod(ll b, ll n,ll m){
  ll res = 1;
  ll x = b;
	
  while (n) {
    if (n % 2) {
      n--;
      res = mult_mod(res,x,m);
    } else {
      n >>= 1;
      x = mult_mod(x,x,m);
    }
  }
	
  return res;
}

void genSmallPrimes(){
  bool isPrime[CB_RT+7];
  for(int i=3;i<CB_RT;i+=2)
    isPrime[i] = true;
	
  primes.clear();
  primes.push_back(2);
	
  int i;
  for(i=3;i*i<CB_RT;i+=2)
    if(isPrime[i]){
      primes.push_back(i);
      for(int j=i*i;j<CB_RT;j+=(2*i))
	isPrime[j] = false;
    }
	
  for(;i<CB_RT;i+=2)
    if(isPrime[i])
      primes.push_back(i);
  numPrimes = primes.size();
}

ll F(ll x,ll n){
  x = mult_mod(x,x,n);
  x -= c;
  return (x < 0 ? x + n : x);
}

ll pollardRho(ll n){
  ll b,g,x,y,z;
 newC:
  c++;
  g = b = x = 1;
  while(g == 1){
    z = 1;
    y = x;
    for(ll i=0;i<b;i++){
      x = F(x,n);
      z = mult_mod(z,abs(x-y),n);
    }
    g = gcd(z,n);
    b <<= 1;
  }
  if(g == n || g == 0)
    goto newC;
	
  c = 2;
  return g;
}

bool miller(ll n){
  ll d = n-1;
  ll s = 0,a,x;
  while(d % 2 == 0){
    d >>= 1;
    s++;
  }
  for(int i=0;i<K;i++){
    a = (rand() % (n-2)) + 2; // [2,n-1];
    x = fast_exp_mod(a,d,n);
    if(x == 1 || x == n-1)
      continue;
    for(ll r=1;r<s;r++){
      x = mult_mod(x,x,n);
      if(x == 1)
	return false;
      if(x == n-1)
	goto nextK;
    }
    return false;
  nextK:;
  }
  return true;
}

void printEntry(bool& printed,ll prime,int ex){
  if(!printed)
    printed = true;
  else
    cout << " * ";
  cout << prime;
  if(ex > 1)
    cout << "^" << ex;
}

vector<ll> factor(ll x){
  vector<ll> v;
  if (x == 1) {
    v.push_back(1);
    return v;
  }

  for(int i=0;i<numPrimes;i++)
    if(x % primes[i] == 0){
      int ex = 0; // Exponent
      do{
	x /= primes[i];
	ex++;
      } while(x % primes[i] == 0);
      for (int j = 0; j < ex; j++) {
	v.push_back(primes[i]);
      }
    }
  if(x == 1){
    return v;
  }
  
  // lgPrimes and semiPrimes are useful if there
  //   is a lot repetition of large primes/semi-primes
  //   in the test data
  if(lgPrimes.find(x) != lgPrimes.end()){
    v.push_back(x);
    return v;
  }
  
  if(semiPrimes.find(x) != semiPrimes.end()){
    ll lgFac = semiPrimes[x];
    v.push_back(x/lgFac);
    v.push_back(lgFac);
    return v;
  }
	
  if(miller(x)){ // if x is prime
    v.push_back(x);
    lgPrimes.insert(x);
    return v;
  }
	
  // Pollard's Rho does not work well with squares,
  //   so we'll check for it manually.
  ll sqrtX = ll(sqrt(x) + 0.1);
  if(sqrtX*sqrtX == x){
    v.push_back(sqrtX);
    v.push_back(sqrtX);
    return v;
  }
	
  ll smFac = pollardRho(x);
  ll lgFac = x/smFac;
  if(lgFac < smFac)
    swap(smFac,lgFac);
  v.push_back(smFac);
  v.push_back(lgFac);
  semiPrimes[x] = lgFac;

  return v;
}

int main(){
  genSmallPrimes();
  srand((unsigned int) time(NULL));

  ll N;
  while(cin >> N && N > 0){
    auto v = factor(N);
    sort(begin(v), end(v));
    for (auto x : v) {
      cout << "    " << x << endl;
    }
    cout << endl;
  }
  return 0;
}
