// Just do it?
//
// Of course you have to be careful with everything.  Using stoi will
// make things a lot easier.  Also, no need to worry about keeping things
// as integers, since we are dealing with a floating point output

#include <bits/stdc++.h>

using namespace std;

void solve()
{
  int E, M;
  string B;
  cin >> E >> M >> B;

  int sign = (B[0] == '1') ? -1 : 1;
  string ex = B.substr(1, E);
  string man = B.substr(1+E);

  double exval = pow(2.0, stoi(ex, nullptr, 2) - ((1 << (E-1)) - 1));
  double manval = 1.0 + stoi(man, nullptr, 2) * pow(2.0, -M);

  double val = sign * exval * manval;

  cout << fixed << setprecision(10) << val << endl;
}

int main()
{
  int n;
  cin >> n;

  while (n--) {
    solve();
  }

  return 0;
}
