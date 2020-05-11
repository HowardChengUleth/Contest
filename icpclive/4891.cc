#include <iostream>

using namespace std;

unsigned long long binom[99][99];

int main(void)
{
  for (int n = 0; n <= 98; n++) {
    binom[n][0] = binom[n][n] = 1;
    for (int k = 1; k < n; k++) {
      binom[n][k] = binom[n-1][k] + binom[n-1][k-1];
    }
  }

  int x, y;
  int case_num = 1;
  while (cin >> x >> y && (x || y)) {
    cout << "Case " << case_num++ << ": " << binom[x+y-2][x-1] << endl;
  }

  return 0;
}
