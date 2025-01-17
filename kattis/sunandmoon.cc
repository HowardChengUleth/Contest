#include <bits/stdc++.h>

using namespace std;

int main()
{
  int ds, ys, dm, ym;
  cin >> ds >> ys >> dm >> ym;

  for (int i = 0; i <= 5000; i++) {
    if (ds == 0 && dm == 0) {
      cout << i << endl;
      break;
    }

    ds++;
    dm++;
    ds %= ys;
    dm %= ym;
  }

  
  return 0;
}
