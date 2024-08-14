#include <bits/stdc++.h>

using namespace std;

int main()
{
  int region[12][12];
  char soln[12][12] = { 0 };

  char ch;
  for (int r = 1; r <= 10; r++) {
    for (int c = 1; c <= 10; c++) {
      cin >> ch;
      region[r][c] = ch - '0';
    }
  }

  for (int r = 1; r <= 10; r++) {
    for (int c = 1; c <= 10; c++) {
      cin >> soln[r][c];
    }
  }

  bool valid = true;
  int row[11] = {0}, col[11] = {0}, reg[10] = {0};
  
  for (int r = 1; r <= 10; r++) {
    for (int c = 1; c <= 10; c++) {
      if (soln[r][c] == '.') continue;
      row[r]++;
      col[c]++;
      reg[region[r][c]]++;

      int count = 0;
      for (int rr = r-1; rr <= r+1; rr++) {
	for (int cc = c-1; cc <= c+1; cc++) {
	  if (soln[rr][cc] == '*')
	    count++;
	}
      }
      if (count != 1) {
	valid = false;
      }
    }
  }

  for (int i = 0; i < 10; i++) {
    valid &= (row[i+1] == 2) && (col[i+1] == 2) && (reg[i] == 2);
  }
  cout << (valid ? "valid" : "invalid") << endl;
  

  return 0;
}
