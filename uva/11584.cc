// This is dynamic programming in two ways.
//
// First, if we want to compute the optimal partition of the first n
// characters, try all lengths for the last partition (if it's a palindrome)
// and glue it to the optimal solution for the first part.  This has
// complexity O(n^2).
//
// The second dynamic programming component involves the determination
// of whether a substring is a palindrome.  This can be done in O(n^2)
// time as well and the result should be memorized.
//
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

typedef unsigned int uint;

void solve(const string &s)
{
  // is s[i..j] a palindrome?
  bool is_pal[1000][1000];

  // length 1 always palindrome
  for (uint i = 0; i < s.length(); i++) {
    is_pal[i][i] = true;
  }

  // consider substrings of increasing lengths
  for (uint k = 1; k < s.length(); k++) {
    for (uint i = 0; i+k < s.length(); i++) {
      is_pal[i][i+k] = (s[i] == s[i+k] && 
			(k == 1 || is_pal[i+1][i+k-1]));
    }
  }

  int sol[1001];  // sol[i] = min groups for the first i characters
  sol[0] = 0;
  for (uint i = 1; i <= s.length(); i++) {
    sol[i] = -1;
    // try all partitions ending at character i-1.
    for (uint j = 0; j <= i-1; j++) {
      if (!is_pal[j][i-1]) continue;
      int temp = 1 + sol[j];
      if (sol[i] == -1 || temp < sol[i]) {
	sol[i] = temp;
      }
    }
  }
  cout << sol[s.length()] << endl;
}

int main(void)
{
  int n;
  cin >> n;
  while (n-- > 0) {
    string s;
    cin >> s;
    solve(s);
  }
  return 0;
}
