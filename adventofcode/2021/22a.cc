#include <bits/stdc++.h>

using namespace std;

bool inside(int c)
{
  return (-50 <= c && c <= 50);
}

bool outside(int x1, int x2, int y1, int y2, int z1, int z2)
{
  return !(inside(x1) && inside(x2) && inside(y1) && inside(y2)
	   && inside(z1) && inside(z2));
}

bool A[101][101][101];

int main()
{
  string cmd, line;
  while (cin >> cmd) {
    getline(cin, line);
    replace(begin(line), end(line), ',', ' ');
    replace(begin(line), end(line), '.', ' ');
    replace(begin(line), end(line), '=', ' ');

    istringstream iss(line);
    char ch;
    int x1, x2, y1, y2, z1, z2;
    iss >> ch >> x1 >> x2 >> ch >> y1 >> y2 >> ch >> z1 >> z2;

    if (outside(x1, x2, y1, y2, z1, z2))
      continue;

    for (int x = x1; x <= x2; x++) {
      for (int y = y1; y <= y2; y++) {
	for (int z = z1; z <= z2; z++) {
	  A[x+50][y+50][z+50] = (cmd == "on");
	}
      }
    }    
  }

  int ans = 0;
  for (int i = 0; i <= 100; i++) {
    for (int j = 0; j <= 100; j++) {
      for (int k = 0; k <= 100; k++) {
	ans += A[i][j][k];
      }
    }
  }

  cout << ans << endl;

  return 0;
}
