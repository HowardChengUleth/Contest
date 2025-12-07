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

vector<string> grid;
vector<vector<int64_t>> memo;

int64_t f(int r, int c)
{
  if (r >= M) {
    return 1;
  }
  if (c < 0 || c >= N) {
    return 0;
  }

  int64_t &ans = memo[r][c];
  if (ans >= 0) {
    return ans;
  }

  if (grid[r][c] != '^') {
    return ans = f(r+1, c);
  } else {
    return ans = f(r+1, c-1) + f(r+1, c+1);
  }
}


int main()
{
  string line;
  while (getline(cin, line)) {
    grid.push_back(line);
  }
  M = grid.size();
  N = grid[0].length();

  memo.resize(M, vector<int64_t>(N, -1));

  for (int j = 0; j < N; j++) {
    if (grid[0][j] == 'S') {
      cout << f(0, j) << endl;
    }
  }

  return 0;
}
