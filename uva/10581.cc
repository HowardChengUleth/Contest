/* @JUDGE_ID: 1102NT 10581 C++ "" */

#include <iostream>

using namespace std;

const int max_n = 10, max_m = 220;

void print(long long P[max_n+1][max_m+1], int n, int m, int k, int base)
{
  if (n == 1) {
    cout << m+base << endl;
    return;
  }

  int i;
  int count = 0, old_count;

  for (i = 1; i <= m && m-i-(n-1)*(i-1) >= 0; i++) {
    old_count = count;
    count += P[n-1][m-i-(n-1)*(i-1)];
    if (count >= k) {
      break;
    }
  }
  cout << i+base << endl;
  print(P, n-1, m-i-(n-1)*(i-1), k - old_count, base+i-1);
}

int main(void)
{
  int n, m, k;
  long long P[max_n+1][max_m+1];

  for (n = 0; n <= max_n; n++) {
    P[n][0] = 0;
  }
  for (m = 1; m <= max_m; m++) {
    P[0][m] = 0;
    P[1][m] = 1;
  }
  for (n = 2; n <= max_n; n++) {
    for (m = 1; m <= max_m; m++) {
      P[n][m] = 0;
      for (k = 1; k <= m && m-k-(n-1)*(k-1) >= 0; k++) {
	P[n][m] += P[n-1][m-k-(n-1)*(k-1)];
      }
    }
  }

  int c;
  cin >> c;
  while (c-- > 0) {
    cin >> m >> n >> k;
    print(P, n, m, k, 0);
  }

  return 0;
}
