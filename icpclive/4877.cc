#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

typedef unsigned long long ull;

ull ans[65];

// aux[i][j] = # of sequences of length i ending with digit j
ull aux[65][10];

int main(void)
{
  ans[1] = 10;
  fill(aux[1], aux[1]+10, 1);

  for (int N = 2; N <= 64; N++) {
    for (int d = 0; d < 10; d++) {
      aux[N][d] = accumulate(aux[N-1], aux[N-1] + d + 1, 0ULL);
    }
    ans[N] = accumulate(aux[N], aux[N] + 10, 0ULL);
  }

  int P;
  cin >> P;
  while (P--) {
    int id, N;
    cin >> id >> N;
    cout << id << ' ' << ans[N] << endl;
  }
  return 0;
}
