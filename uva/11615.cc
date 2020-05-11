#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
  int T;
  cin >> T;
  while (T--) {
    int n, a, b;
    cin >> n >> a >> b;

    int num = (1 << n)-1;

    a = max(a, b);
    int gen = 0;
    while (a > 0) {
      gen++;
      a >>= 1;
    }

    int remove = (1 << (n - (gen-1))) - 2;
    cout << num - remove << endl;
  }
  return 0;
}
