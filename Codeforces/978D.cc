#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  int b[100000];

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }

  if (n <= 2) {
    cout << 0 << endl;
    return 0;
  }

  int best_ans = n+1;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      int diff = b[1] - b[0] + j - i;
      bool good = true;
      int ans = (i != 0) + (j != 0);
      for (int k = 2; k < n && good; k++) {
	int d2 = b[k] - (b[0] + i + diff*k);
	if (d2 == -1 || d2 == 1) {
	  ans++;
	} else if (d2) {
	  good = false;
	}
      }
      if (good) {
	best_ans = min(best_ans, ans);
      }
    }
  }
  if (best_ans > n) {
    cout << -1 << endl;
  } else {
    cout << best_ans << endl;
  }

  return 0;
}
