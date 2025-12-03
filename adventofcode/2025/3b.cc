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

vector<vector<int64_t>> memo;

int64_t bank(const string &s, int num, int need = 12)
{
  if (num < need) {
    return -1;
  }
  if (need == 0) {
    return 0;
  }
  
  auto &ans = memo[num][need];
  if (ans != -1) {
    return ans;
  }

  // try taking the digit
  auto ans1 = bank(s, num-1, need-1) * 10 + s[num-1] - '0';

  // try not taking it
  auto ans2 = bank(s, num-1, need);
  
  return ans = max(ans1, ans2);
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
    memo.clear();
    memo.resize(N+1, vector<int64_t>(13, -1));
    ans += bank(s, N);
  }

  cout << ans << endl;

  return 0;
}
