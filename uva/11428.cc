#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
  int xans[10001] = {0};
  int yans[10001] = {0};
  for (int N = 1; N <= 10000; N++) {
    for (int y = 1; y*y <= N; y++) {
      int x = floor(pow(N + y*y*y, 1.0/3.0)+0.5)-1;
      if (x*x*x - y*y*y == N) {
	xans[N] = x;
	yans[N] = y;
      }
      x++;
      if (x*x*x - y*y*y == N) {
	xans[N] = x;
	yans[N] = y;
      }
      x++;
      if (x*x*x - y*y*y == N) {
	xans[N] = x;
	yans[N] = y;
      }
      if (xans[N]) break;
    }
  }

  int N;
  while (cin >> N && N) {
    if (xans[N]) {
      cout << xans[N] << ' ' << yans[N] << endl;
    } else {
      cout << "No solution" << endl;
    }
  }
  return 0;
}
