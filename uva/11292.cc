#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
  int n, m;
  int d[20000], h[20000];
  
  while (cin >> n >> m && (n || m)) {
    for (int i = 0; i < n; i++) {
      cin >> d[i];
    }
    for (int i = 0; i < m; i++) {
      cin >> h[i];
    }
    sort(d, d+n);
    sort(h, h+m);
    
    int di = 0, hi = 0;
    int sum = 0;

    while (di < n && hi < m) {
      if (d[di] > h[hi]) {
	hi++;
      } else if (d[di] <= h[hi]) {
	sum += h[hi];
	di++;
	hi++;
      }
    }
    if (di < n) {
      cout << "Loowater is doomed!" << endl;
    } else {
      cout << sum << endl;
    }
  }
  
  
  return 0;
}
