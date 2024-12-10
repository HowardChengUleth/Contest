#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

int M, N;

vvi read_input()
{
  vvi grid;

  string line;
  while (getline(cin, line)) {
    vi row;
    for (auto ch : line) {
      row.push_back(ch - '0');
    }
    grid.push_back(row);
  }

  M = grid.size();
  N = grid[0].size();
  
  return grid;
}

const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

bool inside(int r, int c)
{
  return 0 <= r && r < M && 0 <= c && c < N;
}

int find_head(const vvi &grid, int r, int c)
{
  int ans = 0;
  
  typedef pair<int,int> pii;
  queue<pii> Q;
  set<pii> visited;
  
  Q.emplace(r, c);
  visited.emplace(r, c);

  while (!Q.empty()) {
    auto [curr_r, curr_c] = Q.front();
    Q.pop();

    int curr_h = grid[curr_r][curr_c];
    if (curr_h == 0) {
      ans++;
      continue;
    }

    for (int d = 0; d < 4; d++) {
      int next_r = curr_r + dr[d];
      int next_c = curr_c + dc[d];
      if (inside(next_r, next_c) && grid[next_r][next_c] == curr_h-1 &&
	  visited.count(pii(next_r, next_c)) == 0) {
	Q.emplace(next_r, next_c);
	visited.emplace(next_r, next_c);
      }
    }
  }

  return ans;
}

int main()
{
  int ans = 0;
  vvi grid = read_input();
  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      if (grid[r][c] == 9) {
	ans += find_head(grid, r, c);
      }
    }
  }

  cout << ans << endl;

  return 0;
}
