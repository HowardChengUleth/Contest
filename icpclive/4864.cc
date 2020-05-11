//
// We only have 63-bit numbers, so whatever number we get there are at most
// 63 1's.  We will work out the value of K based on how many 1's you have,
// and then we will try to figure out how many numbers in a range has that
// many 1's.

#include <iostream>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;

// ans[b] = number of steps to get to 1 if N_0 = b
int ans[64];

// binomial[n][k]
ull binom[64][64];

void precompute()
{
  for (ull b = 1; b <= 63; b++) {
    ans[b] = 0;
    ull N = b;
    while (N > 1) {
      ull count = 0;
      while (N > 0) {
	if (N & 1) count++;
	N >>= 1;
      }
      N = count;
      ans[b]++;
    }
  }

  for (int n = 0; n <= 63; n++) {
    binom[n][0] = binom[n][n] = 1;
    for (int k = 1; k < n; k++) {
      binom[n][k] = binom[n-1][k] + binom[n-1][k-1];
    }
  }
}

// count the number of integers in [0, hi] with exactly b 1's
ull count_b_ones(ull hi, int b)
{
  if (hi == 0) {
    if (b > 0) {
      return 0;
    } else {
      return 1;
    }
  }
  if (b == 0) {
    return 1;
  }
  
  int bit_len = 0;
  ull x = hi;
  while (x > 0) {
    bit_len++;
    x >>= 1;
  }

  ull ans = 0;

  // all numbers where MSB = 0
  if (b <= bit_len-1) {
    ans += binom[bit_len-1][b];
  }

  //  + all numbers where MSB = 1
  ans += count_b_ones(hi - (1ULL << (bit_len-1)), b-1);

  return ans;
}

ull count_b_ones(ull lo, ull hi, int b)
{
  return count_b_ones(hi, b) - count_b_ones(lo-1, b);
}

int main(void)
{
  precompute();
  ull lo, hi;
  int k;
  while (cin >> lo >> hi >> k && (lo || hi || k)) {
    ull total = 0;

    // handle 1 separately
    if (lo <= 1 && 1 <= hi && k == 0) {
      total++;
    }

    lo = max(2ULL, lo);
    for (int b = 1; b <= 63 && lo <= hi; b++) {
      if (ans[b] != k-1) continue;
      total += count_b_ones(lo, hi, b);
    }
    cout << total << endl;
  }
  return 0;
}
