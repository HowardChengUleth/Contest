#include <bits/stdc++.h>

using namespace std;

int main()
{
  int L, R;
  cin >> L >> R;

  if (L+R == 0) {
    cout << "Not a moose" << endl;
  } else if (L == R) {
    cout << "Even " << L+R << endl;
  } else {
    cout << "Odd " << 2*max(L, R) << endl;
  }

  return 0;
}
