#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
  int n;
  cin >> n;
  while (n-- > 0) {
    int sides[4];
    cin >> sides[0] >> sides[1] >> sides[2] >> sides[3];
    sort(sides, sides+4);
    if (sides[0] == sides[3]) {
      cout << "square" << endl;
    } else if (sides[0] == sides[1] && sides[2] == sides[3]) {
      cout << "rectangle" << endl;
    } else if (sides[0] + sides[1] + sides[2] > sides[3]) {
      cout << "quadrangle" << endl;
    } else {
      cout << "banana" << endl;
    }

  }

  return 0;
}
