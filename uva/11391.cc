#include <iostream>
#include <algorithm>

using namespace std;

struct State
{
  bool grid[4][4];
  int R, C;
  int blobs;
  
  int toint() const
  {
    int x = 0;

    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
	x <<= 1;
	if (grid[i][j]) x++;
      }
    }
    return (x << 4) + (R << 2) + C;
  }

  State()
    : R(0), C(0), blobs(0)
  {
  }
  
  State(const State &s)
    : R(s.R), C(s.C), blobs(s.blobs)
  {
    for (int i = 0; i < s.R; i++) {
      copy(s.grid[i], s.grid[i]+s.C, grid[i]);
    }
  }

  bool done() const
  {
    return blobs == 1;
  }
};

istream &operator>>(istream &is, State &s)
{
  int N;
  is >> s.R >> s.C >> N;
  for (int i = 0; i < s.R; i++) {
    fill(s.grid[i], s.grid[i]+s.C, false);
  }
  s.blobs = N;
  while (N--) {
    int x, y;
    is >> x >> y;
    x--; y--;
    s.grid[x][y] = true;
  }
  return is;
};

int ways[16*65536];

int compute(const State &s)
{
  int idx = s.toint();
  if (ways[idx] != -1) return ways[idx];
  if (s.done()) {
    return ways[idx] = 1;
  }

  ways[idx] = 0;
  for (int i = 0; i < s.R; i++) {
    for (int j = 0; j < s.C; j++) {
      if (!s.grid[i][j]) continue;

      for (int di = -1; di <= 1; di++) {
	for (int dj = -1; dj <= 1; dj++) {
	  if (di == 0 && dj == 0) continue;
	  if (!(0 <= i+2*di && i+2*di < s.R &&
		0 <= j+2*dj && j+2*dj < s.C)) continue;
	  if (!(s.grid[i+di][j+dj] && !s.grid[i+2*di][j+2*dj])) continue;

	  State next = s;
	  next.grid[i][j] = next.grid[i+di][j+dj] = false;
	  next.grid[i+2*di][j+2*dj] = true;
	  next.blobs--;
	  ways[idx] += compute(next);
	}
      }
    }
  }
  return ways[idx];
}

void solve()
{
  State start;
  cin >> start;
  cout << compute(start) << endl;
}

int main(void)
{
  fill(ways, ways+16*65536, -1);
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": ";
    solve();
  }
  return 0;
}
