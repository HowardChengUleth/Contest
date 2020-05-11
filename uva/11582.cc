// Fibonacci numbers are completely determined by the last two terms.
// Since we are only interested in remainders mod n, we only have
// n^2 possible pairs of last two terms, so it must cycle after n^2
// steps.  In fact the cycle lengths are much shorter than n^2 but
// that's hard to prove.
//
// Once we have the cycle length, then we just want to compute
// f(a^b mod cycle length) mod n
//
// NOTE: fibonacci numbers can be computed both forward and backward given
// any two terms.  So if there is a cycle then there must be no "precycle"
// before entering it.

#include <iostream>
#include <algorithm>

using namespace std;

unsigned long long fast_exp_mod(unsigned long long b, unsigned long long n, 
				unsigned long long m)
{
  unsigned long long res = 1;
  unsigned long long x = b % m;

  while (n > 0) {
    if (n & 0x01) {
      n--;
      res = (res * x) % m;
    } else {
      n >>= 1;
      x = (x * x) % m;
    }
  }

  return res;
}

int cycle_len[1001];

void compute_cycle(int n)
{
  // already computed
  if (cycle_len[n] >= 0) return;

  int prev2 = 0, prev1 = 1 % n;
  int step = 0;
  while (!(prev2 == 0 && prev1 == 1 % n && step > 0)) {
    int curr = (prev2 + prev1) % n;
    prev2 = prev1;
    prev1 = curr;
    step++;
  }

  cycle_len[n] = step;
}

void do_case(void)
{
  unsigned long long a, b;
  int n;
  cin >> a >> b >> n;

  compute_cycle(n);

  int order;
  order = fast_exp_mod(a, b, cycle_len[n]);

  // take care of base cases
  if (order == 0) {
    cout << 0 << endl;
    return;
  } else if (order == 1) {
    cout << 1 % n << endl;
    return;
  }

  int prev2 = 0, prev1 = 1 % n;
  int step = 2;
  int curr = (prev2 + prev1) % n;
  while (step < order) {
    prev2 = prev1;
    prev1 = curr;
    curr = (prev2 + prev1) % n;
    step++;
  }
  cout << curr << endl;
}

int main(void)
{
  fill(cycle_len, cycle_len+1001, -1);

  int t;
  cin >> t;
  while (t-- > 0) {
    do_case();
  }
  return 0;
}
