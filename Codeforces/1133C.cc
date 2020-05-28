#include <bits/stdc++.h>

using namespace std;

// we sort the list from smallest to largest.  Try starting the team at
// each point in the list, and then try to look for the ending point.
// The main observation is that when we move the starting point forward
// by 1, the ending point can start moving forward from where we left off
// in the step before and we do not have to backtrack.  So basically each
// loop iteration always moves the starting point forward and may move
// the ending point forward a few times.  There are only n steps each of
// these points can move, so the algorithm is O(n) overall.
//
// This is the standard "two pointers" algorithm.

int main()
{
  int n;
  cin >> n;

  int A[200000];
  for (int i = 0; i < n; i++) {
    cin >> A[i];
  }
  sort(A, A+n);

  int ans = 0;
  
  int j = 0;
  for (int i = 0; i < n; i++) {
    j = max(j, i+1);
    while (j < n && A[j] - A[i] <= 5)
      j++;

    ans = max(ans, j-i);
  }
  cout << ans << endl;
  return 0;
}
