#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve()
{
  int n;
  cin >> n;

  vector<int> h(n), w(n);
  for (int i = 0; i < n; i++) {
    cin >> h[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> w[i];
  }

  vector<int> inc(n), dec(n);
  for (int i = 0; i < n; i++) {
    inc[i] = dec[i] = w[i];
    for (int j = 0; j < i; j++) {
      if (h[j] < h[i]) {
	inc[i] = max(inc[i], inc[j] + w[i]);
      } else if (h[j] > h[i]) {
	dec[i] = max(dec[i], dec[j] + w[i]);
      }
    }
  }

  int iw = *max_element(inc.begin(), inc.end());
  int dw = *max_element(dec.begin(), dec.end());
  if (iw >= dw) {
    cout << "Increasing (" << iw << "). Decreasing (" << dw << ")." << endl;
  } else {
    cout << "Decreasing (" << dw << "). Increasing (" << iw << ")." << endl;
  }
}

int main(void)
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ". ";
    solve();
  }

  return 0;
}
