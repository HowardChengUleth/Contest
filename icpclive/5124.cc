#include <iostream>
#include <cmath>

using namespace std;

double r(int a, int m, int &s)
{
  double val = (s % m) / (double)m;
  s = (a * s + 1) % m;
  return val;
}

int main()
{
  int a, m, s;
  cin >> a >> m >> s;
  cin.ignore(1);
  char c;
  while (cin.get(c)) {
    if (0x20 <= c && c <= 0x7e) {
      c = c - 32;
      c -= (int)ceil(95 - r(a, m, s)*95);
      while (c < 0) {
	c += 95;
      }
      c %= 95;
      c = c + 32;
      cout << c;

    } else {
      cout << c;
    }
  }
  
  return 0;
}
