#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": ";
    int N, A[10];
    cin >> N;
    for (int j = 0; j < N; j++) {
      cin >> A[j];
    }
    sort(A, A+N);
    cout << A[N/2] << endl;
  }
  return 0;
}
