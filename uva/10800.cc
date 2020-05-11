#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void solve()
{
  string s;
  cin >> s;

  int n = s.length();
  int width = n+3;

  char grid[200][100];
  for (int i = 0; i < 200; i++) {
    for (int j = 0; j < 100; j++) {
      grid[i][j] = ' ';
    }
  }

  /*
  // do it upside down
  for (int i = 0; i < 200; i++) {
    grid[i][0] = '|';
  }
  for (int j = 1; j < width; j++) {
    grid[0][j] = '-';
  }
  grid[0][0] = '+';
  */

  int r = 100;
  int c = 0;
  int lowest = 200;
  int highest = -1;
  for (int i = 0; i < n; i++, c++) {
    if (s[i] == 'C') {
      grid[r][c] = '_';
      lowest = min(lowest, r);
      highest = max(highest, r);
    } else if (s[i] == 'R') {
      lowest = min(lowest, r);
      highest = max(highest, r);
      grid[r++][c] = '/';
    } else if (s[i] == 'F') {
      grid[--r][c] = '\\';
      lowest = min(lowest, r);
      highest = max(highest, r);
    }
  }

  for (int r = highest; r >= lowest; r--) {
    cout << "| ";
    int end;
    for (end = 99; grid[r][end] == ' '; end--)
      ;
    for (int c = 0; c <= end; c++) {
      cout << grid[r][c];
    }
    cout << endl;
  }
  cout << "+";
  for (int i = 0; i < width-1; i++) {
    cout << "-";
  }
  cout << endl;
}

int main(void)
{
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    cout << "Case #" << i << ":" << endl;
    solve();
    cout << endl;
  }
  return 0;
}
