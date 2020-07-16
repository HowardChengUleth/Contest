#include <bits/stdc++.h>

using namespace std;

// look at the inverse of the permutation and check the different offsets
// in the arithmetic progression

int main(void)
{
  int n, i, d;
  int p[10000], inv[10000];
  int bad;

  cin >> n;
  while (n > 0) {
    char c;
    cin >> c;
    for (i = 0; i < n; i++) {
      cin >> p[i];
      inv[p[i]] = i;
    }

    bad = 0;
    for (i = 0; i < n && !bad; i++) {
      for (d = 1; p[i]+2*d < n && !bad; d++) {
	if ((i < inv[p[i]+d] && inv[p[i]+d] < inv[p[i]+2*d])
	    || (i > inv[p[i]+d] && inv[p[i]+d] > inv[p[i]+2*d])) {
	  bad = 1;
	}
      }
    }

    cout << (bad ? "no" : "yes") << endl;
    cin >> n;
  }
  return 0;
}
