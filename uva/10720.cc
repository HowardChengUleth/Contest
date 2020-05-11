#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

int main(void)
{
  int N;
  while (cin >> N && N) {
    int deg[10001];
    for (int i = 1; i <= N; i++) {
      cin >> deg[i];
    }
    sort(deg+1, deg+N+1, greater<int>());

    int degsum = 0;
    bool good = true;
    for (int k = 1; k <= N && good; k++) {
      degsum += deg[k];
      good &= deg[k] >= 0;

      int rhs = k*(k-1);
      for (int i = k+1; i <= N; i++) {
	rhs += min(deg[i], k);
      }
      good &= (degsum <= rhs);
    }

    if (degsum % 2 != 0) {
      good = false;
    }

    if (good) {
      cout << "Possible" << endl;
    } else {
      cout << "Not possible" << endl;
    }
    
  }

  return 0;
}
