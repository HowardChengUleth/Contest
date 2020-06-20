#include <bits/stdc++.h>

using namespace std;

// if anything is out of place, then it must be an even element in an odd spot
// or vice versa.  The only way to fix it is to swap an out of place even
// element with an out of place odd element.  So count each type and make
// sure the number are the same

int main()
{
  int t;
  cin >> t;
  while (t--) {
    int bad[2] = {0};
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
      int a;
      cin >> a;
      if (i % 2 != a % 2) {
	bad[i%2]++;
      }
    }
    if (bad[0] == bad[1]) {
      cout << bad[0] << endl;
    } else {
      cout << -1 << endl;
    }

  }
  return 0;
}
