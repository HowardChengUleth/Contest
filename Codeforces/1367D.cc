#include <bits/stdc++.h>

using namespace std;

// If we look at the positions where b_i = 0, those must be the largest
// character that is left.  It is okay to pick the largest character that
// works (frequency matches the number of b_i = 0) for those positions.
// Once that is done, we can adjust all the other b_i values and repeat
//
// the strings are short, so we don't have to do anything too efficient.

void solve()
{
  string s;
  int m, b[50];

  cin >> s >> m;
  for (int i = 0; i < m; i++) {
    cin >> b[i];
  }
  int freq[256] = {0};
  for (auto c : s) {
    freq[c]++;
  }
  
  char ans[51] = {0};

  char next = 'z';
  while (true) {
    int max_c = 0;
    for (int i = 0; i < m; i++) {
      if (!b[i]) max_c++;
    }
    if (!max_c) break;

    while (freq[next] < max_c)
      next--;

    int b2[50];
    copy(b, b+m, b2);
    
    for (int i = 0; i < m; i++) {
      if (b2[i]) continue;
      ans[i] = next;
      for (int j = 0; j < m; j++) {
	b[j] -= abs(j-i);
      }
      b[i] = -1;
    }
    next--;
  }

  for (int i = 0; i < m; i++) {
    cout << ans[i];
  }
  cout << endl;

}

int main()
{
  int q;
  cin >> q;
  while (q--)
    solve();

  return 0;
}
