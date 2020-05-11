#include <iostream>
#include <algorithm>


using namespace std;

int main(void)
{
  long long x, y;

  while (cin >> x >> y) {
    if (x < 0) x = -x;
    if (y < 0) y = -y;
    long long x1 = max(x, y);
    long long x2 = min(x, y);

    long long ans;
    if (x1 == 1 && x2 == 0) {
      ans = 3;
    } else if (x1 == 2 && x2 == 2) {
      ans = 4;
    } else {
      long long temp = max((x1+1)/2, (x1+x2+2)/3);
      ans = temp + (x1 + x2 - temp) % 2;
    }
    cout << ans << endl;
  }
  return 0;
}
