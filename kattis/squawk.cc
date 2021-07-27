#include <bits/stdc++.h>

using namespace std;

void mult(long long A[][100], long long v[], int n)
{
  long long w[100] = {0};
  for (int i = 0; i < n; i++) {
    for (int k = 0; k < n; k++) {
      w[i] += v[k] * A[k][i];
    }
  }
  copy(w, w+n, v);
}

int main()
{
  int n, m, s, t;
  cin >> n >> m >> s >> t;

  long long A[100][100] = {0};
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    A[x][y] = A[y][x] = 1;
  }

  long long v[100] = {0};
  v[s] = 1;

  for (int i = 0; i < t; i++) {
    mult(A, v, n);
  }

  cout << accumulate(v, v+n, 0LL) << endl;
  
  return 0;
}
