//
// Idea: we can avoid trying all shifts if we convert S and W to differences
// between successive characters (though we have to watch for the case when
// W.length() == 1).  But that is not needed for this problem...
//
// We can't just use the standard string search from STL: it is quadratic.
// We have to use the KMP algorithm to do the string search.
//

#include <iostream>
#include <string>

using namespace std;

int rank[256];

string diff(const string &s, const string &A)
{
  string ans;
  
  for (unsigned int i = 1; i < s.length(); i++) {
    int d = rank[(unsigned)s[i]] - rank[(unsigned)s[i-1]];
    if (d < 0) d += A.length();
    ans += A[d];
  }
  return ans;
}

/*
 * KMP String Matching
 *
 * Author: Howard Cheng
 *
 * The prepare_pattern routine takes in the pattern you wish to search
 * for, and perform some processing to give a "failure array" to be used
 * by the actual search.  The complexity is linear in the length of the
 * pattern.
 *
 * The find_pattern routine takes in a string s, a pattern pat, and a
 * vector T computed by prepare_pattern.  It returns the index of the
 * first occurrence of pat in s, or -1 if it does not occur in s.
 * The complexity is linear in the length of the string s.
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void prepare_pattern(const string &pat, vector<int> &T)
{
  int n = pat.length();
  T.resize(n+1);
  fill(T.begin(), T.end(), -1);
  for (int i = 1; i <= n; i++) {
    int pos = T[i-1];
    while (pos != -1 && pat[pos] != pat[i-1]) {
      pos = T[pos];
    }
    T[i] = pos + 1;
  }
}

void find_pattern(const string &s, const string &pat, const vector<int> &T,
		  vector<int> &matches)
{
  int sp = 0, kp = 0;
  int slen = s.length(), plen = pat.length();
  while (sp < slen) {
    while (kp != -1 && (kp == plen || pat[kp] != s[sp])) {
      kp = T[kp];
    }
    kp++;   sp++;
    if (kp == plen) {
      matches.push_back(sp - plen);
      kp = T[kp];
      //      return sp - plen;
    }
  }
  //  return -1;
}

void solve()
{
  string A, W, S;
  cin >> A >> W >> S;

  for (unsigned int i = 0; i < A.length(); i++) {
    rank[(unsigned)A[i]] = i;
  }

  string Wdiff = diff(W, A), Sdiff = diff(S, A);

  vector<int> T;
  prepare_pattern(Wdiff, T);
  int freq[256] = {0};

  if (Wdiff == "") {
    // special case: every shift is a possible match
    for (unsigned int i = 0; i < S.length(); i++) {
      freq[(unsigned)S[i]]++;
    }
  } else {
    vector<int> matches;
    int k = 0;
    find_pattern(Sdiff, Wdiff, T, matches);
    for (unsigned int i = 0; i < matches.size(); i++) {
      int index = matches[i];
      freq[(unsigned)S[index]]++;
      k = index+1;
    }
  }


  
  int shifts[100];
  int num_shifts = 0;
  for (unsigned int i = 0; i < A.length(); i++) {
    if (freq[(unsigned)A[i]] == 1) {
      int s = rank[(unsigned)A[i]] - rank[(unsigned)W[0]];
      if (s < 0) s += A.length();
      shifts[num_shifts++] = s;
    }
  }
  sort(shifts, shifts + num_shifts);
  
  if (num_shifts == 0) {
    cout << "no solution" << endl;
  } else if (num_shifts == 1) {
    cout << "unique: " << shifts[0] << endl;
  } else {
    cout << "ambiguous:";
    for (int i = 0; i < num_shifts; i++) {
      cout << ' ' << shifts[i];
    }
    cout << endl;
  }
}

int main()
{
  int N;
  cin >> N;
  while (N--) {
    solve();
  }
  return 0;
}
