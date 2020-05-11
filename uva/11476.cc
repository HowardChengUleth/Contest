#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <set>
#include <cmath>

using namespace std;

// Note: N < 2^54

typedef unsigned int uint;
typedef unsigned long long ull;

// cache for primes
set<ull> primes;

const int MILLER_RABIN_TRIALS = 10;
ull gcd(ull a, ull b)
{
  while (b != 0) {
    ull r = a % b;
    a = b;
    b = r;
  }
  return a;
}

ull mulmod(ull a, ull b, ull N)
{
  // write a = ah * 2^27 + al
  //       b = bh * 2^27 + bl
  //
  // then a*b = (ah*bh) 2^54 + (ah*bl+bh*al) 2^27 + al*bl

  ull ah = (a >> 27), al = (a & 0x7FFFFFF);
  ull bh = (b >> 27), bl = (b & 0x7FFFFFF);

  ull c0 = (al*bl) % N;
  ull c1 = (ah*bl + bh*al) % N;
  ull c2 = (ah*bh) % N;
  c2 <<= 9; c2 %= N;
  c2 <<= 9; c2 %= N;
  c2 <<= 9; c2 %= N;
  c2 = (c2+c1) % N;
  c2 <<= 9; c2 %= N;
  c2 <<= 9; c2 %= N;
  c2 <<= 9; c2 %= N;
  c2 = (c2+c0) % N;
  return c2;
}

ull expmod(ull a, ull k, ull N)
{
  ull res = 1;
  ull x = a;
  while (k > 0) {
    if (k & 0x01) {
      k--;
      res = mulmod(res, x, N);
    } else {
      k >>= 1;
      x = mulmod(x, x, N);
    }
  }
  return res;
}

// a version of Miller-Rabin test
bool isprime(ull N)
{
  if (N == 1 || (N & 0x01) == 0) {
    return false;
  }

  if (primes.find(N) != primes.end()) {
    return true;
  }

  // write N-1 = 2^s * d
  int s = 0;
  ull d = N-1;
  while ((d & 0x01) == 0) {
    d >>= 1;
    s++;
  }
  
  for (int k = 0; k < MILLER_RABIN_TRIALS; k++) {
    // not completely random because rand() is only up to 32-bit...
    ull a = (ull)rand() % (N-2) + 2;
    ull x = expmod(a, d, N);
    if (x == 1 || x == N-1) continue;
    int r;
    for (r = 0; r < s-1; r++) {
      x = mulmod(x, x, N);
      if (x == 1) {
	return false;
      } else if (x == N-1) {
	break;
      }
    }
    if (r < s-1) {
      continue;
    }
    return false;
  }
  
  primes.insert(N);
  return true;
}

ull f(ull x, ull C, ull N)
{
  x = mulmod(x, x, N);
  x += C;
  if (x >= N) {
    x -= N;
  }
  return x;
}

void factorhard(ull N, vector<ull> &factors)
{
  if (N == 1) {
    // no need to add any factors
    return;
  }
  
  if (isprime(N)) {
    factors.push_back(N);
    return;
  }

  // use pollard's rho algorithm, with Brent's variation
  ull C = 3;

  while (true) {
    ull x = 2;
    ull y = f(x, C, N);
    ull power = 1, lam = 1;
    ull d = gcd(((x >= y) ? (x-y) : (y-x)), N);
    int times = 0;
    while (d == 1 && times <= 50) {
    if (power == lam) {
      // new power of 2
      x = y;
      power <<= 1;
      times++;
      lam = 0;
    }
    y = f(y, C, N);
    lam++;
    d = gcd(((x >= y) ? (x-y) : (y-x)), N);
    }
    if (d != 1 && d != N) {
      factorhard(d, factors);
      factorhard(N/d, factors);
      return;
    }
    C++;
  }
}

void factor(ull N, vector<ull> &factors)
{
  while ((N & 0x01) == 0) {
    N >>= 1;
    factors.push_back(2);
  }
  while ((N % 3) == 0) {
    N /= 3;
    factors.push_back(3);
  }
  while ((N % 5) == 0) {
    N /= 5;
    factors.push_back(5);
  }
  /*
  ull root = sqrt(N);
  bool square = (root*root == N);
  
  if (square) {
    factorhard(root, factors);
    for (int i = factors.size()-1; i >= 0; i--) {
      factors.push_back(factors[i]);
    }
    } else*/

  if (N > 1) {
    factorhard(N, factors);
  }
}

void print(vector<ull> &factors)
{
  sort(factors.begin(), factors.end());
  
  vector<ull>::size_type i = 0, j = 0;
  bool first = true;
  for (; i < factors.size(); i = j) {
    for (j = i; j < factors.size() && factors[i] == factors[j]; j++)
      ;
    if (!first) {
      cout << " * ";
    }
    cout << factors[i];
    if (j - i > 1) {
      cout << '^' << j-i;
    }
    first = false;
  }
  cout << endl;
}

void check(ull N, vector<ull> &factors)
{
  ull ans = 1;
  for (unsigned int i = 0; i < factors.size(); i++) {
    ans *= factors[i];
  }
  if (N != ans) {
    cout << "Bad" << endl;
    exit(1);
  }
}

int main(void)
{
  int T;
  srand(time(0));
  primes.insert(3);
  primes.insert(5);
  primes.insert(7);

  cin >> T;
  while (T-- > 0) {
    ull N;

    cin >> N;
    cout << N << " = ";

    vector<ull> factors;        // list of factors
    factor(N, factors);
    print(factors);
    check(N, factors);
  }
  return 0;
}
