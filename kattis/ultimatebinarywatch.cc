#include <bits/stdc++.h>

using namespace std;

int main()
{
  int digit[4];
  string s;
  cin >> s;
  for (int i = 0; i < 4; i++) {
    digit[i] = s[i] - '0';
  }

  vector<string> grid(4, string(9, ' '));
  const int col[4] = { 0, 2, 6, 8 };
  for (int i = 0; i < 4; i++) {
    for (int j = 3; j >= 0; j--) {
      grid[j][col[i]] = (digit[i] % 2) ? '*' : '.';
      digit[i] /= 2;
    }
  }
  
  for (auto s : grid) {
    cout << s << endl;
  }

  return 0;
}
