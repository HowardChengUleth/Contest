#include <bits/stdc++.h>

using namespace std;

int R, C;
vector<string> grid;

// longest odd/even vertical and horizontal palindromes "centred" at a
// spot.  For even lengths, centre is rounded down
vector<vector<int>> vert_odd, vert_even, horiz_odd, horiz_even;

// at each spot, the longest palindrome that touches that spot in each
// direction
vector<vector<int>> max_vert, max_horiz;

bool inside(int r, int c)
{
  return (0 <= r && r < R && 0 <= c && c < C);
}

int longest(int r, int c, int dr, int dc, bool odd)
{
  int ans = 0;
  int r2 = r + dr, c2 = c + dc;
  if (odd) {
    ans++;
    r -= dr;
    c -= dc;
  }
  while (inside(r, c) && inside(r2, c2) && grid[r][c] == grid[r2][c2]) {
    ans += 2;
    r -= dr;
    c -= dc;
    r2 += dr;
    c2 += dc;
  }

  return ans;
}

void preprocess()
{
  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      vert_odd[r][c] = longest(r, c, 0, 1, true);
      horiz_odd[r][c] = longest(r, c, 1, 0, true);
      vert_even[r][c] = longest(r, c, 0, 1, false);
      horiz_even[r][c] = longest(r, c, 1, 0, false);
    }
  }
}

void mark(vector<vector<int>> &v, int r, int c, int dr, int dc,
	  const vector<vector<int>> &len, bool odd)
{
  int L = len[r][c];
  int r1 = r, c1 = c;
  if (odd) {
    v[r1][c1] = max(v[r1][c1], len[r][c]);
    r1 -= dr;
    c1 -= dc;
    L--;
  }

  int r2 = r + dr, c2 = c + dc;
  while (L > 0) {
    assert(inside(r1, c1) && inside(r2, c2));
    v[r1][c1] = max(v[r1][c1], len[r][c]);
    v[r2][c2] = max(v[r2][c2], len[r][c]);
    L -= 2;
    r1 -= dr;
    c1 -= dc;
    r2 += dr;
    c2 += dc;
  }
}

void find_max()
{
  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      mark(max_vert, r, c, 0, 1, vert_odd, true);
      mark(max_vert, r, c, 0, 1, vert_even, false);
      mark(max_horiz, r, c, 1, 0, horiz_odd, true);
      mark(max_horiz, r, c, 1, 0, horiz_even, false);
    }
  }

  int best = 0;
  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      best = max(best, max_vert[r][c] * max_horiz[r][c]);
    }
  }

  cout << best << endl;
}

int main()
{
  cin >> R >> C;
  grid.resize(R);
  for (auto &s : grid) {
    cin >> s;
  }

  vert_odd.resize(R);
  vert_even.resize(R);
  horiz_odd.resize(R);
  horiz_even.resize(R);
  max_vert.resize(R);
  max_horiz.resize(R);
  for (int i = 0; i < R; i++) {
    vert_odd[i].resize(C, 0);
    vert_even[i].resize(C, 0);
    horiz_odd[i].resize(C, 0);
    horiz_even[i].resize(C, 0);
    max_vert[i].resize(C, 0);
    max_horiz[i].resize(C, 0);
  }

  preprocess();
  find_max();
  
  return 0;
}
