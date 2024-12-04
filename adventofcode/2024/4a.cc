#include <bits/stdc++.h>

using namespace std;

const string XMAS = "XMAS";

const int dr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dc[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

bool search(const vector<string> &grid, int M, int N, int r, int c, int dir)
{
  for (int i = 0; i < 4; i++) {
    if (!(0 <= r && r < M && 0 <= c && c < N)) return false;
    if (grid[r][c] != XMAS[i]) return false;
    r += dr[dir];
    c += dc[dir];
  }

  return true;
}

int main()
{
  long long ans = 0;

  vector<string> grid;
  string line;
  while (getline(cin, line)) {
    grid.push_back(line);
  }

  int M = grid.size(), N = grid[0].size();
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      for (int dir = 0; dir < 8; dir++) {
	if (search(grid, M, N, i, j, dir)) {
	  ans++;
	}
      }
    }
  }

  cout << ans << endl;
  
  return 0;
}
