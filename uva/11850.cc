#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
  int A[10000];
  int n;

  while (cin >> n && n > 0) {
    for (int i = 0; i < n; i++) {
      cin >> A[i];
    }
    sort(A, A+n);

    // insert a fake one at the end
    A[n] = 1422 + (1422 - A[n-1]);

    bool possible = true;
    for (int i = 0; i < n; i++) {
      if (A[i+1] - A[i] > 200) {
	possible = false;
      }
    }

    if (possible) {
      cout << "POSSIBLE" << endl;
    } else {
      cout << "IMPOSSIBLE" << endl;
    }
  }
  return 0;
}
