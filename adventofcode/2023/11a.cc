#include <bits/stdc++.h>

using namespace std;
vector<string> grid;

void expand()
{
  for (int i = grid.size()-1; i >= 0; i--) {
    if (count(begin(grid[i]), end(grid[i]), '#') == 0) {
      grid.insert(begin(grid) + i, grid[i]);
    }
  }

  for (int j = grid[0].size()-1; j >= 0; j--) {
    int c = 0;
    for (int i = 0; i < grid.size(); i++) {
      c += grid[i][j] == '#';
    }
    if (c) continue;
    for (int i = 0; i < grid.size(); i++) {
      grid[i].insert(j, ".");
    }
  }
}

int main()
{
  string line;
  while (getline(cin, line)) {
    grid.push_back(line);
  }

  expand();
  
  vector<int> row, col;
  for (int r = 0; r < grid.size(); r++) {
    for (int c = 0; c < grid[0].size(); c++) {
      if (grid[r][c] == '#') {
	row.push_back(r);
	col.push_back(c);
      }
    }
  }

  int sum = 0;
  for (int i = 0; i < row.size(); i++) {
    for (int j = i+1; j < row.size(); j++) {
      sum += abs(row[i] - row[j]) + abs(col[i] - col[j]);
    }
  }

  cout << sum << endl;
  return 0;
}
