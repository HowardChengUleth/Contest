#include <bits/stdc++.h>

using namespace std;

// First, to make things simpler we relabel the elements to be 0, 1, ..., n-1.
// This will not affect the answer.
//
// The idea is that instead of minimizing the operations, we will maximize
// the number of elements that do not move.  Once those are fixed, then
// the rest can always be moved in such a way that each element requires
// exactly 1 move to get to the final spot.
//
// The ones that don't move must form a contiguous sequence that are in
// order.  In other words, it would be i, i+1, ..., i+k, so that their
// positions are increasing order.  This can be done easily if we find
// out the position of each element, and to find the largest segment
// such that pos[i] < pos[i+1] < ... < pos[i+k].

void solve()
{
  map<int,int> rank;
  
  int n, a[3000];
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    rank[a[i]] = 1;
  }

  int r = 0;
  for (auto p : rank) {
    rank[p.first] = r++;
  }
  assert(r == n);
  for (int i = 0; i < n; i++) {
    a[i] = rank[a[i]];
  }

  int pos[3000];
  for (int i = 0; i < n; i++) {
    pos[a[i]] = i;
  }

  int len = 1;
  int best = len;
  for (int i = 1; i < n; i++) {
    if (pos[i] > pos[i-1]) {
      len++;
    } else {
      len = 1;
    }
    best = max(len, best);
  }

  cout << n - best << endl;
  

}

int main()
{
  int t;
  cin >> t;
  while (t--)
    solve();

  return 0;
}
