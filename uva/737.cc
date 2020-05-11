#include <iostream>
#include <algorithm>

using namespace std;

void intersect(int &x, int &y, int &z, int &lenx, int &leny, int &lenz,
	       int x2, int y2, int z2, int len)
{
  int xl = max(x, x2), xh = min(x+lenx, x2+len);
  int yl = max(y, y2), yh = min(y+leny, y2+len);
  int zl = max(z, z2), zh = min(z+lenz, z2+len);

  x = xl;
  y = yl;
  z = zl;
  lenx = max(0, xh-xl);
  leny = max(0, yh-yl);
  lenz = max(0, zh-zl);
}

bool solve()
{
  int n;
  cin >> n;
  if (!n) return false;

  int x, y, z, lenx, leny, lenz;
  cin >> x >> y >> z >> lenx;
  leny = lenz = lenx;
  
  for (int i = 1; i < n; i++) {
    int x2, y2, z2, len;
    cin >> x2 >> y2 >> z2 >> len;
    intersect(x, y, z, lenx, leny, lenz, x2, y2, z2, len);
  }

  cout << lenx*leny*lenz << endl;
  
  return true;
}

int main(void)
{
  while (solve())
    ;

  return 0;
}
