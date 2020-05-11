#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

bool is_prime[1000001];
int prime_list[1000000];
int num_primes = 0;
int num_prime[1000001];
double ans[1000001];

void compute(int N)
{
  if (ans[N] >= 0.0) {
    return;
  }

  if (is_prime[N]) {
    double prob = (double)(num_prime[N] - 1) / num_prime[N];
    ans[N] = 1.0/(1.0-prob);
    return;
  }

  ans[N] = 0.0;
  int count = 0;
  for (int p = 0; p < num_primes; p++) {
    int prime = prime_list[p];
    if (N % prime != 0) continue;
    count++;
    compute(N / prime);
    ans[N] += (1.0/num_prime[N]) * (1 + ans[N / prime]);
  }

  double prob = (double)(num_prime[N] - count) / num_prime[N];
  ans[N] = (ans[N] + prob)/(1.0-prob);
}

int main(void)
{
  fill(is_prime, is_prime+1000001, true);
  is_prime[0] = is_prime[1] = false;
  for (int k = 2; k <= 1000000; k++) {
    if (!is_prime[k]) continue;
    prime_list[num_primes++] = k;
    for (int j = 2*k; j <= 1000000; j += k) {
      is_prime[j] = false;
    }
  }

  num_prime[0] = 0;
  for (int i = 1; i <= 1000000; i++) {
    num_prime[i] = (is_prime[i] ? 1 : 0) + num_prime[i-1];
  }

  ans[1] = 0.0;
  fill(ans+2, ans+1000001, -1.0);

  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    int N;
    cin >> N;
    compute(N);
    cout << "Case " << i << ": " << fixed << setprecision(10) 
	 << ans[N] << endl;
  }

  return 0;
}
