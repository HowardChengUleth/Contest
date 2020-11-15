#include <bits/stdc++.h>

using namespace std;

int main()
{
  int a, b, c;
  cin >> a >> b >> c;

  int d1 = b - a, d2 = c - b;

  if (d1*d2 < 0) {
    cout << "turned" << endl;
  } else if (abs(d2) > abs(d1)) {
    cout << "accelerated" << endl;
  } else if (abs(d2) < abs(d1)) {
    cout << "braked" << endl;
  } else {
    cout << "cruised" << endl;
  }
  
  return 0;
}
