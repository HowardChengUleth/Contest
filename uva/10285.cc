#include <iostream>
#include <string>

using namespace std;

int best[102][102];
int grid[102][102];

int find_len(int r, int c)
{
  int dr[4] = { -1, 0, 1, 0 };
  int dc[4] = { 0, -1, 0, 1 };

  if (best[r][c] >= 0) {
    return best[r][c];
  }
  
  best[r][c] = 1;
  for (int i = 0; i < 4; i++) {
    int nr = r + dr[i], nc = c + dc[i];
    if (grid[r][c] > grid[nr][nc]) {
      int t = find_len(nr, nc);
      if (best[r][c] < t+1) {
	best[r][c] = t+1;
      }
    }
  }
  
  return best[r][c];
}

void solve_case(void)
{
  string name;
  int R, C;

  cin >> name >> R >> C;
  
  for (int r = 0; r <= R+1; r++) {
    grid[r][0] = grid[r][C+1] = 101;
  }
  for (int c = 0; c <= C+1; c++) {
    grid[0][c] = grid[R+1][c] = 101;
  }
  for (int r = 1; r <= R; r++) {
    for (int c = 1; c <= C; c++) {
      cin >> grid[r][c];
      best[r][c] = -1;
    }
  }

  int longest = 0;
  for (int r = 1; r <= R; r++) {
    for (int c = 1; c <= C; c++) {
      int len = find_len(r, c);
      if (len > longest) {
	longest = len;
      }
    }
  }
  cout << name << ": " << longest << endl;
}

int main(void)
{
  int N;
  cin >> N;
  while (N-- > 0) {
    solve_case();
  }
  return 0;
}
