#include <bits/stdc++.h>

using namespace std;

int main()
{
  int x, y, z, a, b, c;

  cin >> x >> y >> z;
  cin >> a >> b >> c;

  bool good = x <= a && (x+y+z <= a+b+c);
  a -= x;
  good &= y <= a + b;

  cout << (good ? "YES" : "NO") << endl;
  
  
  return 0;
}
