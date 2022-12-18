#include <bits/stdc++.h>

using namespace std;

const int dx[] = {-1, 1, 0, 0, 0, 0};
const int dy[] = {0, 0, 1, -1, 0, 0};
const int dz[] = {0, 0, 0, 0, 1, -1};

int A[24][24][24] = {0};

void flood(int x, int y, int z)
{
  A[x][y][z] = 2;

  for (int d = 0; d < 6; d++) {
    int x2 = x + dx[d], y2 = y + dy[d], z2 = z + dz[d];
    if (0 <= x2 && x2 < 24 && 0 <= y2 && y2 < 24 &&
	0 <= z2 && z2 < 24 && !A[x2][y2][z2]) {
      flood(x2, y2, z2);
    }
  }
}

int main()
{
  // max input coord is 21
  char comma;
  int X, Y, Z;

  
  while (cin >> X >> comma >> Y >> comma >> Z) {
    A[X+1][Y+1][Z+1] = 1;
  }

  for (int x = 0; x <= 23; x++) {
    for (int y = 0; y <= 23; y++) {
      for (int z = 0; z <= 23; z++) {
	if (x == 0 || x == 23 || y == 0 || y == 23 || z == 0 || z == 23) {
	  if (!A[x][y][z]) {
	    flood(x, y, z);
	  }
	}
      }
    }
  }
  
  int ans = 0;
  for (int x = 0; x <= 23; x++) {
    for (int y = 0; y <= 23; y++) {
      for (int z = 0; z <= 23; z++) {
	if (A[x][y][z] != 1) continue;
	for (int d = 0; d < 6; d++) {
	  int x2 = x + dx[d], y2 = y + dy[d], z2 = z + dz[d];
	  if (0 <= x2 && x2 < 24 && 0 <= y2 && y2 < 24 &&
	      0 <= z2 && z2 < 24 && A[x2][y2][z2] == 2) {
	    ans++;
	  }
	}
      }
    }
  }

  cout << ans << endl;

  return 0;
}
