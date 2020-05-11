#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
  int h1, m1, h2, m2;

  while (cin >> h1 >> m1 >> h2 >> m2 && (h1 || h2 || m1 || m2)) {
    int diff = (h2-h1)*60 + m2-m1;
    if (diff < 0) diff += 24*60;

    cout << diff << endl;

  }


  return 0;
}
