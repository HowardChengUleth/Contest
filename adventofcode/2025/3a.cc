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

int bank(const string &s)
{
  int ans = 0;
  for (int i = 0; i < N-1; i++) {
    for (int j = i+1; j < N; j++) {
      int t = (s[i] - '0')*10 + (s[j] - '0');
      ans = max(t, ans);
    }
  }
  return ans;
}

int main()
{
  vector<string> grid;
  string line;
  while (getline(cin, line)) {
    grid.push_back(line);
  }
  M = grid.size();
  N = grid[0].size();

  int64_t ans = 0;
  for (auto s : grid) {
    ans += bank(s);
  }

  cout << ans << endl;

  return 0;
}
