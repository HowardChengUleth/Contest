#include <iostream>

using namespace std;

const int MOD = 1000007;

int binom[20*20+1][20*20+1];

void init()
{
  for (int n = 0; n <= 20*20; n++) {
    binom[n][0] = binom[n][n] = 1;
    for (int k = 1; k < n; k++) {
      binom[n][k] = (binom[n-1][k] + binom[n-1][k-1]) % MOD;
    }
  }
}

int b(int n, int k)
{
  if (n < 0 || n < k) return 0;
  return binom[n][k];
}

void solve()
{
  int m, n, k;
  cin >> m >> n >> k;

  int total = b(m*n, k);
  int neg = 2*(b((m-1)*n, k) + b(m*(n-1), k)) % MOD;
  neg = (neg -
	 (b((m-2)*n, k) + b(m*(n-2), k) + 4*b((m-1)*(n-1), k))
	 % MOD) % MOD;
  neg = (neg + 2*b((m-2)*(n-1), k) + 2*b((m-1)*(n-2), k)) % MOD;
  neg = (neg - b((m-2)*(n-2),k)) % MOD;

  total -= neg;
  total %= MOD;
  if (total < 0) total += MOD;
  cout << total << endl;
}

int main()
{
  init();

  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": ";
    solve();
  }
  return 0;
}
