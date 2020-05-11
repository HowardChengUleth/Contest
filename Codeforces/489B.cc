#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n, m;
  int a[100], b[100];

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  cin >> m;
  for (int i = 0; i < m; i++) {
    cin >> b[i];
  }

  sort(a, a+n);
  sort(b, b+m);

  int ai = 0, bi = 0;
  int count = 0;
  
  while (ai < n && bi < m) {
    int diff = a[ai] - b[bi];
    if (-1 <= diff && diff <= 1) {
      count++;
      ai++;
      bi++;
    } else if (diff > 0) {
      bi++;
    } else {
      ai++;
    }
  }

  cout << count << endl;


  return 0;
}
