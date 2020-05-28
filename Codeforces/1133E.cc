#include <bits/stdc++.h>

using namespace std;

// first, sort the skills in increasing order
//
// Let f(n, k) be the max number of students included in at most k balanced
// teams, using the n smallest students.
//
// Clearly f(n, 0) = f(0, k) = 0
//
// To compute f(n, k), there are two cases:
//
// If the n-th student is not on any team, then it is just f(n-1, k)
//
// Otherwise, the n-th student may be in a team of 1, 2, 3, ..., n as
// long as the resulting team is balanced.  If the size of that team is t,
// then the number of students included is t + f(n-t, k-1).  Note that
// we always want that team to have maximum size because it does not help
// to include fewer (use a greedy argument).  Since the list is sorted,
// we can use binary search to find this largest team.
//
// complexity is O(n^2 log n)

int n, k;
int A[5000];

int dp[5001][5001];

int f(int n, int k)
{
  if (n == 0 || k == 0) {
    return 0;
  }
  if (dp[n][k] >= 0) {
    return dp[n][k];
  }

  int t = n - (lower_bound(A, A+n-1, A[n-1]-5) - A);
  return dp[n][k] = max(f(n-1,k), t + f(n-t, k-1));
}

int main()
{
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> A[i];
  }
  sort(A, A+n);

  for (int i = 0; i <= n; i++) {
    fill(dp[i], dp[i]+k+1, -1);
  }

  cout << f(n, k) << endl;

  return 0;
}
