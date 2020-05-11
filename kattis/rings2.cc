#include <bits/stdc++.h>

using namespace std;

int n, m;
char grid[102][102];
int dist[102][102];

typedef pair<int,int> pii;

int main()
{
  cin >> n >> m;
  int max_d = 0;

  queue<pii> q;
  for (int i = 0; i < n+2; i++) {
    for (int j = 0; j < m+2; j++) {
      if (i == 0 || j == 0 || i == n+1 || j == m+1) {
	grid[i][j] = '.';
      }	else {
	cin >> grid[i][j];
      }
      if (grid[i][j] == '.') {
	dist[i][j] = 0;
	q.emplace(i, j);
      } else {
	dist[i][j] = -1;
      }
    }
  }
  
  const int dr[] = {-1,1,0,0}, dc[] = {0,0,-1,1};
  while (!q.empty()) {
    pii curr = q.front();
    q.pop();
    int r = curr.first, c = curr.second;
    for (int d = 0; d < 4; d++) {
      int r2 = r + dr[d], c2 = c + dc[d];
      if (!(1 <= r2 && r2 <= n && 1 <= c2 && c2 <= m)) continue;
      if (dist[r2][c2] >= 0) continue;
      dist[r2][c2] = dist[r][c]+1;
      max_d = max(max_d, dist[r2][c2]);
      q.emplace(r2,c2);
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (dist[i][j] == 0) cout << ((max_d < 10) ? ".." : "...");
      else cout << setfill('.') << setw((max_d < 10) ? 2 : 3) << dist[i][j];
    }
    cout << endl;
  }
  
  
  return 0;
}
