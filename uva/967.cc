#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

const int MAX_N = 1000000;

bool prime[MAX_N];
int circ[MAX_N];    // 0 = false, 1 = true, 2 = calculating, -1 = unknown
int ccount[MAX_N];

void compute_circ(int n)
{
  if (circ[n] == 0 || circ[n] == 1) return;
  if (!prime[n]) {
    circ[n] = 0;
    return;
  }

  if (circ[n] == 2) {
    circ[n] = 1;
    return;
  }

  circ[n] = 2;
  int d = 0;
  int nn = n;
  int m = 1;
  while (nn > 0) {
    nn /= 10;
    d++;
    m *= 10;
  }
  m /= 10;
  nn = (n % 10) * m + (n / 10);
  compute_circ(nn);
  circ[n] = circ[nn];
}

void init()
{
  fill(prime, prime+MAX_N, true);
  prime[0] = prime[1] = false;
  for (long long p = 2; p < MAX_N; p++) {
    if (!prime[p]) continue;
    for (long long k = p*p; k < MAX_N; k += p) {
      prime[k] = false;
    }
  }

  fill(circ, circ+MAX_N, -1);
  for (int n = 100; n < 1000000; n++) {
    compute_circ(n);
  }

  partial_sum(circ, circ+MAX_N, ccount);
}

int main()
{
  init();
  
  int i, j;
  while (cin >> i >> j && i != -1) {
    int ans = ccount[j] - ccount[i-1];
    if (ans == 0) {
      cout << "No Circular Primes." << endl;
    } else if (ans == 1) {
      cout << "1 Circular Prime." << endl;
    } else {
      cout << ans << " Circular Primes." << endl;
    }
  }
  return 0;
}
