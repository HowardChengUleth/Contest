#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1000000007;

const int MAX_N = 51;

ll N, M, T;
ll A[MAX_N][MAX_N], v[MAX_N];
int type[MAX_N];

void add_edge(int u, int v)
{
  if (type[u] == 1) {
    A[v][N]++;
  } else {
    A[v][u] = 1;
  }
}

// C = A * B
void mult(ll A[MAX_N][MAX_N], ll B[MAX_N][MAX_N], ll C[MAX_N][MAX_N])
{
  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= N; j++) {
      C[i][j] = 0;
      for (int k = 0; k <= N; k++) {
	C[i][j] += (A[i][k] * B[k][j]) % MOD;
	C[i][j] %= MOD;
      }
    }
  }
}

// w = A * v
void mult(ll A[MAX_N][MAX_N], ll v[MAX_N], ll w[MAX_N])
{
  for (int i = 0; i <= N; i++) {
    w[i] = 0;
    for (int k = 0; k <= N; k++) {
      w[i] += (A[i][k] * v[k]) % MOD;
      w[i] %= MOD;
    }
  }
}

// B = A^n
void exp(ll A[MAX_N][MAX_N], ll B[MAX_N][MAX_N], ll n)
{
  if (n == 0) {
    for (int i = 0; i <= N; i++) {
      for (int j = 0; j <= N; j++) {
	B[i][j] = (i == j);
      }
    }
    return;
  }

  ll temp[MAX_N][MAX_N];
  if (n % 2 == 0) {
    mult(A, A, temp);
    exp(temp, B, n/2);
  } else {
    exp(A, temp, n-1);
    mult(A, temp, B);
  }
}

int main()
{
  cin >> N >> M >> T;
  
  for (int i = 0; i <= N; i++) {
    v[i] = 1;
    for (int j = 0; j <= N; j++) {
      A[i][j] = (i == j);
    }
  }

  for (int i = 0; i < N; i++) {
    cin >> type[i];
  }

  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;

    add_edge(u, v);
    add_edge(v, u);
  }

  ll Apow[MAX_N][MAX_N];
  exp(A, Apow, T);

  ll w[MAX_N];
  mult(Apow, v, w);

  ll ans = 0;
  for (int i = 0; i < N; i++) {
    ans += w[i];
    ans %= MOD;
  }
  cout << ans << endl;
  /*  
  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= N; j++) {
      cout << A[i][j] << ' ';
    }
    cout << endl;
    }
  */
  
  return 0;
}
