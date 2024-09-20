#include <bits/stdc++.h>

using namespace std;

int main()
{
  int p, q, s;
  cin >> p >> q >> s;
  
  for (int t = 1; t <= s; t++) {
    if (t % p == 0 && t % q == 0) {
      cout << "yes" << endl;
      return 0;
    }
  }

  cout << "no" << endl;

  return 0;
}
