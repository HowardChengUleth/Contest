#include <bits/stdc++.h>

using namespace std;

int R, C, n;

typedef pair<int,int> pii;

// r, c, tower ID, dist
typedef tuple<int,int,int,int> ti4;

vector<pii> towers;

// first = dist, second = index of tower
pii dist[500][500][2];

void update(queue<ti4> &q, int r, int c, int tower_index, int d)
{
  pii p(d, tower_index);
  if (p < dist[r][c][0]) {
    dist[r][c][1] = dist[r][c][0];
    dist[r][c][0] = p;
  } else if (p < dist[r][c][1] && dist[r][c][0].second != tower_index) {
    dist[r][c][1] = p;
  } else {
    return;
  }

  q.emplace(r, c, tower_index, d);
}

void print_grid(int k)
{
  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      cout << dist[r][c][k].second << ' ';
    }
    cout << endl;
  }
}

void BFS()
{
  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      dist[r][c][0] = dist[r][c][1] = pii(INT_MAX, -1);
    }
  }
  
  queue<ti4> q;
  for (int i = 0; i < n; i++) {
    auto [r, c] = towers[i];
    update(q, r, c, i+1, 0);
  }

  while (!q.empty()) {
    auto [r, c, ID, len] = q.front();
    q.pop();

    int dr[] = { -1, 1, 0, 0 };
    int dc[] = { 0, 0, -1, 1 };
    
    for (int d = 0; d < 4; d++) {
      int r2 = r + dr[d], c2 = c + dc[d];
      if (0 <= r2 && r2 < R && 0 <= c2 && c2 < C) {
	update(q, r2, c2, ID, len+1);
      }
    }
  }

  for (int k = 0; k < 2; k++) {
    print_grid(k);
  }
}

int main()
{
  cin >> R >> C >> n;

  towers.reserve(n);
  for (int k = 0; k < n; k++) {
    int i, j;
    cin >> i >> j;
    towers.emplace_back(i-1, j-1);
  }

  BFS();
  
  return 0;
}
