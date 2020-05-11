/* @JUDGE_ID: 1102NT 10408 C++ "" */

// see Knuth v. 1 1.3.2 exercises 18 and 19.

#include <iostream>
using namespace std;

int main(void)
{
  int n, k;

  while (cin >> n >> k) {
    int x, y, x1, y1, x2, y2;

    x = 1;  y = n;
    x1 = 0; y1 = 1;

    for (int i = 2; i <= k; i++) {
      x2 = x1; y2 = y1;
      x1 = x;  y1 = y;
      x = ((y2 + n)/y1)*x1 - x2;
      y = ((y2 + n)/y1)*y1 - y2;
    }

    cout << x << "/" << y << endl;
  }


  return 0;
}
