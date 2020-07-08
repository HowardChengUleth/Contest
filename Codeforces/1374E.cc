#include <bits/stdc++.h>

using namespace std;

// the idea is this:
//
// - A book that is not liked by either Alice or Bob can be ignored
// - A book that is liked only by Alice will have to be paired with a book that
//   is only liked by Bob
// - Books that are liked by both can be used
//
// We can do this greedily.  At each step, we choose either a pair of books
// (1 0 and 0 1) that sums up to the smallest total, or a book (1 1) that
// has the next smallest total.  Do this until we have k.
//
// So we sort books liked only by Alice and Bob, pair them up and pretend they
// are one combined book liked by both.  Then sort the list of books liked
// by both and picked the k shortest books.

int main()
{
  int n, k;
  cin >> n >> k;

  vector<int> A, B, both;
  for (int i = 0; i < n; i++) {
    int t, a, b;
    cin >> t >> a >> b;
    if (a && b) {
      both.push_back(t);
    } else if (a) {
      A.push_back(t);
    } else if (b) {
      B.push_back(t);
    }
  }
  if (both.size() + min(A.size(), B.size()) < k) {
    cout << -1 << endl;
    return 0;
  }

  sort(begin(A), end(A));
  sort(begin(B), end(B));
  for (int i = 0; i < min(A.size(), B.size()); i++) {
    both.push_back(A[i]+B[i]);
  }
  sort(begin(both), end(both));
  cout << accumulate(begin(both), begin(both)+k, 0) << endl;

  
  return 0;
}
