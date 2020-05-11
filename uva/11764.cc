#include <iostream>

using namespace std;

int main(void)
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": ";

    int N;
    cin >> N;

    int A[50];
    int hi = 0, lo = 0;
    for (int i = 0; i < N; i++) {
      cin >> A[i];
      if (i > 0) {
	if (A[i] > A[i-1]) {
	  hi++;
	} else if (A[i] < A[i-1]) {
	  lo++;
	}
      }
    }
    cout << hi << ' ' << lo << endl;
  }
  return 0;
}
    
