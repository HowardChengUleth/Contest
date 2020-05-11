#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
  long long A[3];

  while (cin >> A[0] >> A[1] >> A[2] && (A[0] || A[1] || A[2])) {
    sort(A, A+3);
    if (A[0]*A[0] + A[1]*A[1] == A[2]*A[2]) {
      cout << "right" << endl;
    } else {
      cout << "wrong" << endl;
    }
  }

  return 0;
}
