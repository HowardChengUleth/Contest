#include <bits/stdc++.h>

using namespace std;

typedef int64_t ll;

const ll MOD = 1'000'000'000;

void mult(ll A[2][2], ll B[2][2], ll C[2][2])
{
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      C[i][j] = 0;
      for (int k = 0; k < 2; k++) {
	C[i][j] += (A[i][k] * B[k][j]) % MOD;
	C[i][j] %= MOD;
      }
    }
  }
}

void exp(ll A[2][2], ll res[2][2], ll Y)
{
  if (Y == 0) {
    res[0][0] = res[1][1] = 1;
    res[0][1] = res[1][0] = 0;
    return;
  }

  if (Y % 2 == 0) {
    ll A2[2][2];
    mult(A, A, A2);
    exp(A2, res, Y/2);
  } else {
    ll A1[2][2];
    exp(A, A1, Y-1);
    mult(A1, A, res);
  }
}

ll solve(ll Y)
{
  // [ fib(n) fib(n+1) ]^T = A^n * [ 0 1 ]^T, so we just have to
  // look at the (0,1) entry of A^n
  ll A[2][2] = { { 0, 1 }, { 1, 1 } };
  ll B[2][2];
  
  exp(A, B, Y);

  return B[0][1];
}

int main()
{
  int P;
  cin >> P;

  for (int i = 0; i < P; i++) {
    int K;
    ll Y;
    cin >> K >> Y;

    cout << K << ' ';
    cout << solve(Y) << endl;
  }

  return 0;
}
