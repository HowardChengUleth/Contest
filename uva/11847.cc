#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
  int n;
  while (cin >> n && n) {
    cout << (int)(floor(log2(n))+0.5) << endl;
  }
  return 0;
}
