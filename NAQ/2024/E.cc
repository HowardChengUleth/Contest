#include <bits/stdc++.h>

using namespace std;

// just count

int main()
{
  int n;
  cin >> n;
  n *= 10;

  int freq[51] = {0};
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 5; j++) {
      int x;
      cin >> x;
      freq[x]++;
    }
  }

  bool printed = false;
  for (int i = 1; i <= 50; i++) {
    if (freq[i] > n/5) {
      if (printed)
	cout << ' ';
      cout << i;
      printed = true;
    }
  }

  if (!printed) {
    cout << -1;
  }

  cout << endl;

  return 0;
}
