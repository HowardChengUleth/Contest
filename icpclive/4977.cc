// we scan from left to right.  Whenever we find a t[i] > 0, we need to find
// an index j < i such that t[j] = 0 and occuring after the last time we see
// t[i].  Note that we need to choose j to be the smallest possible.  Of
// course each such j can only be used once.
//
// We will keep track of the last time we see each lake, and also a set of
// the times we have seen 0.

#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int t[1000000];
int last[1000001];
int drink[1000000];

void solve_case()
{
  int n, m;

  cin >> n >> m;

  for (int i = 0; i < m; i++) {
    cin >> t[i];
  }

  fill(drink, drink+m, 0);
  fill(last+1, last+n+1, -1);

  set<int> zeroes;

  for (int i = 0; i < m; i++) {
    if (t[i] == 0) {
      zeroes.insert(i);
    } else {
      set<int>::iterator it = zeroes.lower_bound(last[t[i]]+1);
      if (it == zeroes.end()) {
	cout << "NO" << endl;
	return;
      }
      drink[*it] = t[i];
      last[t[i]] = i;
      zeroes.erase(it);
    }
  }

  cout << "YES" << endl;
  bool printed = false;
  for (int i = 0; i < m; i++) {
    if (t[i]) continue;
    if (printed) cout << ' ';
    cout << drink[i];
    printed = true;
  }
  cout << endl;
}

int main(void)
{
  int Z;
  cin >> Z;
  while (Z--) {
    solve_case();
  }

  return 0;
}
