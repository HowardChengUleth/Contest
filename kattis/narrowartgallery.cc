#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// which row, how many to close off, bitmask for next row
ll memo[210][210][3];

int A[210][2];

ll f(int N, int k, int next)
{
  if (memo[N][k][next] != -1) {
    return memo[N][k][next];
  }

  if (N == 0) {
    if (k == 0) {
      return memo[N][k][next] = 0;
    } else {
      return INT_MIN;
    }
  }

  // try closing the left
  ll ans = INT_MIN;
  if (!(next & 2) && k > 0) {
    ans = max(ans, A[N-1][1] + f(N-1, k-1, 1));
  }
  // try closing the right
  if (!(next & 1) && k > 0) {
    ans = max(ans, A[N-1][0] + f(N-1, k-1, 2));
  }

  // try not closing
  ans = max(ans, A[N-1][0] + A[N-1][1] + f(N-1, k, 0));

  return memo[N][k][next] = ans;
}

bool solve()
{
  int N, k;
  cin >> N >> k;
  if (!N && !k) return false;

  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= k; j++) {
      fill(memo[i][j], memo[i][j]+3, -1);
    }
  }
  
  for (int i = 0; i < N; i++) {
    cin >> A[i][0] >> A[i][1];
  }

  cout << f(N, k, 0) << endl;

  return true;
}

int main()
{
  while (solve())
    ;
  return 0;
}
