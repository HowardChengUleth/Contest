#include <bits/stdc++.h>

using namespace std;

int main()
{
  bool dirty[366] = { false };

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int d;
    cin >> d;
    dirty[d] = true;
  }

  int ans = 0;
  int num_dirty = 0;
  int dirtyness = 0;

  for (int d = 1; d <= 365; d++) {
    dirtyness += num_dirty;
    if (dirtyness >= 20) {
      // clean up the day before
      ans++;
      num_dirty = 0;
      dirtyness = 0;
    }
    
    if (dirty[d]) {
      num_dirty++;
    }
  }

  if (num_dirty > 0) {
    ans++;
  }

  cout << ans << endl;

  
  return 0;
}
