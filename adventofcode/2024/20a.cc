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

typedef vector<string> vs;

vs grid;

int start_r, start_c, end_r, end_c;

void read_grid()
{
  string s;
  while (cin >> s) {
    grid.push_back(s);
  }
  M = grid.size();
  N = grid[0].size();

  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      if (grid[r][c] == 'S') {
	start_r = r;
	start_c = c;
      } else if (grid[r][c] == 'E') {
	end_r = r;
	end_c = c;
      }
    }
  }
}

// dist to end
vector<vector<int>> dist;
typedef pair<int,int> pii;

void compute_dist()
{
  dist.resize(M, vector<int>(N, -1));
  queue<pii> Q;

  Q.emplace(end_r, end_c);
  dist[end_r][end_c] = 0;

  while (!Q.empty()) {
    auto [curr_r, curr_c] = Q.front();
    Q.pop();
    if (grid[curr_r][curr_c] == 'S') continue;
    for (int d = 0; d < 4; d++) {
      int r2 = curr_r + dr[d], c2 = curr_c + dc[d];
      if (inside(r2, c2) && grid[r2][c2] != '#' &&
	  dist[r2][c2] == -1) {
	Q.emplace(r2, c2);
	dist[r2][c2] = dist[curr_r][curr_c] + 1;
      }
    }
  }
}

map<int,int> cheat;

void find_cheat()
{
  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      if (dist[r][c] == -1) continue;
      for (int d = 0; d < 4; d++) {
	int r2 = r + dr[d], c2 = c + dc[d];
	int r3 = r2 + dr[d], c3 = c2 + dc[d];
	if (!inside(r3, c3)) continue;
	if (grid[r2][c2] != '#') continue;
	if (dist[r3][c3] == -1) continue;

	int orig_d = dist[r][c];
	int new_d = dist[r3][c3] + 2;
	int saved = orig_d - new_d;
	if (saved > 0) {
	  cheat[saved]++;
	}
      }
    }
  }

}

int main()
{
  read_grid();
  compute_dist();
  find_cheat();

  int ans = 0;
  for (auto [p, f] : cheat) {
    if (p >= 100) {
      ans += f;
    }
  }

  cout << ans << endl;
  return 0;
}
