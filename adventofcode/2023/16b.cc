#include <bits/stdc++.h>

using namespace std;

int M, N;
vector<string> grid;
vector<vector<int>> visited;

// 0 = N, 1 = E, 2 = S, 3 = W
const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

int nextdir[256][4];

void init()
{
  for (int i = 0; i < 4; i++) {
    nextdir['.'][i] = 1 << i;
  }

  nextdir['/'][0] = 1 << 1;
  nextdir['/'][1] = 1 << 0;
  nextdir['/'][2] = 1 << 3;
  nextdir['/'][3] = 1 << 2;

  nextdir['\\'][0] = 1 << 3;
  nextdir['\\'][1] = 1 << 2;
  nextdir['\\'][2] = 1 << 1;
  nextdir['\\'][3] = 1 << 0;

  nextdir['|'][0] = 1 << 0;
  nextdir['|'][1] = (1 << 0) | (1 << 2);
  nextdir['|'][2] = 1 << 2;
  nextdir['|'][3] = (1 << 0) | (1 << 2);

  nextdir['-'][0] = (1 << 1) | (1 << 3);
  nextdir['-'][1] = 1 << 1;
  nextdir['-'][2] = (1 << 1) | (1 << 3);
  nextdir['-'][3] = 1 << 3;
}

bool inside(int r, int c)
{
  return 0 <= r && r < M && 0 <= c && c < N;
}

void trace(int r, int c, int dir)
{
  visited[r][c] |= (1 << dir);
  int next = nextdir[(int)grid[r][c]][dir];

  for (int d = 0; d < 4; d++) {
    if (next & (1 << d)) {
      int r2 = r + dr[d];
      int c2 = c + dc[d];
      if (!inside(r2, c2)) continue;
      if (visited[r2][c2] & (1 << d)) continue;
      trace(r2, c2, d);
    }
  }
}

int start_trace(int r, int c, int dir)
{
  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      visited[r][c] = 0;
    }
  }
  trace(r, c, dir);

  int ans = 0;
  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      if (visited[r][c]) {
	ans++;
      }
    }
  }

  return ans;
}

int try_all()
{
  int ans = 0;
  for (int c = 0; c < N; c++) {
    ans = max(ans, start_trace(0, c, 2));
    ans = max(ans, start_trace(M-1, c, 0));
  }
  for (int r = 0; r < M; r++) {
    ans = max(ans, start_trace(r, 0, 1));
    ans = max(ans, start_trace(r, N-1, 3));
  }
  return ans;
}

int main()
{
  init();
  
  string line;
  while (getline(cin, line)) {
    grid.push_back(line);
  }

  M = grid.size();
  N = grid[0].size();
  visited.resize(M, vector<int>(N, 0));
  
  cout << try_all() << endl;

  return 0;
}
