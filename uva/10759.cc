#include <iostream>

using namespace std;

typedef unsigned long long ull;

ull ways[25][150];

ull gcd(ull a, ull b)
{
  while (b) {
    ull r = a % b;
    a = b;
    b = r;
  }
  return a;
}

int main(void)
{
  for (int s = 1; s <= 6; s++) {
    ways[1][s] = 1;
  }
  for (int n = 1; n < 24; n++) {
    for (int s = 0; s <= 144; s++) {
      if (ways[n][s] > 0) {
	for (int r = 1; r <= 6; r++) {
	  ways[n+1][s+r] += ways[n][s];
	}
      }
    }
  }

  int n, x;
  while (cin >> n >> x && (n || x)) {
    ull denom = 1;
    for (int i = 0; i < n; i++) {
      denom *= 6;
    }
    ull numer = 0;
    for (int i = x; i <= 144; i++) {
      numer += ways[n][i];
    }
    ull g = gcd(numer, denom);
    numer /= g;
    denom /= g;
    if (denom == 1) {
      cout << numer << endl;
    } else {
      cout << numer << '/' << denom << endl;
    }
  }
  return 0;
}
