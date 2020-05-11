#include <iostream>

using namespace std;

int solve(int a, int b, int n, int m)
{
  int mod = 1;
  for (int i = 0; i < m; i++) {
    mod *= 10;
  }


  int r[2][2] = { {1, 0}, {0, 1} };
  int x[2][2] = { {0, 1}, {1, 1} };
  int t[2][2];

  while (n > 0) {
    if (n & 0x01) {
      n--;
      t[0][0] = r[0][0]*x[0][0] + r[0][1]*x[1][0];
      t[0][1] = r[0][0]*x[0][1] + r[0][1]*x[1][1];
      t[1][0] = r[1][0]*x[0][0] + r[1][1]*x[1][0];
      t[1][1] = r[1][0]*x[0][1] + r[1][1]*x[1][1];
      for (int i = 0; i < 2; i++) {
	for (int j = 0; j < 2; j++) {
	  r[i][j] = t[i][j] % mod;
	}
      }
    } else {
      n >>= 1;
      t[0][0] = x[0][0]*x[0][0] + x[0][1]*x[1][0];
      t[0][1] = x[0][0]*x[0][1] + x[0][1]*x[1][1];
      t[1][0] = x[1][0]*x[0][0] + x[1][1]*x[1][0];
      t[1][1] = x[1][0]*x[0][1] + x[1][1]*x[1][1];
      for (int i = 0; i < 2; i++) {
	for (int j = 0; j < 2; j++) {
	  x[i][j] = t[i][j] % mod;
	}
      }
    }
  }

  return (r[0][0]*a + r[0][1]*b) % mod;
}

int main(void)
{
  int T;
  cin >> T;
  while (T--) {
    int a, b, n, m;
    cin >> a >> b >> n >> m;
    cout << solve(a, b, n, m) << endl;
  }
  return 0;
}
