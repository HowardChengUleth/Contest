#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double log_n_fact[100001];

int main(void)
{
  int i, n, g;
  double ans;

  log_n_fact[0] = log_n_fact[1] = 0;
  for (i = 2; i <= 100000; i++) {
    log_n_fact[i] = log_n_fact[i-1] + log(i);
  }

  cin >> n;
  while (n-- > 0) {
    cin >> g;
    ans = 1-exp(log_n_fact[g-2] - 2*log_n_fact[(g-2)/2] - (g-2)*log(2));
    cout << fixed << setprecision(4) << ans << endl;
  }
  return 0;
}
