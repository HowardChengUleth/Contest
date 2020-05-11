#include <iostream>

using namespace std;

int main()
{
  int n;
  while (cin >> n && n) {
    n++;
    bool pow2 = true;
    while (n > 0) {
      if (n > 1 && (n & 1)) pow2 = false;
      n >>= 1;
    }
    if (pow2) {
      cout << "Bob" << endl;
    } else {
      cout << "Alice" << endl;
    }
  }

  return 0;
}
