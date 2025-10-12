#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;

  for (int i = 0; i < 100; i++) {
    cin >> n;
  }

  n %= 10;
  if (n == 0) {
    cout << 10 << endl;
  } else {
    cout << n << endl;
  }
  return 0;
}
