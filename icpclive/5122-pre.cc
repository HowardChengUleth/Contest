#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

typedef long long ll;

ll fib[101];
int maxn = 0;

void factor(ll n)
{
  if (n <= 1) {
    cout << "\"No prime factors\"";
    return;
  }
  cout << "\"Prime factors:";

  while ((n & 1) == 0) {
    n >>= 1;
    cout << " 2";
  }

  for (ll p = 3; p <= ceil(sqrt(n)); p += 2) {
    while (n % p == 0) {
      n /= p;
      cout << ' ' << p;
    }
  }
  if (n > 1) {
    cout << ' ' << n;
  }
  
  cout << "\"";
}

int main(void)
{
  fib[0] = 0;
  fib[1] = 1;
  maxn = 1;
  for (int k = 2; true; k++) {
    fib[k] = fib[k-1] + fib[k-2];
    if (fib[k] < fib[k-1]) break;
    maxn = k;
  }

  cout << "typedef long long ll;" << endl;
  cout << "ll fib[" << maxn+1 << "] = {" << fib[0];
  for (int n = 1; n <= maxn; n++) {
    cout << ',' << fib[n] << "LL";
  }
  cout << "};" << endl;

  cout << "string lg[" << maxn+1 << "] = {";
  cout << "\"lg does not exist\"";
  for (int n = 1; n <= maxn; n++) {
    cout << ", \"lg is " << fixed << setprecision(6) << log(fib[n])/log(2.0)
	 << "\"";
  }
  cout << "};" << endl;

  cout << "string factors[" << maxn+1 << "] = {";
  for (int n = 0; n <= maxn; n++) {
    if (n) cout << ',';
    factor(fib[n]);
  }
  cout << "};" << endl;
  return 0;
}
