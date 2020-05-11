#include <iostream>
#include <algorithm>

using namespace std;

typedef int Mat[15][15];

// C = A*B
void mult(Mat C, Mat A, Mat B, int d, int m)
{
  for (int i = 0; i < d; i++) {
    for (int j = 0; j < d; j++) {
      C[i][j] = 0;
      for (int k = 0; k < d; k++) {
	C[i][j] += (A[i][k] * B[k][j]) % m;
	C[i][j] %= m;
      }
    }
  }
}

// A *= B, A can be the same as B
void mult(Mat A, Mat B, int d, int m)
{
  Mat C;
  mult(C, A, B, d, m);
  for (int i = 0; i < d; i++) {
    copy(C[i], C[i]+d, A[i]);
  }
}

void pow(Mat A, int d, int n, int m)
{
  Mat X;
  for (int i = 0; i < d; i++) {
    copy(A[i], A[i]+d, X[i]);
  }
  for (int i = 0; i < d; i++) {
    for (int j = 0; j < d; j++) {
      A[i][j] = (i == j);
    }
  }

  while (n > 0) {
    if (n & 1) {
      n--;
      mult(A, X, d, m);
    } else {
      n >>= 1;
      mult(X, X, d, m);
    }
  }
}

bool solve()
{
  int d, n, m;
  cin >> d >> n >> m;
  if (!d && !n && !m) return false;

  Mat A;
  for (int i = 0; i < d-1; i++) {
    for (int j = 0; j < d; j++) {
      A[i][j] = (j == i+1);
    }
  }

  for (int j = d-1; j >= 0; j--) {
    cin >> A[d-1][j];
    A[d-1][j] %= m;
  }
  
  int f[15];
  for (int i = 0; i < d; i++) {
    cin >> f[i];
    f[i] %= m;
  }

  int ans = 0;
  if (n <= d) {
    ans = f[n-1];
  } else {
    pow(A, d, n-d, m);
    for (int i = 0; i < d; i++) {
      ans += (A[d-1][i]*f[i]) % m;
      ans %= m;
    }
  }

  cout << ans << endl;
  return true;
}

int main(void)
{
  while (solve())
    ;
  return 0;
}
