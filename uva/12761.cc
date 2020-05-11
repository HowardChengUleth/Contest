// Trick: you can represent the number of chips each person has as a vector v,
// and you can formulate each step as a matrix multiplication (with the same
// matrix A).  The number of chips after k steps is then M^k * v.
//
// Complexity: O(N^3 log K)

#include <iostream>
#include <algorithm>

using namespace std;

typedef int Matrix[50][50];
typedef int Vector[50];

void mult(Matrix A, Matrix B, int N, Matrix R)
{
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      R[i][j] = 0;
      for (int k = 0; k < N; k++) {
	R[i][j] += (A[i][k] * B[k][j]) % N;
	R[i][j] %= N;
      }
    }
  }
}

void mult(Matrix A, Vector v, int N, Vector R)
{
  for (int i = 0; i < N; i++) {
    R[i] = 0;
    for (int k = 0; k < N; k++) {
      R[i] += (A[i][k] * v[k]) % N;
      R[i] %= N;
    }
  }
}

void power(Matrix A, int N, int k, Matrix R)
{
  if (k == 0) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
	R[i][j] = (i == j);
      }
    }
    return;
  }

  Matrix T;
  if (k % 2 == 0) {
    power(A, N, k/2, T);
    mult(T, T, N, R);
  } else {
    power(A, N, k-1, T);
    mult(T, A, N, R);
  }
}

void solve()
{
  Vector X;

  int N, K, D;
  cin >> N >> K >> D;
  for (int i = 0; i < N; i++) {
    cin >> X[i];
    X[i] %= N;
  }

  Matrix A;
  for (int i = 0; i < N; i++) {
    fill(A[i], A[i]+N, 0);
    for (int j = 1; j <= D; j++) {
      A[i][(i+j) % N] = 1;
      A[i][(i+N-j) % N] = 1;
    }
  }

  Matrix P;
  power(A, N, K, P);

  Vector R;
  mult(P, X, N, R);

  int best = *min_element(R, R+N);
  cout << best << endl;

  bool printed = false;
  for (int i = 0; i < N; i++) {
    if (R[i] != best) continue;
    if (printed) cout << ' ';
    cout << i+1;
    printed = true;
  }
  cout << endl;

  
  
}

int main()
{
  int T;
  cin >> T;
  while (T--)
    solve();

  return 0;
}
