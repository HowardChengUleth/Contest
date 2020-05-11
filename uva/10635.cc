/*
 * Longest Ascending Subsequence
 *
 * Author: Howard Cheng
 * Reference:
 *   Gries, D.  The Science of Programming
 *
 * Given an array of size n, asc_seq returns the length of the longest
 * ascending subsequence, as well as one of the subsequences in S.
 * sasc_seq returns the length of the longest strictly ascending
 * subsequence.  It runs in O(n log n) time.
 *
 * Also included are simplified versions when only the length is needed.
 *
 * Note: If we want to find do the same things with descending
 * subsequences, just reverse the array before calling the routines.
 * 
 */


#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

int asc_seq(int A[], int n)
{
  vector<int> last(n+1);
  if (n == 0) {
    return 0;
  }

  int len = 1;
  last[1] = A[0];

  for (int i = 1; i < n; i++) {
    int j = upper_bound(last.begin()+1, last.begin()+len+1, A[i]) -
      last.begin();
    last[j] = A[i];
    len = max(len, j);
  }

  return len;
}

void solve()
{
  int n, p, q;
  cin >> n >> p >> q;
  
  int seq1[250*250], seq2[250*250];
  int index[250*250+1];

  for (int i = 0; i <= p; i++) {
    cin >> seq1[i];
  }
  for (int i = 0; i <= q; i++) {
    cin >> seq2[i];
  }

  fill(index+1, index+n*n+1, -1);
  for (int i = 0; i <= p; i++) {
    index[seq1[i]] = i;
  }

  int num = 0;
  for (int i = 0; i <= q; i++) {
    int t = index[seq2[i]];
    if (t >= 0) {
      seq1[num++] = t;
    }
  }

  cout << asc_seq(seq1, num) << endl;
}

int main()
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": ";
    solve();
  }
  return 0;
}
