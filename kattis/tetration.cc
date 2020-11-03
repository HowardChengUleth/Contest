#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
  double N;

  // a^N = N

  cin >> N;
  double a = pow(N, 1.0/N);
  cout << fixed << setprecision(10) << a << endl;
  return 0;
}

