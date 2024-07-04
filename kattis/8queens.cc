#include <bits/stdc++.h>

using namespace std;

int main()
{
  int row[8] = {0}, col[8] = {0};
  int diag1[15] = {0}, diag2[15] = {0};
  int queens = 0;
  
  string line;

  for (int r = 0; r < 8; r++) {
    for (int c = 0; c < 8; c++) {
      char ch;
      cin >> ch;
      if (ch == '.') continue;
      row[r]++;
      col[c]++;
      diag1[r+c]++;
      diag2[r-c+7]++;
      queens++;
    }
  }

  bool good = queens == 8;
  for (int i = 0; i < 8; i++) {
    good &= (row[i] == 1 && col[i] == 1);
  }
  for (int i = 0; i < 15; i++) {
    good &= (diag1[i] <= 1 && diag2[i] <= 1);
  }

  if (good) {
    cout << "valid" << endl;
  } else {
    cout << "invalid" << endl;
  }

  return 0;
}
