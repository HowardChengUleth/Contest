#include <bits/stdc++.h>

using namespace std;

int main()
{
  int a, b, h;

  cin >> a >> b >> h;

  int curr = 0;
  int day = 0;

  while (curr < h) {
    day++;
    curr += a;
    if (curr >= h) break;
    curr -= b;
  }

  cout << day << endl;

  return 0;
}
