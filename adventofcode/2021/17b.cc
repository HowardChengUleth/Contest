#include <bits/stdc++.h>

using namespace std;

int X1, X2, Y1, Y2;

int main()
{
  cin >> X1 >> X2 >> Y1 >> Y2;

  int ans = 0;
  for (int vx = 1; vx <= X2; vx++) {
    for (int vy = -10000; vy <= 10000; vy++) {
      int x = 0, y = 0;;
      int dx = vx, dy = vy;
      int h = 0;
      while (x <= X2 && y >= Y1) {
	x += dx;
	if (dx) {
	  dx--;
	}
	y += dy;
	dy--;
	h = max(h, y);
	if (X1 <= x && x <= X2 && Y1 <= y && y <= Y2) {
	  ans++;
	  break;
	}
      }
    }
  }

  cout << ans << endl;
  
  return 0;
}
