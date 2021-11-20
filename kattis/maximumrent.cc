#include <bits/stdc++.h>

using namespace std;

int a, b, m, s;

int f(int x, int y)
{
  return a*x + b*y;
}

int main()
{
  cin >> a >> b >> m >> s;

  int R = 0;

  int x = m-1, y = 1;
  if (2*x + y >= s) {
    R = max(R, f(x, y));
  }
  x = 1; y = m-1;
  if (2*x + y >= s) {
    R = max(R, f(x, y));
  }

  /*
    x + y = m 
    2x + y = s

    => x = s-m
  */
  x = s - m; y = m - x;
  if (x >= 1 && y >= 1 && 2*x+y >= s) {
    R = max(R, f(x,y));
  }

  cout << R << endl;
}
