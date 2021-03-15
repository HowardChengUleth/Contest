#include <bits/stdc++.h>

using namespace std;

int region[12][12];
int col[11] = {0}, reg[10] = {0};
char soln[12][12] = { 0 };

bool checkadj(int r, int c)
{
  for (int cc = c-1; cc <= c+1; cc++) {
    if (soln[r-1][cc] == '*') return false;
  }

  return true;

}

void solve(int r)
{
  if (r > 10) {
    for (int i = 1; i <= 10; i++) {
      for (int j = 1; j <= 10; j++) {
	cout << soln[i][j];
      }
      cout << endl;
    }
    return;
  }

  for (int c1 = 1; c1 <= 10; c1++) {
    if (!checkadj(r, c1) || col[c1] == 2) continue;
    if (reg[region[r][c1]] == 2) continue;
    col[c1]++;
    reg[region[r][c1]]++;
    soln[r][c1] = '*';
    for (int c2 = c1+2; c2 <= 10; c2++) {
      if (!checkadj(r, c2) || col[c2] == 2) continue;
      if (reg[region[r][c2]] == 2) continue;
      col[c2]++;
      reg[region[r][c2]]++;
      soln[r][c2] = '*';
      solve(r+1);
      soln[r][c2] = '.';
      col[c2]--;
      reg[region[r][c2]]--;
    }

    soln[r][c1] = '.';
    col[c1]--;
    reg[region[r][c1]]--;
  }
  

}

int main()
{

  char ch;
  for (int r = 1; r <= 10; r++) {
    for (int c = 1; c <= 10; c++) {
      cin >> ch;
      region[r][c] = ch - '0';
      soln[r][c] = '.';
    }
  }

  solve(1);
  
  return 0;
}
