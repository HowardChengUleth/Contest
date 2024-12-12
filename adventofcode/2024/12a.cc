#include <bits/stdc++.h>

using namespace std;

typedef vector<string> vs;
typedef vector<vector<bool>> vvb;
typedef long long ll;
typedef pair<int,int> pii;

int M, N;
vs grid;

void read_grid()
{
  string s;
  while (getline(cin, s)) {
    grid.push_back(s);
  }
  M = grid.size();
  N = grid[0].length();
}

bool inside(int r, int c)
{
  return 0 <= r && r < M && 0 <= c && c < N;
}

const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };

ll score(int r, int c, vvb &marked)
{
  char type = grid[r][c];

  queue<pii> Q;
  Q.emplace(r, c);
  
  ll area = 0;
  ll peri = 0;

  while (!Q.empty()) {
    auto [curr_r, curr_c] = Q.front();
    Q.pop();
    bool first = !marked[curr_r][curr_c];
    marked[curr_r][curr_c] = true;

    if (first) {
      area++;
      for (int d = 0; d < 4; d++) {
	int r2 = curr_r + dr[d], c2 = curr_c + dc[d];
	if (!inside(r2, c2) || grid[r2][c2] != type) {
	  peri++;
	}
	
	if (inside(r2, c2) && grid[r2][c2] == type && !marked[r2][c2]) {
	  Q.emplace(r2, c2);
	}
      }
    }
  }

  return area * peri;
}

int main()
{
  read_grid();

  vvb marked(M, vector<bool>(N, false));

  ll ans = 0;
  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      if (marked[r][c]) continue;
      ans += score(r, c, marked);
    }
  }

  cout << ans << endl;

  return 0;
}
