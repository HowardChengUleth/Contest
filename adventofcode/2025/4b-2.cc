#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int M, N;

typedef pair<int,int> pii;

bool inside(int r, int c)
{
  return 0 <= r && r < M && 0 <= c && c < N;
}

vector<string> grid;
vector<vector<int>> nbrs;

int count_nbrs(int r, int c)
{
  int nbrs = 0;
  for (int i = r-1; i <= r+1; i++) {
    for (int j = c-1; j <= c+1; j++) {
      if (inside(i, j) && !(i == r && j == c) && grid[i][j] == '@') {
	nbrs++;
      }
    }
  }
  return nbrs;
}

int main()
{
  string s;
  while (getline(cin, s)) {
    grid.push_back(s);
  }
  M = grid.size();
  N = grid[0].size();

  nbrs.resize(M, vector<int>(N, 0));
  queue<pii> Q;
  
  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      if (grid[r][c] == '@' && (nbrs[r][c] = count_nbrs(r, c)) < 4) {
	Q.emplace(r, c);
      }
    }
  }

  int ans = 0;

  while (!Q.empty()) {
    auto [r, c] = Q.front();
    Q.pop();

    ans++;
    for (int i = r-1; i <= r+1; i++) {
      for (int j = c-1; j <= c+1; j++) {
	if (inside(i,j) && grid[i][j] == '@') {
	  if (nbrs[i][j]-- == 4) {
	    Q.emplace(i, j);
	  }
	}
      }
    }
  }
  

  cout << ans << endl;
  return 0;
}
