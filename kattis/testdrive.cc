#include <bits/stdc++.h>

using namespace std;

int main()
{
  int a, b, c;
  cin >> a >> b >> c;

  int d1 = b - a;
  int d2 = c - b;

  if (d1 == d2) {
    cout << "cruised" << endl;
  } else if (d1 * d2 < 0) {
    cout << "turned" << endl;
  } else if (abs(d1) < abs(d2)) {
    cout << "accelerated" << endl;
  } else {
    cout << "braked" << endl;
  }

  return 0;
}
