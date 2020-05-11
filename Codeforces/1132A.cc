#include <bits/stdc++.h>

using namespace std;

int main()
{
  int c1, c2, c3, c4;
  cin >> c1 >> c2 >> c3 >> c4;

  bool good = (c1 == c4) && (c3 == 0 || c1 > 0);
  cout << (good ? 1 : 0) << endl;
  return 0;
}
