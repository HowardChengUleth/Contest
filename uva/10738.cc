#include <iostream>
#include <numeric>
#include <algorithm>
#include <iomanip>

using namespace std;

int mu[1000001];
bool prime[1000001];
bool init[1000001];
int M[1000001];

int main(void)
{
  fill(prime+2, prime+1000001, true);
  fill(mu+2, mu+1000001, 0);

  mu[0] = 0;
  mu[1] = 1;
  init[0] = init[1] = true;

  for (long long  p = 2; p <= 1000000; p++) {
    if (!prime[p]) continue;
    mu[p] = -1;
    init[p] = true;
    
    for (long long i = 2*p; i <= 1000000; i += p) {
      prime[i] = false;
      if (mu[i] == 0 && !init[i]) {
	mu[i] = -1;
      } else {
	mu[i] *= -1;
      }
      init[i] = true;
    }

    for (long long e = p*p; e <= 1000000; e *= p) {
      for (long long i = e; i <= 1000000; i += e) {
	mu[i] = 0;
	init[i] = true;
      }
    }
  }

  partial_sum(mu, mu+1000001, M);

  int n;
  while (cin >> n && n) {
    cout << setw(8) << n << setw(8) << mu[n] << setw(8) << M[n] << endl;
  }

  return 0;
}
