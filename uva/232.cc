#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void print_string(const string puzzle[10], int r, int c, int i, int j, 
		  int dr, int dc)
{
  do {
    cout << puzzle[i][j];
    i += dr;
    j += dc;
  } while (i < r && j < c && puzzle[i][j] != '*');
  cout << endl;

}

void solve(int r, int c)
{
  int label[10][10];
  bool across[10][10];
  bool down[10][10];
  string puzzle[10];
  int next_label = 1;

  getline(cin, puzzle[0]);
  for (int i = 0; i < r; i++) {
    getline(cin, puzzle[i]);
  }

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      across[i][j] = down[i][j] = false;
      label[i][j] = -1;
      if (puzzle[i][j] == '*') {
	continue;
      }

      across[i][j] = (j == 0 || puzzle[i][j-1] == '*');
      down[i][j] = (i == 0 || puzzle[i-1][j] == '*');
      if (across[i][j] || down[i][j]) {
	label[i][j] = next_label++;
      }
    }
  }

  cout << "Across" << endl;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (!across[i][j]) continue;
      cout << setw(3) << label[i][j] << ".";
      print_string(puzzle, r, c, i, j, 0, 1);
    }
  }

  cout << "Down" << endl;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (!down[i][j]) continue;
      cout << setw(3) << label[i][j] << ".";
      print_string(puzzle, r, c, i, j, 1, 0);
    }
  }
}

int main(void)
{
  int r, c;
  int p = 1;
  while (cin >> r >> c && r) {
    if (p > 1) cout << endl;
    cout << "puzzle #" << p++ << ":" << endl;
    solve(r, c);
  }
  return 0;
}
