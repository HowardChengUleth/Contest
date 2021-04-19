#include <bits/stdc++.h>

using namespace std;

int main()
{
  int D, R, T;
  cin >> D >> R >> T;

  for (int i = 4; true; i++) {
    if (i - D < 0) continue;

    int rita = i*(i+1)/2 - 6;
    int theo = (i-D >= 3) ? (i-D)*(i-D+1)/2 - 3 : 0;

    if (R < rita) continue;
    int diff = R - rita;
    if (T + diff == theo) {
      cout << diff << endl;
      break;
    }

  }
  
  return 0;
}
