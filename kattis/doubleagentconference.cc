#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n[3];
  for (int i = 0; i < 3; i++) {
    cin >> n[i];
  }

  int mask[100000] = {0};

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < n[i]; j++) {
      int x;
      cin >> x;
      mask[x] |= (1 << i);
    }
  }

  int count[8] = {0};
  for (int i = 0; i < 100000; i++) {
    count[mask[i]]++;
  }

  int ans = count[7] + count[6] + count[5] + count[3] +
    max(0, max(
	       max(count[1] - count[6], count[2] - count[5]),
	       count[4] - count[3]));
  cout << ans << endl;

  return 0;
}
