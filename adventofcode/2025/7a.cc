#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int M, N;

bool inside(int r, int c)
{
  return 0 <= r && r < M && 0 <= c && c < N;
}

const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };

int main()
{
  vector<string> grid;
  string line;
  while (getline(cin, line)) {
    grid.push_back(line);
  }
  M = grid.size();
  N = grid[0].length();

  int split = 0;
  
  replace(begin(grid[0]), end(grid[0]), 'S', '|');
  for (int i = 1; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (grid[i][j] == '.') {
	if (grid[i-1][j] == '|') {
	  grid[i][j] = '|';
	}
      } else if (grid[i][j] == '^') {
	if (grid[i-1][j] == '|') {
	  split++;
	  if (j-1 >= 0) {
	    grid[i][j-1] = '|';
	  }
	  if (j+1 < N) {
	    grid[i][j+1] = '|';
	  }
	}
      }
    }
  }

  cout << split << endl;

  return 0;
}
