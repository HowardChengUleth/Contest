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

vector<string> grid;

int count_nbrs(int r, int c)
{
  int nbrs = 0;
  for (int i = r-1; i <= r+1; i++) {
    for (int j = c-1; j <= c+1; j++) {
      if (inside(i, j) && !(i == r && j == c) && grid[i][j] == '@') {
	nbrs++;
      }
    }
  }
  return nbrs;
}

int main()
{
  string s;
  while (getline(cin, s)) {
    grid.push_back(s);
  }
  M = grid.size();
  N = grid[0].size();

  int ans = 0;
  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      if (grid[r][c] != '@') continue;
      if (count_nbrs(r, c) < 4) {
	ans++;
      }
    }
  }

  cout << ans << endl;
  return 0;
}
