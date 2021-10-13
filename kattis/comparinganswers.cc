#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
ll A[1000][1000], B[1000][1000];

void mult(ll A[1000][1000], ll v[1000], ll out[1000])
{
  for (int i = 0; i < n; i++) {
    out[i] = 0;
    for (int j = 0; j < n; j++) {
      out[i] += A[i][j] * v[j];
    }
  }
}

bool trial()
{
  ll v[1000];

  for (int i = 0; i < n; i++) {
    v[i] = rand() % 10;
  }

  ll Av[1000], AAv[1000], Bv[1000];
  mult(A, v, Av);
  mult(A, Av, AAv);
  mult(B, v, Bv);

  return equal(AAv, AAv + n, Bv);
}

bool solve()
{
  cin >> n;
  if (!n) return false;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> A[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> B[i][j];
    }
  }

  for (int i = 0; i < 20; i++) {
    if (!trial()) {
      cout << "NO" << endl;
      return true;
    }
  }

  cout << "YES" << endl;			\
  
  return true;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  while (solve())
    ;
  
  return 0;
}
