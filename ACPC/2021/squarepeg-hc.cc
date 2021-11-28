#include <bits/stdc++.h>

using namespace std;

int main()
{
  int L, R;
  cin >> L >> R;

  if (2*L*L <= 4*R*R) {
    cout << "fits" << endl;
  } else {
    cout << "nope" << endl;
  }

  return 0;
}
