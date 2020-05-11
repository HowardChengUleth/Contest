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
 * Note: If we want to find do the same things with descending
 * subsequences, just reverse the array before calling the routines.
 * 
 */


#include <iostream>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

int sasc_seq(vector<int> &A, vector<int> &S)
{
  int n = A.size();
  vector<int> last(n+1), pos(n+1), pred(n);
  if (n == 0) {
    return 0;
  }

  int len = 1;
  last[1] = A[pos[1] = 0];

  for (int i = 1; i < n; i++) {
    int j = lower_bound(last.begin()+1, last.begin()+len+1, A[i]) -
      last.begin();
    pred[i] = (j-1 > 0) ? pos[j-1] : -1;
    last[j] = A[pos[j] = i];
    len = max(len, j);
  }

  S.resize(len);
  int start = pos[len];
  for (int i = len-1; i >= 0; i--) {
    S[i] = A[start];
    start = pred[start];
  }

  return len;
}
int main(void)
{
  int cases;

  cin >> cases;
  cin.ignore();
  cin.ignore();
  while (cases-- > 0) {
    string line;
    vector<int> A, S;
    while (getline(cin, line) && line.length() > 0) {
      A.push_back(atoi(line.c_str()));
    }
    int len = sasc_seq(A, S);
    
    cout << "Max hits: " << len << endl;
    for (int i = 0; i < len; i++) {
      cout << S[i] << endl;
    }
    if (cases) {
      cout << endl;
    }

  }
  return 0;
}
