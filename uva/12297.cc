#include <bits/stdc++.h>

// To compute f(n,k):
//
// The sum of k items may have 0 - 4 1's.
//
// If there are 0 1's, then you can reduce each item by 1 and count f(n-k,k)
// If there is 1 1's, then you can reduce the remaining k-1 items by 1 and
//   count f(n-1 - (k-1), k-1) = f(n-k, k-1).  Multiply that by C(4,1)
// Similarly, if there are p 1's, it is C(4,p) * f(n-k, k-p)
//
// So recurrence is
//
// f(n,k) = f(n-k,k) + 4*f(n-k,k-1) + 6*f(n-k,k-2) + 4*f(n-k,k-3) + f(n-k,k-4)
//
// f(n,k) = 0 if k < 0
//
// We compute the vector [ f(n,k) ... f(n,1) ] from [ f(n-k,k) ... f(n-k,1)]
// with a matrix, so that we can compute the one we want quickly with matrix
// exponentiation

using namespace std;

const int C[5] = { 1, 4, 6, 4, 1};
typedef long long ll;
const ll MOD = 1000000009;
int n, k;

void mult_mat(ll A[110][110], ll B[110][110], ll C[110][110], int n)
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      C[i][j] = 0;
      for (int k = 0; k < n; k++) {
	C[i][j] += (A[i][k] * B[k][j]) % MOD;
	C[i][j] %= MOD;
      }
    }
  }
}

void mult_mat_vec(ll A[110][110], ll v[110], ll w[110], int n)
{
  for (int i = 0; i < n; i++) {
    w[i] = 0;
    for (int j = 0; j < n; j++) {
      w[i] += (A[i][j] * v[j]) % MOD;
      w[i] %= MOD;
    }
  }
}

void exp_mat(ll A[110][110], int n, int e, ll C[110][110])
{
  if (e == 0) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
	C[i][j] = (i == j) ? 1 : 0;
      }
    }
    return;
  } else if (e == 1) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
	C[i][j] = A[i][j];
      }
    }
    return;
  }

  ll B[110][110];
  if (e % 2 == 0) {
    exp_mat(A, n, e/2, B);
    mult_mat(B, B, C, n);
  } else {
    exp_mat(A, n, e-1, B);
    mult_mat(A, B, C, n);
  }
}

// f(n,k) value for 0 <= n, k <= 10
ll smallf[11][11];

void smallf_precomp()
{
  smallf[0][0] = 1;
  
  for (int n = 1; n <= 10; n++) {
    for (int k = 1; k <= 10; k++) {
      for (int t = 0; t <= 4; t++) {
	if (n-k >= 0 && k-t >= 0) {
	  smallf[n][k] += C[t] * smallf[n-k][k-t];
	  smallf[n][k] %= MOD;
	}
      }
      //      cout << setw(4) << smallf[n][k];
    }
    //    cout << endl;
  }
}

int index(int nn, int kk)
{
  if (1 <= nn && nn <= k && 1 <= kk && kk <= k) {
    return (nn-1)*k + (kk-1);
  } else {
    return -1;
  }
}

bool solve()
{
  cin >> n >> k;
  if (!n && !k)
    return false;

  if (n <= 10) {
    ll ans = 0;
    for (int i = 1; i <= k; i++) {
      ans += smallf[n][i];
      ans %= MOD;
    }
    cout << ans << endl;
    return true;
  }

  ll v[110] = {0}, w[110];
  for (int nn = 1; nn <= k; nn++) {
    for (int kk = 1; kk <= k; kk++) {
      v[index(nn, kk)] = smallf[nn][kk];
    }
  }
  
  ll A[110][110] = {0};

  for (int nn = 1; nn <= k; nn++) {
    for (int kk = 1; kk <= k; kk++) {
      int row = index(nn, kk);
      if (index(nn+1, kk) != -1) {
	A[row][index(nn+1, kk)] = 1;
      } else {
	for (int t = 0; t <= 4; t++) {
	  int pos = index(nn+1-kk, kk-t);
	  if (pos >= 0) {
	    A[row][pos] = C[t];
	  }
	}
      }
    }
  }

  ll Aexp[110][110];
  exp_mat(A, k*k, n-k, Aexp);

  mult_mat_vec(Aexp, v, w, k*k);

  ll ans = 0;
  for (int i = 1; i <= k; i++) {
    ans += w[index(k, i)];
    ans %= MOD;
  }
  cout << ans << endl;

  return true;
}

int main()
{
  smallf_precomp();
  while (solve())
    ;
  
  return 0;
}
