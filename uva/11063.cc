#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
  int N;
  int cases = 1;

  while (cin >> N) {
    int B[100];
    int sums[10000];
    bool bad = false;

    for (int i = 0; i < N; i++) {
      cin >> B[i];
      if (B[i] < 1) bad = true;
      if (i > 0 && B[i] <= B[i-1]) bad = true;
    }
    
    int k = 0;
    for (int i = 0; i < N; i++) {
      for (int j = i; j < N; j++) {
	sums[k++] = B[i] + B[j];
      }
    }
    sort(sums, sums+k);

    int i;
    for (i = 0; i < k-1; i++) {
      if (sums[i] == sums[i+1]) {
	bad = true;
      }
    }

    cout << "Case #" << cases++ << ": ";
    cout << "It is" << (bad ? " not" : "") << " a B2-Sequence." << endl;
    cout << endl;
  }
  return 0;
}
