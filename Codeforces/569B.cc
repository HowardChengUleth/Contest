#include <bits/stdc++.h>

using namespace std;

// The idea is that any numbers that are repeated has to be reassigned.
// It doesn't actually matter to what, because there will be empty spots.
// So we just have to check this with a boolean array and assign one of the
// empty spots

int main()
{
  bool seen[100001] = {false};
  int a[100001];
  int n;

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i] > n) continue;
    seen[a[i]] = true;
  }

  bool seen2[100001] = {false};
  int empty = 1;
  for (int i = 0; i < n; i++) {
    if (1 <= a[i] && a[i] <= n && !seen2[a[i]]) {
      cout << a[i] << ' ';
    } else {
      while (seen[empty]) empty++;
      seen[empty] = true;
      cout << empty << ' ';
    }
    seen2[a[i]] = true;
  }
  cout << endl;

  return 0;
}
