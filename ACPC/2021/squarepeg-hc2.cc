#include <bits/stdc++.h>

using namespace std;

int main()
{
  int L, R;
  cin >> L >> R;

  if (sqrt(2*L*L) <= 2*R) {
    cout << "fits" << endl;
  } else {
    cout << "nope" << endl;
  }

  return 0;
}
