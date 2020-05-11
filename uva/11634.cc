#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
  int a;
  while (cin >> a && a > 0) {
    int used[10000];
    fill(used, used+10000, false);

    int count = 0;
    while (!used[a]) {
      count++;
      used[a] = true;
      a = ((a*a)/100) % 10000;
    }
    cout << count << endl;
  }
  return 0;
}
