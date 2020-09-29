// all candidate string must be a substring of the input, because it is the
// last copy inserted, and its length has to be a divisor of the length of the
// input string

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int ans[201][201][201];

// assuming I still need to match str[si..n-1] by copies more copy of test,
// and test[ti..tn-1]
bool f(const string &str, const string &test, int si, int ti, int copies)
{
  if (ans[si][ti][copies] != -1) return ans[si][ti][copies];

  int tn = test.length();

  if (ti == tn) {
    // exhausted one more copy
    return ans[si][ti][copies] = f(str, test, si, 0, copies-1);
  }

  if (copies == 0) {
    // exhausted everything
    return ans[si][ti][copies] = true;
  }

  // I could match one more character from test
  if (str[si] == test[ti] && f(str, test, si+1, ti+1, copies)) {
    return ans[si][ti][copies] = true;
  }

  // or insert some copies in between
  for (int k = 1; k < copies; k++) {
    if (f(str, test, si, 0, k) &&              // copies inserted
	f(str, test, si+k*tn, ti, copies-k))   // remaining bit
      return ans[si][ti][copies] = true;
  }

  return ans[si][ti][copies] = false;
}

int main()
{
  string str;
  cin >> str;
  int n = str.length();

  int orig_freq[26] = {0};
  for (int i = 0; i < n; i++) {
    orig_freq[str[i]-'a']++;
  }

  bool found = false;
  string best;

  // try candidate substring of length len
  for (int len = 1; len <= n && !found; len++) {
    if (n % len != 0) continue;

    // if you cannot divide the frequency of each letter by the
    // proposed number of copies then it is not possible
    bool bad = false;
    int target_freq[26] = {0};
    for (int i = 0; i < 26; i++) {
      target_freq[i] = orig_freq[i] / (n / len);
      if (orig_freq[i] % (n / len) != 0) {
	bad = true;
	break;
      }
    }
    if (bad) continue;

    // try all substrings of that length
    for (int s = 0, e = len-1; e < n; s++, e++) {
      if (str[0] != str[s] || str[n-1] != str[e]) continue;
      int freq[26] = {0};
      for (int i = s; i <= e; i++) {
	freq[str[i]-'a']++;
      }
      if (!equal(freq, freq+26, target_freq)) continue;

      // frequencies have to be right to keep going

      
      string test = str.substr(s, len);

      for (int i = 0; i <= n; i++) {
	for (int j = 0; j <= len; j++) {
	  for (int k = 0; k <= n/len; k++) {
	    ans[i][j][k] = -1;
	  }
	}
      }
      
      if (f(str, test, 0, 0, n/len)) {
	if (!found || test < best) {
	  best = test;
	  found = true;
	}
      }
    }
  }
  cout << best << endl;
  
  return 0;
}
