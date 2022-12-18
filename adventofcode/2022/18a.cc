#include <bits/stdc++.h>

using namespace std;

int main()
{
  // max input coord is 21
  char comma;
  int X, Y, Z;

  bool A[22][22][22] = {false};

  
  while (cin >> X >> comma >> Y >> comma >> Z) {
    A[X][Y][Z] = true;
  }

  int ans = 0;
  for (int x = 0; x <= 21; x++) {
    for (int y = 0; y <= 21; y++) {
      for (int z = 0; z <= 21; z++) {
	if (!A[x][y][z]) continue;
	int dx[] = {-1, 1, 0, 0, 0, 0};
	int dy[] = {0, 0, 1, -1, 0, 0};
	int dz[] = {0, 0, 0, 0, 1, -1};
	int face = 6;
	for (int d = 0; d < 6; d++) {
	  int x2 = x + dx[d], y2 = y + dy[d], z2 = z + dz[d];
	  if (0 <= x2 && x2 < 22 && 0 <= y2 && y2 < 22 &&
	      0 <= z2 && z2 < 22 && A[x2][y2][z2]) {
	    face--;
	  }
	}
	ans += face;
      }
    }
  }

  cout << ans << endl;

  return 0;
}
