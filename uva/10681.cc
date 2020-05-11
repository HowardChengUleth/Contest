#include <iostream>
#include <algorithm>

using namespace std;

typedef bool Mat[100][100];

// C = A*B
void mult(Mat C, Mat A, Mat B, int n)
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      C[i][j] = false;
      for (int k = 0; k < n; k++) {
	C[i][j] |= (A[i][k] && B[k][j]);
      }
    }
  }
}

// A *= B, A can be the same as B
void mult(Mat A, Mat B, int n)
{
  Mat C;
  mult(C, A, B, n);
  for (int i = 0; i < n; i++) {
    copy(C[i], C[i]+n, A[i]);
  }
}

void pow(Mat A, int n, int d)
{
  Mat X;
  for (int i = 0; i < n; i++) {
    copy(A[i], A[i]+n, X[i]);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      A[i][j] = (i == j);
    }
  }

  while (d > 0) {
    if (d & 1) {
      d--;
      mult(A, X, n);
    } else {
      d >>= 1;
      mult(X, X, n);
    }
  }
}

bool solve()
{
  int C, L;
  cin >> C >> L;
  if (!C && !L) return false;
  
  Mat A;
  for (int i = 0; i < C; i++) {
    for (int j = 0; j < C; j++) {
      A[i][j] = false;
    }
  }
  while (L--) {
    int u, v;
    cin >> u >> v;
    A[u-1][v-1] = A[v-1][u-1] = true;
  }

  int S, E, D;
  cin >> S >> E >> D;
  pow(A, C, D);

  if (A[S-1][E-1]) {
    cout << "Yes, Teobaldo can travel." << endl;
  } else {
    cout << "No, Teobaldo can not travel." << endl;
  }
  return true;
}

int main(void)
{
  while (solve())
    ;
  return 0;
}
