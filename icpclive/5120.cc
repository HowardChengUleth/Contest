#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;

void solve(int n)
{
  int ba, bb, bc;
  ba = bb = bc = -1;
  
  for (ll a = 1; a <= 4000; a++) {
    for (ll b = 1; a+2*b <= 4000; b++) {
      ll a3 = a*a*a;
      ll t = n*b*b*b - a3;

      if (a3 < t) continue;
      if (t <= 0) continue;
      ll c = floor(pow((long double)t, (long double)1.0/3.0)+0.5);
      bool found = (c*c*c == t);
      if (!found) continue;
      int bt = ba + bc + 2*bb;
      ll tt = a + c + 2*b;
      if (bt < 0 || tt < bt) {
	ba = a;
	bb = b;
	bc = c;
      }
    }
  }

  if (ba < 0) {
    cout << "No value." << endl;
  } else {
    cout << "(" << ba << "/" << bb << ")^3 + (" << bc << "/" << bb << ")^3 = "
	 << n << endl;
  }
}

int main()
{
  int n;
  while (cin >> n && n) {
    solve(n);
  }
  return 0;
}
