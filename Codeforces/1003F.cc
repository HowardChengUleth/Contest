#include <bits/stdc++.h>

using namespace std;

// Since n is so small, we can just brute force O(n^3) provided that we only
// look at words instead of individual characters.
//
// So we first compare each pair of words at the beginning and remember
// that information.  Then for each i, j we compute the length (in number of
// words) the common substring starting at positions i and j.  We won't worry
// about overlap in this part.
//
// Finally, just try to abbreviate w[s..s+k-1] over all s and k.  For each
// choice, we can greedily look for non-overlapping chunks that are the same
// and try to find as many as we can.
// 

int main()
{
  int n;
  string w[300];
  int wlen[300];
  
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> w[i];
    wlen[i] = w[i].length();
  }

  // equal[i][j] = true iff w[i] == w[j]
  bool equal[300][300];
  for (int i = 0; i < n; i++) {
    equal[i][i] = true;
    for (int j = i+1; j < n; j++) {
      equal[i][j] = equal[j][i] = (w[i] == w[j]);
    }
  }

  // len[i][j] = number of common words from w[i] and w[j], i < j
  int common[300][300];
  
  for (int i = 0; i < n-1; i++) {
    common[i][n-1] = equal[i][n-1];
  }
  for (int j = n-2; j >= 0; j--) {
    for (int i = j-1; i >= 0; i--) {
      common[i][j] = (w[i] == w[j]) ? 1 + common[i+1][j+1] : 0;
    }
  }

  int total = accumulate(wlen, wlen+n, n-1);
  int best = total;
  
  // now just try abbreviating where the first segment starts at s for k
  // words
  for (int s = 0; s < n; s++) {
    int seqlen = 0;
    for (int k = 1; k <= n-s; k++) {
      seqlen += wlen[s+k-1];
      
      // let's see how many chunks are equal
      int chunks = 1;

      int t = s+k;
      while (t < n) {
	if (common[s][t] >= k) {
	  chunks++;
	  t += k;
	} else {
	  t++;
	}
      }

      if (chunks == 1) continue;
      int len = total + (1 - seqlen)*chunks;
      best = min(best, len);
    }
  }
  
  cout << best << endl;
}
