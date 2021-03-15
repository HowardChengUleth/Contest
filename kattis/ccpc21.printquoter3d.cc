#include <bits/stdc++.h>

using namespace std;

int W, H, D;
int A[100][100][100];

char Gfront[100][100], Gright[100][100], Gtop[100][100];

void read(char G[100][100], int R, int C)
{
  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      cin >> G[r][c];
    }
  }
}

void carve(char G[100][100], int R, int C, int dx, int dy, int dz)
{
  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      if (G[r][c] == '#') continue;

      int x, y, z;
      if (dx) {
	x = 0;
	y = r;
	z = c;
      } else if (dy) {
	x = c;
	y = 0;
	z = R-1-r;
      } else {
	x = c;
	y = r;
	z = 0;
      }

      while (0 <= x && x < W && 0 <= y && y < H && 0 <= z && z < D) {
	A[x][y][z] = 0;
	
	x += dx;
	y += dy;
	z += dz;
      }
    }
  }
  /*
    for (int y = 0; y < H; y++) {
    for (int z = 0; z < D; z++) {
      for (int x = 0; x < W; x++) {
	cout << A[x][y][z];
      }
      cout << endl;
    }
    cout << endl;
  }
  */
}

bool check(char G[100][100], int R, int C, int dx, int dy, int dz)
{
  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      if (G[r][c] == '.') continue;

      int x, y, z;
      if (dx) {
	x = 0;
	y = r;
	z = c;
      } else if (dy) {
	x = c;
	y = 0;
	z = R-1-r;
      } else {
	x = c;
	y = r;
	z = 0;
      }

      bool found = false;
      while (0 <= x && x < W && 0 <= y && y < H && 0 <= z && z < D) {
	found |= A[x][y][z];
	
	x += dx;
	y += dy;
	z += dz;
      }
      if (!found) return false;
    }
  }
  return true;
}

int main()
{
  cin >> W >> H >> D;
  for (int x = 0; x < W; x++) {
    for (int y = 0; y < H; y++) {
      for (int z = 0; z < D; z++) {
	A[x][y][z] = 1;
      }
    }
  }

  read(Gfront, H, W);
  read(Gright, H, D);
  read(Gtop, D, W);

  carve(Gfront, H, W, 0, 0, 1);
  carve(Gright, H, D, 1, 0, 0);
  carve(Gtop, D, W, 0, 1, 0);
  bool valid = check(Gfront, H, W, 0, 0, 1) &&
    check(Gright, H, D, 1, 0, 0) &&
    check(Gtop, D, W, 0, 1, 0);

  
  if (!valid) {
    cout << "invalid" << endl;
  } else {
    int ans = 0;
    for (int x = 0; x < W; x++) {
      for (int y = 0; y < H; y++) {
	for (int z = 0; z < D; z++) {
	  ans += A[x][y][z];
	}
      }
    }
    cout << ans << endl;
  }
  
  return 0;
}
