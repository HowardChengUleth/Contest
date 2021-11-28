#include <bits/stdc++.h>

using namespace std;

int main()
{
  int a, b, c;
  cin >> a >> b >> c;

  // a^(b^c) = (a^b)^c
  // <==> b^c = c * log_a (a^b)        assuming a != 1
  // <==> b^c = b*c                  
  // <==> (b = c = 2) or (c = 1)

  if (a == 1 || (b == 2 && c == 2) || (c == 1)) {
    cout << "What an excellent example!" << endl;
  } else {
    cout << "Oh look, a squirrel!" << endl;
  }
  
  return 0;
}
