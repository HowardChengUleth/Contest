#include <bits/stdc++.h>

using namespace std;

int grid[500][500];
int dist[500][500];

int main()
{
  int n, m;
  cin >> n >> m;
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < m; c++) {
      char ch;
      cin >> ch;
      grid[r][c] = ch - '0';
      dist[r][c] = -1;
    }
  }

  queue<pair<int,int>> Q;
  Q.emplace(0, 0);
  dist[0][0] = 0;

  const int dr[] = {-1, 1, 0, 0};
  const int dc[] = {0, 0, -1, 1};
  
  while (!Q.empty()) {
    auto [r, c] = Q.front();
    Q.pop();
    int d = grid[r][c];
    for (int dir = 0; dir < 4; dir++) {
      int r2 = r + d * dr[dir];
      int c2 = c + d * dc[dir];
      if (0 <= r2 && r2 < n && 0 <= c2 && c2 < m
	  && dist[r2][c2] == -1) {
	dist[r2][c2] = dist[r][c] + 1;
	Q.emplace(r2, c2);
      }
    }
  }

  cout << dist[n-1][m-1] << endl;


  return 0;
}
