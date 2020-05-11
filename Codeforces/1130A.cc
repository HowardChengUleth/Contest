#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  int pos = 0, neg = 0;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    if (a > 0) pos++;
    if (a < 0) neg++;
  }

  if (pos >= (n+1)/2) {
    cout << 1 << endl;
  } else if (neg >= (n+1)/2) {
    cout << -1 << endl;
  } else {
    cout << 0 << endl;
  }
  return 0;
}
