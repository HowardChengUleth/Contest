#include <bits/stdc++.h>

using namespace std;
vector<string> grid;

void expand()
{
  for (int i = grid.size()-1; i >= 0; i--) {
    if (count(begin(grid[i]), end(grid[i]), '#') == 0) {
      for (int j = 0; j < (int)grid[i].size(); j++) {
	grid[i][j] = '*';
      }
    }
  }

  for (int j = grid[0].size()-1; j >= 0; j--) {
    int c = 0;
    for (int i = 0; i < (int)grid.size(); i++) {
      c += grid[i][j] == '#';
    }
    if (c) continue;
    for (int i = 0; i < (int)grid.size(); i++) {
      grid[i][j] = '*';
    }
  }
}

typedef long long ll;
typedef tuple<ll, int, int> ti3;

void dijkstra(int sr, int sc, vector<vector<ll>> &dist)
{
  const int EXPAND = 100;
  
  int M = grid.size();
  int N = grid[0].size();
  
  dist.resize(M, vector<ll>(N, -1));

  priority_queue<ti3, vector<ti3>, greater<ti3>> PQ;
  dist[sr][sc] = 0;
  PQ.emplace(0, sr, sc);

  while (!PQ.empty()) {
    auto [d, r, c] = PQ.top();
    PQ.pop();

    const int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};
    for (int dir = 0; dir < 4; dir++) {
      int r2 = r + dr[dir], c2 = c + dc[dir];
      if (0 <= r2 && r2 < M && 0 <= c2 && c2 < N &&
	  dist[r2][c2] == -1) {
	ll cost = (grid[r2][c2] == '*') ? EXPAND : 1;
	dist[r2][c2] = dist[r][c] + cost;
	PQ.emplace(dist[r2][c2], r2, c2);
      }
    }
  }
  /*
  for (auto s : grid) {
    cout << s << endl;
  }
  cout << "=========" << endl;
  for (auto v : dist) {
    for (auto d : v) {
      cout << setw(4) << d;
    }
    cout << endl;
  }
  cout << "============" << endl;
  */
  
}

int main()
{
  string line;
  while (getline(cin, line)) {
    grid.push_back(line);
  }

  expand();
  
  vector<int> row, col;
  for (int r = 0; r < (int)grid.size(); r++) {
    for (int c = 0; c < (int)grid[0].size(); c++) {
      if (grid[r][c] == '#') {
	row.push_back(r);
	col.push_back(c);
      }
    }
  }

  ll sum = 0;
  for (int i = 0; i < (int)row.size(); i++) {
    vector<vector<ll>> dist;
    dijkstra(row[i], col[i], dist);
    for (int j = i+1; j < (int)row.size(); j++) {
      sum += dist[row[j]][col[j]];
    }
  }

  cout << sum << endl;
  return 0;
}
