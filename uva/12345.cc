#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
  int n, m;
  cin >> n >> m;

  int a[50000];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  // for query q (1 <= q <= m), if present[i] = q then i appears in the
  // subarray specified in the query
  int present[1000001];
  fill(present, present+1000001, 0);

  for (int q = 1; q <= m; q++) {
    char cmd;
    int x, y;
    cin >> cmd >> x >> y;
    if (cmd == 'M') {
      a[x] = y;
      continue;
    }

    int ans = 0;
    for (int k = x; k < y; k++) {
      if (present[a[k]] != q) {
	present[a[k]] = q;
	ans++;
      }
    }
    cout << ans << endl;
  }

  
  return 0;
}
