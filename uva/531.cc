/* @JUDGE_ID: 1102NT 531 C "Dynamic programming" */

/*
 * Longest common subsequence
 *
 * Author: Howard Cheng
 * Reference:
 *   http://www.ics.uci.edu/~eppstein/161/960229.html
 *
 * Given two arrays A and B with sizes n and m respectively, compute the
 * length of the longest common subsequence.  It also returns in s a longest
 * common subsequence (it may not be unique).  One can specify which one
 * to choose when multiple longest common subsequences exist.
 *
 * Running time and space requirement is O(mn).
 *
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <cassert>

using namespace std;

const int MAX_LEN = 101;

int LCS(string A[], int n, string B[], int m, string s[])
{
  int L[MAX_LEN+1][MAX_LEN+1];
  int i, j, k;
  
  for (i = n; i >= 0; i--) {
    for (j = m; j >= 0; j--) {
      if (i == n || j == m) {
	L[i][j] = 0;
      } else if (A[i] == B[j]) {
	L[i][j] = 1 + L[i+1][j+1];
      } else {
	L[i][j] = max(L[i+1][j], L[i][j+1]);
      }
    }
  }
  
  /* the following is not needed if you are not interested in the sequence */
  k = 0;
  i = j = 0;
  while (i < n && j < m) {
    if (A[i] == B[j]) {
      s[k++] = A[i];
      i++;
      j++;
    } else if (L[i+1][j] > L[i][j+1]) {
      i++;
    } else if (L[i+1][j] < L[i][j+1]) {
      j++;
    } else {
      /* put tie-breaking conditions here */

      /* eg. pick the one that starts at the first one the earliest */
      j++;
    }
  }
  return L[0][0];
}

int main(void)
{
   string A[MAX_LEN], B[MAX_LEN], s[MAX_LEN], buffer;
   int m, n, i, l;

   while (1) {
     n = m = 0;
     
     while (cin >> buffer && buffer != "#") {
       A[n++] = buffer;
     }
     if (!n) {
       break;
     }
     while (cin >> buffer && buffer != "#") {
       B[m++] = buffer;
     }
     l = LCS(A, n, B, m, s);
     for (i = 0; i < l; i++) {
       if (i) {
       cout << " ";
       }
     cout << s[i];
     }
     cout << endl;
   }
   return 0;
}
