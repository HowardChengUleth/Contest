/*
 * Suffix array
 *
 * Author: Howard Cheng
 * References:
 *   Manber, U. and Myers, G.  "Suffix Arrays: a New Method for On-line
 *   String Searches."  SIAM Journal on Computing.  22(5) p. 935-948, 1993.
 *
 *   T. Kasai, G. Lee, H. Arimura, S. Arikawa, and K. Park.  "Linear-time
 *   Longest-common-prefix Computation in Suffix Arrays and Its
 *   Applications."  Proc. 12th Annual Conference on Combinatorial
 *   Pattern Matching, LNCS 2089, p. 181-192, 2001
 *
 *   J. K?kk?nen and P. Sanders. Simple linear work suffix array
 *   construction.  In Proc. 13th International Conference on Automata,
 *   Languages and Programming, Springer, 2003
 *
 * The build_sarray routine takes in a string str of n characters (null-
 * terminated), and construct an array sarray.  Optionally, you can also
 * construct an lcp array from the sarray computed.  The properties
 * are:
 *
 * - If p = sarray[i], then the suffix of str starting at p (i.e.
 *   str[p..n-1] is the i-th suffix when all the suffixes are sorted in
 *   lexicographical order
 *
 *   NOTE: the empty suffix is not included in this list, so sarray[0] != n.
 *
 * - lcp[i] contains the length of the longest common prefix of the suffixes
 *   pointed to by sarray[i-1] and sarray[i].  lcp[0] is defined to be 0.
 *
 * - To see whether a pattern P occurs in str, you can look for it as the
 *   prefix of a suffix.  This can be done with a binary search in
 *   O(|P| log n) time.  Call find() to return an index of the pattern
 *   in str (if there are multiple occurrences, it can be *ANY* index),
 *   or -1 if not found.
 *
 * The construction of the suffix array takes O(n) time.
 *
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

bool leq(int a1, int a2,   int b1, int b2)
{
  return(a1 < b1 || a1 == b1 && a2 <= b2); 
}                                                   

bool leq(int a1, int a2, int a3,   int b1, int b2, int b3)
{
  return(a1 < b1 || a1 == b1 && leq(a2,a3, b2,b3)); 
}

void radixPass(int* a, int* b, int* r, int n, int K) 
{
  int* c = new int[K + 1];
  fill(c, c+K+1, 0);
  for (int i = 0;  i < n;  i++) c[r[a[i]]]++;
  for (int i = 0, sum = 0;  i <= K;  i++) {
     int t = c[i];  c[i] = sum;  sum += t;
  }
  for (int i = 0;  i < n;  i++) b[c[r[a[i]]]++] = a[i];
  delete [] c;
}

#define GetI() (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2)

void sarray_int(int* s, int* SA, int n, int K) {
  int n0=(n+2)/3, n1=(n+1)/3, n2=n/3, n02=n0+n2; 
  int* s12  = new int[n02 + 3];  s12[n02]= s12[n02+1]= s12[n02+2]=0; 
  int* SA12 = new int[n02 + 3]; SA12[n02]=SA12[n02+1]=SA12[n02+2]=0;
  int* s0   = new int[n0];
  int* SA0  = new int[n0];
 
  for (int i=0, j=0;  i < n+(n0-n1);  i++) if (i%3 != 0) s12[j++] = i;

  radixPass(s12 , SA12, s+2, n02, K);
  radixPass(SA12, s12 , s+1, n02, K);  
  radixPass(s12 , SA12, s  , n02, K);

  int name = 0, c0 = -1, c1 = -1, c2 = -1;
  for (int i = 0;  i < n02;  i++) {
    if (s[SA12[i]] != c0 || s[SA12[i]+1] != c1 || s[SA12[i]+2] != c2) { 
      name++;  c0 = s[SA12[i]];  c1 = s[SA12[i]+1];  c2 = s[SA12[i]+2];
    }
    if (SA12[i] % 3 == 1) { s12[SA12[i]/3]      = name; }
    else                  { s12[SA12[i]/3 + n0] = name; }
  }

  if (name < n02) {
    sarray_int(s12, SA12, n02, name);
    for (int i = 0;  i < n02;  i++) s12[SA12[i]] = i + 1;
  } else
    for (int i = 0;  i < n02;  i++) SA12[s12[i] - 1] = i; 

  for (int i=0, j=0;  i < n02;  i++) if (SA12[i] < n0) s0[j++] = 3*SA12[i];
  radixPass(s0, SA0, s, n0, K);

  for (int p=0,  t=n0-n1,  k=0;  k < n;  k++) {
    int i = GetI();
    int j = SA0[p];
    if (SA12[t] < n0 ? 
        leq(s[i],       s12[SA12[t] + n0], s[j],       s12[j/3]) :
        leq(s[i],s[i+1],s12[SA12[t]-n0+1], s[j],s[j+1],s12[j/3+n0]))
    {
      SA[k] = i;  t++;
      if (t == n02) {
        for (k++;  p < n0;  p++, k++) SA[k] = SA0[p];
      }
    } else { 
      SA[k] = j;  p++; 
      if (p == n0)  {
        for (k++;  t < n02;  t++, k++) SA[k] = GetI(); 
      }
    }  
  } 
  delete [] s12; delete [] SA12; delete [] SA0; delete [] s0; 
}

void build_sarray(string str, int sarray[])
{
  int n = str.length();
  int *s = new int[n+3];
  int *SA = new int[n+3];
  for (int i = 0; i < n; i++) {
    s[i] = str[i];
  }
  s[n] = s[n+1] = s[n+2] = 0;
  sarray_int(s, SA, n, 256);
  copy(SA, SA+n, sarray);

  delete[] s;
  delete[] SA;
}

void compute_lcp(string str, int sarray[], int lcp[])
{
  int n = str.length();
  int *rank = new int[n];
  for (int i = 0; i < n; i++) {
    rank[sarray[i]] = i;
  }
  int h = 0;
  for (int i = 0; i < n; i++) {
    int k = rank[i];
    if (k == 0) {
      lcp[k] = -1;
    } else {
      int j = sarray[k-1];
      while (i + h < n && j + h < n && str[i+h] == str[j+h]) {
	h++;
      }
      lcp[k] = h;
    }
    if (h > 0) {
      h--;
    }
  }
  lcp[0] = 0;
  delete[] rank;
}

#include <iostream>
#include <set>
#include <string>

using namespace std;

void solve(const string &s1, const string &s2)
{
  int n1 = s1.length(), n2 = s2.length();
  string str = s1 + "#" + s2;
  int sarray[601], lcp[601];
  build_sarray(str, sarray);
  compute_lcp(str, sarray, lcp);

  int best = 0;
  for (int i = 1; i < n1+n2+1; i++) {
    if (((sarray[i-1] < n1 && sarray[i] >= n1) ||
	 (sarray[i-1] >= n1 && sarray[i] < n1))) {
      best = max(best, lcp[i]);
    }
  }

  if (best == 0) {
    cout << "No common sequence." << endl;
  } else {
    set<string> S;
    for (int i = 1; i < n1+n2+1; i++) {
      if (((sarray[i-1] < n1 && sarray[i] >= n1) ||
	   (sarray[i-1] >= n1 && sarray[i] < n1)) &&
	  best == lcp[i]) {
	S.insert(str.substr(sarray[i], best));
      }
    }

    for (set<string>::const_iterator it = S.begin(); it != S.end(); ++it) {
      cout << *it << endl;
    }
  }
}

int main(void)
{
  string s1, s2;
  bool first = true;
  while (cin >> s1 >> s2) {
    if (!first) cout << endl;
    solve(s1, s2);
    first = false;
  }
  
  return 0;
}
