#include <bits/stdc++.h>

using namespace std;

int main()
{
  int S, P;
  cin >> S >> P;

  // measure middle of day.  Let Q = (100-P)/100
  //
  // day 1: S
  // day 2: S * Q + S = S * (1+Q)
  // day 3: S * (1+Q) * Q + S = S * (1 + Q + Q^2)
  // ...
  // day n+1: S * (1 + Q + Q^2 + ... + Q^n) = S * (Q^(n+1) - 1) / (Q-1)
  //
  // or S/(1-Q) * (1- Q^(n+1)) -> S/(1-Q) as n goes to infinity.
  //

  double Q = (100.0 - P) / 100.0;
  cout << fixed << setprecision(10) << S/(1 - Q) << endl;
  return 0;
}
