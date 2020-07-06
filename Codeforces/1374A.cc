#include <bits/stdc++.h>

using namespace std;

//
// k mod x = y means that there exists q such that k = q*x+y.
// From k = q*x + y <= n you get q <= (n-y)/x.
//

void solve()
{
  int x, y, n;
  cin >> x >> y >> n;

  int q = (n-y)/x;
  int k = q*x + y;
  cout << k << endl;

}

int main()
{
  int t;
  cin >> t;
  while (t--)
    solve();
  
  return 0;
}
