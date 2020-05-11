#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

int main(void)
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": ";
    int A[3];
    cin >> A[0] >> A[1] >> A[2];
    sort(A, A+3);
    cout << A[1] << endl;
  }
  return 0;
}
