#include <bits/stdc++.h>

using namespace std;

// does first player wins
bool win(int k, int m, int n)
{
  // no possible move
  if (k < m) {
    return false;
  }

  if (k < n || m == n) {
    // you can only take m at a time
    int q = k / m;
    return (q % 2 != 0);
  }

  if (k < m+n) {
    // take n to force win
    return true;
  }

  // whenever k is a losing state, so is k + m + n:
  //
  // whatever the first player at k + m + n does, the second player does
  // the opposite to get back to k
  //
  // whenever k is a winning state, then either k - m or k - n is a losing
  // state.  So the above implies that k + n = (k - m + m + n) or k + m
  // is a losing state.  Therefore, k + m + n is also a winning state because
  // either (k+m+n) - m or (k+m+n) - n is a losing state
  //
  // So basically everything is periodic with a period of m+n

  return win(k % (m+n), m, n);
}

int main()
{
  int k, m, n;
  cin >> k >> m >> n;

  if (win(k, m, n)) {
    cout << "Alex" << endl;
  } else {
    cout << "Barbossa" << endl;
  }

  return 0;
}
