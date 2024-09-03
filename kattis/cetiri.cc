#include <bits/stdc++.h>

using namespace std;

int main()
{
  int A[3];
  for (int i = 0; i < 3; i++) {
    cin >> A[i];
  }
  
  sort(A, A+3);

  int D[3];
  adjacent_difference(A, A+3, D);

  if (D[1] == D[2]) {
    // they are the same, so we just produce the one after
    cout << A[2] + D[1] << endl;
  } else if (D[1] < D[2]) {
    // missing 3rd number
    assert(D[2] == D[1]*2);
    cout << A[1] + D[1] << endl;
  } else {
    // missing first number
    assert(D[1] == D[2]*2);
    cout << A[0] + D[2] << endl;
  }

  return 0;
}
