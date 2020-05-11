#include <iostream>

using namespace std;

void solve()
{
  int a, c;
  cin >> a >> c;
  if (c % a != 0) {
    cout << "NO SOLUTION" << endl;
    return;
  }

  int b = 1;

  for (int p = 2; p*p <= c; p++) {
    int count = 0, count2 = 0;
    while (c % p == 0) {
      c /= p;
      count++;
    }
    while (a % p == 0) {
      a /= p;
      count2++;
    }
    if (count > count2) {
      while (count--) {
	b *= p;
      }
    }
  }
  if (c > 1) {
    if (a % c != 0) {
      b *= c;
    }
  }
  cout << b << endl;
}

int main(void)
{
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
