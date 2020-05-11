#include <iostream>

using namespace std;
long long binom[21][21];

int main(void)
{
  for (int n = 0; n <= 20; n++) {
    binom[n][n] = binom[n][0] = 1;
    for (int k = 1; k < n; k++) {
      binom[n][k] = binom[n-1][k-1] + binom[n-1][k];
    }
  }

  int n;
  bool first = true;
  while (cin >> n) {
    if (!first) cout << endl;
    cout << binom[2*n][n]/(n+1) << endl;
    first = false;
  }
  return 0;
}
