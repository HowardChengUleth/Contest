#include <iostream>

using namespace std;

long long ans[51][51][51];

long long f(int n, int k, int m)
{
  if (n <= 0) {
    return 0;
  }
  
  if (ans[n][k][m] >= 0) {
    return ans[n][k][m];
  }

  if (k == 1) {
    return (ans[n][k][m] = (n <= m) ? 1 : 0);
  }

  ans[n][k][m] = 0;
  for (int w = 1; w <= m && w <= n; w++) {
    ans[n][k][m] += f(n-w, k-1, m);
  }
  return ans[n][k][m];

}

int main(void)
{
  int n, k, m;

  for (int i = 0; i <= 50; i++) {
    for (int j = 0; j <= 50; j++) {
      for (int k = 0; k <= 50; k++) {
	ans[i][j][k] = -1;
      }
    }
  }
  
  while (cin >> n >> m >> k) {
    cout << f(n, m, k) << endl;
  }
  return 0;
}
