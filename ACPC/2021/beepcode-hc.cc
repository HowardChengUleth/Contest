#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  vector<int> a(n);
  for (auto &x : a)
    cin >> x;

  char ans[20];
  
  int A = 0, B = 0, Q = 0;
  for (int i = 0 ; i < 20; i++) {
    int pos = (1 << i);
    if (pos >= n) {
      Q++;
      ans[i] = '?';
      continue;
    }
    int prev = a[pos-1] + A - B;
    if (prev < a[pos]) {
      B++;
      ans[i] = 'B';
    } else if (prev > a[pos]) {
      A++;
      ans[i] = 'A';
    } else {
      ans[i] = 'x';
    }
  }

  if (a[0] > A) {
    if (a[0] - A == Q) {
      replace(ans, ans+20, '?', 'A');
    }
  }
  for (int i = 0; i < 20; i++) {
    cout << ans[i] << ' ';
  }
  cout << endl;

  return 0;
}
