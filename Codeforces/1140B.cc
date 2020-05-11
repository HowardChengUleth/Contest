#include <bits/stdc++.h>

using namespace std;

int main()
{
  int t;
  cin >> t;
  while (t--) {
    int n;
    string s;
    cin >> n >> s;
    int lcount = 0, rcount = 0;
    int lastl = -1, firstr = 2*n;
    for (int i = 0; i < n; i++) {
      char c = s[i];
      if (c == '<') {
	lcount++;
	lastl = i;
      }
      if (c == '>') {
	rcount++;
	firstr = min(firstr, i);
      }
    }
    int ans = min(firstr, n-1-lastl);
    if (!lcount || !rcount) ans = 0;
    cout << ans << endl;
  }
      
  
  return 0;
}
