#include <iostream>

using namespace std;

// idea: for each K being the longest side, figure out how many ways we
//       can form the triangle (by varying the 2nd longest side).  Each
//       varying of a side leads to a sum and we can solve for the closed
//       form formula.

int main(void)
{
  long long n;
  while (cin >> n && n >= 3) {
    long long f = n/2;
    long long c = (n+1)/2;
    long long ans = (-3*n*n + 3*n + 2*f*f*f + 3*f*f + f + 2*c*c*c - 2*c)/6;
    cout << ans << endl;

  }

  return 0;
}
