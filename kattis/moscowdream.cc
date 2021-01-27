#include <bits/stdc++.h>

using namespace std;

int main()
{
  int a, b, c, n;
  cin >> a >> b >> c >> n;
  if (a+b+c >= n && a && b && c && n >= 3) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }

  return 0;
}
