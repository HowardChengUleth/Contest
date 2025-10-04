#include <bits/stdc++.h>

using namespace std;

int h, w;

int f(const vector<string> &field, vector<vector<int>> &best,
      int r, int c)
{
  int &ans = best[r][c];

  if (ans >= 0) {
    return ans;
  }
  
  ans = (field[r][c] == 'I');
  int right = 0, down = 0;
  
  if (r < h-1) {
    down = f(field, best, r+1, c);
  }

  if (c < w-1) {
    right = f(field, best, r, c+1);
  }

  return ans += max(down, right);
}

int main()
{
  cin >> h >> w;

  vector<string> field(h);
  for (auto &s : field) {
    cin >> s;
  }

  vector<vector<int>> best(h, vector<int>(w, -1));

  cout << f(field, best, 0, 0) << endl;

  return 0;
}
