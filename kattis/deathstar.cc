#include <bits/stdc++.h>

using namespace std;

int main()
{
  int a[1000] = {0};
  int n, m;

  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> m;
      if (i == j) continue;
      a[i] |= m;
      a[j] |= m;
    }
  }

  for (int i = 0; i < n; i++) {
    cout << a[i] << ' ';
  }
  cout << endl;
  return 0;
}
