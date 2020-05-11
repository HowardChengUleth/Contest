// Pretty much any kind of evaluation works here.  You should make
// sure that a 32-bit int variable is large enough to hold the result
// of the polynomial (which is okay in this case).  Otherwise you can
// reduce intermediate results mod d as much as we can
//
// The solution below actually computes the values of the polynomial
// at consecutive integers a little faster than the usual approach,
// but it is not really that important here.
#include <iostream>

using namespace std;

int main(void)
{
  int a, b, c, d, L;

  while (cin >> a >> b >> c >> d >> L &&
	 (a || b || c || d || L)) {
    int fval = c;
    int count = (fval % d) ? 0 : 1;
    for (int n = 1; n <= L; n++) {
      fval += (a*(2*n-1) + b) % d;
      fval %= d;
      if (fval == 0) {
	count++;
      }
    }
    cout << count << endl;

  }

  return 0;
}
