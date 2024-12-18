#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int M = 71, N = 71;
//const int M = 7, N = 7;


bool inside(int r, int c)
{
  return 0 <= r && r < M && 0 <= c && c < N;
}

const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };

typedef pair<int,int> pii;
vector<pii> pos;

void read_pos()
{
  int x, y;
  char ch;

  while (cin >> x >> ch >> y) {
    pos.emplace_back(x, y);
  }
}

vector<string> grid(M, string(N,'.'));

void mark_fall(pii coord)
{
  auto [x, y] = coord;
  grid[y][x] = '#';
}

int find_exit()
{
  queue<pair<int,int>> Q;
  vector<vector<int>> dist(M, vector<int>(N, -1));

  Q.emplace(0,0);
  dist[0][0] = 0;

  while (!Q.empty()) {
    auto curr = Q.front();
    auto [cr, cc] = curr;
    Q.pop();

    if (cr == M-1 && cc == N-1) {
      return dist[cr][cc];
    }

    for (int d = 0; d < 4; d++) {
      int nr = cr + dr[d], nc = cc + dc[d];
      if (inside(nr, nc) && grid[nr][nc] == '.' &&
	  dist[nr][nc] == -1) {
	Q.emplace(nr, nc);
	dist[nr][nc] = dist[cr][cc]+1;
      }
    }
  }

  assert(false);
  return -1;
}

int main()
{
  read_pos();
  for (int i = 0; i < 1024; i++) {
    mark_fall(pos[i]);
  }

  cout << find_exit() << endl;

  return 0;
}
