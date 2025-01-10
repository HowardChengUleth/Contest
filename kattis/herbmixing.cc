#include <bits/stdc++.h>

using namespace std;

int main()
{
  int boost = 0;
  int G, R;
  cin >> G >> R;

  boost += 10 * min(G, R);
  G -= min(G, R);

  boost += 10 * (G/3);
  G %= 3;

  boost += 3 * (G/2);
  G %= 2;

  boost += G;

  cout << boost << endl;

  
  return 0;
}
