#include <bits/stdc++.h>

using namespace std;

int main()
{
  string s;
  cin >> s;

  const int space = 0, lower = 1, upper = 2, symbols = 3;
  int count[4] = {0};
  
  for (auto c : s) {
    if (c == '_') {
      count[space]++;
    } else if (islower(c)) {
      count[lower]++;
    } else if (isupper(c)) {
      count[upper]++;
    } else {
      count[symbols]++;
    }
  }

  for (int i = 0; i < 4; i++) {
    cout << fixed << setprecision(10) << (double)count[i] / s.length() << endl;
  }
    
  return 0;
}
