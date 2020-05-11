// There are faster/slicker way to do this, but this is a "straightforward"
// approach

#include <iostream>

using namespace std;

int main(void)
{
  int n;
  while (cin >> n && n) {
    int a = 0, b = 0;
    int index[32];
    int num = 0;

    int pos = 0;
    while (n) {
      if (n % 2 == 1) {
	index[num++] = pos;           // remember the indices of 1s
      }
      pos++;
      n >>= 1;                        // same as n /= 2
    }
    for (int i = 0; i < num; i++) {
      if (i % 2 == 0) {
	a |= 1 << index[i];           // same as a += 2^(index[i])
      } else {
	b |= 1 << index[i];
      }
    }
    cout << a << ' ' << b << endl;
    
  }
  return 0;
}
