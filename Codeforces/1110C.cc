#include <bits/stdc++.h>

using namespace std;

int ones[26];
int largest[26];

int solve(int a)
{
  int index = lower_bound(ones, ones+26, a) - ones;
  if (ones[index] != a) {
    return ones[index];
  } else {
    return largest[index];
  }
}

int main()
{
  for (int i = 0; i < 26; i++) {
    ones[i] = (1 << i) - 1;
    largest[i] = 1;
    for (long long k = 2; k*k <= ones[i]; k++) {
      if (ones[i] % k == 0) {
	largest[i] = max(largest[i], max<int>(k, ones[i]/k));
      }
    }
  }

  int q;
  cin >> q;
  while (q--) {
    int a;
    cin >> a;
    cout << solve(a) << endl;
  }
  
  return 0;
}
