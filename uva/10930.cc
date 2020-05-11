#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
  int d;
  int id = 1;
  while (cin >> d) {
    cout << "Case #" << id++ << ":";

    int A[30];
    bool good = true;
    for (int i = 0; i < d; i++) {
      cin >> A[i];
      cout << ' ' << A[i];
      good &= (A[i] >= 1);
    }
    cout << endl;

    bool sum[1001] = { false };
    sum[0] = sum[A[0]] = true;

    for (int i = 1; i < d && good; i++) {
      good &= (A[i] > A[i-1]);
      if (sum[A[i]]) good = false;
      bool sum2[1001] = { false };
      for (int j = 0; j <= 1000 - A[i]; j++) {
	if (sum[j]) sum2[j + A[i]] = true;
      }
      for (int j = 0; j <= 1000; j++) {
	sum[j] |= sum2[j];
      }
    }

    if (good) {
      cout << "This is an A-sequence." << endl;
    } else {
      cout << "This is not an A-sequence." << endl;
    }
  }
  return 0;
}
