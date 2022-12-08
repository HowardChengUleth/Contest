#include <bits/stdc++.h>

using namespace std;

vector<string> H;
int m, n;

int line(int r, int c, int dr, int dc)
{
  int height = H[r][c] - '0';

  int count = 0;
  while (true) {
    r += dr;
    c += dc;
    if (!(0 <= r && r < m && 0 <= c && c < n)) break;

    count++;
    if (H[r][c] - '0' >= height) break;
  }
  return count;
}

int score(int r, int c)
{
  return line(r, c, 1, 0) * line(r, c, -1, 0) * line(r, c, 0, 1) * line(r, c, 0, -1);
}

int main()
{
  string line;
  while (getline(cin, line)) {
    H.push_back(line);
  }

  m = H.size();
  n = H[0].size();
  int best = 0;
  for (int r = 0; r < m; r++) {
    for (int c = 0; c < n; c++) {
      best = max(best, score(r,c));
    }
  }

  cout << best << endl;
  return 0;
}
