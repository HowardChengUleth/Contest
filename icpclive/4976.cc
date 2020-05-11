//
// idea:
//
// for each i, we can compute start[i] (and end[i]) = length of longest
// increasing consecutive towers starting (ending) at position i.  This
// can be done in O(n) time.
//
// We are interesting in finding end[j] + start[i] where j < i and A[j] < A[i].
// As we scan through j = 0, 1, ..., n-1, we keep track of
//
//   len = max(end[i], i = 0..j-1)
//   last[k] = last element of an increasing sequence of length k (k = 1..len).
//             Ties are broken by choosing last[k].
//
// Notice that last[0] < last[1] < ... < last[len] so we can
// use binary search to see where A[j] falls into, and update if
// necessary.  This is similar to the O(n log n) longest increasing
// subsequence algorithm.
// 

#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

void solve_case()
{
  int n;
  cin >> n;

  int A[200000];
  for (int i = 0; i < n; i++) {
    cin >> A[i];
  }

  // compute start and end
  int start[200000], end[200000];
  end[0] = 1;
  for (int i = 1; i < n; i++) {
    if (A[i] > A[i-1]) {
      end[i] = end[i-1] + 1;
    } else {
      end[i] = 1;
    }
  }
  start[n-1] = 1;
  for (int i = n-2; i >= 0; i--) {
    if (A[i] < A[i+1]) {
      start[i] = start[i+1] + 1;
    } else {
      start[i] = 1;
    }
  }

  // now we go through start[i] and find the best end[j]
  int last[200001];
  int pos[200001];
  int ans = max(*max_element(start, start+n),
		*max_element(end, end+n));
  int len = 1;
  last[1] = A[0];
  pos[1] = 0;
  for (int i = 1; i < n; i++) {
    int j = lower_bound(last+1, last+len+1, A[i]) - last - 1;
    assert(j == 0 || A[i] > last[j]);
    if (j) {
      ans = max(ans, end[pos[j]] + start[i]);
    }
    if (end[i] > len || A[i] < last[end[i]]) {
      last[end[i]] = A[i];
      pos[end[i]] = i;
    }
    len = max(len, end[i]);
  }

  cout << ans << endl;
}

int main(void)
{
  int Z;
  cin >> Z;
  while (Z--) {
    solve_case();
  }

  return 0;
}
