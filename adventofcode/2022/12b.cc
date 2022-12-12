#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

int main()
{
  vector<string> grid;
  string line;
  while (getline(cin, line)) {
    grid.push_back(line);
  }

  int m = grid.size();
  int n = grid[0].size();

  pii S, E;
  for (int r = 0; r < m; r++) {
    for (int c = 0; c < n; c++) {
      if (grid[r][c] == 'S') {
	S = pii(r, c);
	grid[r][c] = 'a';
      } else if (grid[r][c] == 'E') {
	E = pii(r, c);
	grid[r][c] = 'z';
      }
    }
  }

  int D[100][100];
  for (int r = 0; r < m; r++) {
    fill(D[r], D[r]+n, -1);
  }
  D[E.first][E.second] = 0;

  queue<pii> Q;
  Q.push(E);
  while (!Q.empty()) {
    auto curr = Q.front();
    Q.pop();
    if (grid[curr.first][curr.second] == 'a') {
      cout << D[curr.first][curr.second] << endl;
      break;
    }

    const int dr[] = {-1, 1, 0, 0};
    const int dc[] = {0, 0, -1, 1};
    for (int d = 0; d < 4; d++) {
      int r2 = curr.first + dr[d];
      int c2 = curr.second + dc[d];
      if (0 <= r2 && r2 < m && 0 <= c2 && c2 < n &&
	  D[r2][c2] == -1 &&
	  grid[r2][c2] + 1 >= grid[curr.first][curr.second]) {
	Q.emplace(r2, c2);
	D[r2][c2] = D[curr.first][curr.second]+1;
      }
    }
  }

  return 0;
}
