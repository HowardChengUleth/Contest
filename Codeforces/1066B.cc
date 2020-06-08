#include <bits/stdc++.h>

using namespace std;


// the idea is that we try to find the rightmost heater that can heat up the
// first position: that position has to be covered by some heater and it is
// never better to use a heater to the left.  Once the first position is
// covered, we look for the next uncovered position and repeat.

int main()
{
  int n, r;
  cin >> n >> r;

  int a[1000];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  int ans = 0;
  int next = 0;   // next one to cover
  while (next < n) {
    // brute force search.  We could make it O(1) with some preprocessing,
    // if at each location we know where the most recent heater is to the
    // left
    bool found = false;
    for (int i = next + r - 1; i >= next - r + 1 && !found; i--) {
      if (i >= n || i < 0) continue;
      if (a[i]) {
	ans++;
	next = i + r;
	found = true;
      }
    }
    if (!found) {
      cout << -1 << endl;
      return 0;
    }
  }

  cout << ans << endl;
  return 0;
}
