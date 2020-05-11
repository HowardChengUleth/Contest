//
// Want the largest d such that m/n >= 1/d, that means we want
//
//    d >= ceil(n/m)
//
// and we can start searching upwards until we find one such that the
// denominator of n/m - 1/d is < 1,000,000.  

#include <iostream>

using namespace std;

typedef unsigned long long ull;

ull gcd(ull a, ull b)
{
  while (b) {
    ull r = a % b;
    a = b;
    b = r;
  }
  return a;
}
  
bool solve()
{
  ull m, n;
  cin >> m >> n;
  if (!m && !n) return false;

  bool printed = false;
  do {
    ull d = (n + (m-1)) / m;

    bool done = false;
    while (!done) {
      ull newm = m*d - n, newn = n*d;
      ull r = gcd(newm, newn);
      newm /= r;
      newn /= r;
      if (newn < 1000000) {
	done = true;
	if (printed) {
	  cout << ' ';
	}
	cout << d;
	printed = true;
	m = newm;
	n = newn;
      }
      d++;
    }
  } while (m != 1);
  if (printed) {
    cout << ' ';
  }
  cout << n << endl;

  return true;
}
  
int main(void)
{
  while (solve())
    ;
  return 0;
}
