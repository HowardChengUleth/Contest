#include <iostream>
#include <string>
#include <algorithm>

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
 * The build_sarray routine takes in a string str of n characters (null-
 * terminated), and construct two arrays sarray and lcp.  The properties
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
 *   O(|P| log n) time.
 *
 * The construction of the suffix array takes O(n log n) time.
 *
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <climits>
#include <cassert>

using namespace std;

void build_sarray(string str, int sarray[], int lcp[])
{
  int *prm, *count;
  char *bh;       /* use 1st bit for BH, 2nd bit for B2H in paper */
  int bucket[CHAR_MAX-CHAR_MIN+1];  /* just in ase char is signed */
  int n, a, c, d, e, h, i, j, l;

  n = str.length();
  prm = new int[n];
  count = new int[n];
  bh = new char[n+1];
  assert(prm && count && bh);

  /* sort the suffixes by first character */
  for (a = 0; a <= CHAR_MAX - CHAR_MIN; a++) {
    bucket[a] = -1;
  }
  for (i = 0; i < n; i++) {
    j = str[i] - CHAR_MIN;
    prm[i] = bucket[j];
    bucket[j] = i;
  }
  c = 0;
  for (a = 0; a <= CHAR_MAX - CHAR_MIN; a++) {
    for (i = bucket[a]; i != -1; i = j) {
      j = prm[i];
      prm[i] = c;
      bh[c++] = (i == bucket[a]);
    }
  }
  bh[n] = 1;
  for (i = 0; i < n; i++) {
    sarray[prm[i]] = i;
  }

  /* inductive sort */
  l = 0;
  for (h = 1; h < n; h *= 2) {
    for (i = 0; i < n; i++) {
      if (bh[i] & 1) {
	l = i;
	count[l] = 0;
      }
      prm[sarray[i]] = l;
    }

    d = n - h;
    e = prm[d];
    prm[d] = e + count[e];
    count[e]++;
    bh[prm[d]] |= 2;

    i = 0;
    while (i < n) {
      for (j = i; j < n && (j == i || !(bh[j] & 1)); j++) {
	d = sarray[j] - h;
	if (d >= 0) {
	  e = prm[d];
	  prm[d] = e + count[e];
	  count[e]++;
	  bh[prm[d]] |= 2;
	}
      }

      for (j = i; j < n && (j == i || !(bh[j] & 1)); j++) {
	d = sarray[j] - h;
	if (d >= 0 && bh[prm[d]] & 2) {
	  for (e = prm[d]+1; bh[e] == 2; e++) {
	    bh[e] &= 1;
	  }
	}
      }
      i = j;
    }

    for (i = 0; i < n; i++) {
      sarray[prm[i]] = i;
      if (bh[i] == 2) {
	bh[i] = 3;
      }
    }
  }

  h = 0;
  for (i = 0; i < n; i++) {
    e = prm[i];
    if (e > 0) {
      j = sarray[e-1];
      while (str[i+h] == str[j+h]) {
	h++;
      }
      lcp[e] = h;
      if (h > 0) {
	h--;
      }
    }
  }
  lcp[0] = 0;

  delete[] prm;
  delete[] count;
  delete[] bh;
}

using namespace std;

int table[256];

void setup()
{
  table['A'] = 0;
  table['B'] = 2;
  table['C'] = 3;
  table['D'] = 5;
  table['E'] = 7;
  table['F'] = 8;
  table['G'] = 10;
}

int semitone(const string &s)
{
  int t = table[s[0]];
  if (s.length() == 2) {
    if (s[1] == '#') {
      t++;
    } else {
      t--;
    }
  }
  return t % 12;
}

bool KMP(const string &s, const string &pat)
{
  int T[10001];
  fill(T, T + pat.size() + 1, -1);
  
  for(int i = 1; i <= pat.size(); i++) {
    int pos = T[i-1];
    while(pos != -1 && pat[pos] != pat[i-1]) {
      pos = T[pos];
    }
    T[i] = pos + 1;
  }

  int sp = 0;
  int kp = 0;
  while(sp < s.size()) {
    while (kp != -1 && (kp == pat.size() || pat[kp] != s[sp])) {
      kp = T[kp];
    }
    kp++;  sp++;
    if(kp == pat.size()) {
      return true;
    }
  }
 
  return false;
}

int find(const string &str, const int sarray[], const string &pattern)
{
  int n = str.length();
  int lo = 0, hi = n-1;
  while (lo <= hi) {
    int mid = (lo + (hi - lo)/2);
    int cmp = str.compare(sarray[mid], pattern.length(), pattern);
    if (cmp == 0) {
      return sarray[mid];
    } else if (cmp < 0) {
      lo = mid+1;
    } else {
      hi = mid-1;
    }
  }
  return -1;
}

int main(void)
{
  setup();
  int M, T;

  while (cin >> M >> T && M != 0 || T != 0) {
    string orig, pat;
    orig.reserve(100000);
    pat.reserve(10000);
    
    string s;
    int prev, t;
    for (int i = 0; i < M; i++) {
      cin >> s;
      t = semitone(s);
      if (i > 0) {
	orig += (char)((t + 12 - prev) % 12 + 'A');
      }
      prev = t;
    }
    for (int i = 0; i < T; i++) {
      cin >> s;
      t = semitone(s);
      if (i > 0) {
	pat += (char)((t + 12 - prev) % 12 + 'A');
      }
      prev = t;
    }

    /*

    if (KMP(orig, pat)) {
      cout << "S" << endl;
    } else {
      cout << "N" << endl;
    }
    */

    int sarray[100000], lcp[100000];
    build_sarray(orig, sarray, lcp);

    cout << (find(orig, sarray, pat) >= 0 ? "S" : "N") << endl;
  }

  return 0;
}
