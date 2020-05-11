#include <iostream>

using namespace std;

int sigma[1000];

int main(void)
{
  for (int i = 1; i <= 999; i++) {
    sigma[i] = 0;
    for (int j = 1; j <= i; j++) {
      if (i % j == 0) {
	sigma[i] += j;
      }
    }
  }

  int id = 1;
  int S;
  while (cin >> S && S) {
    int k = 999;
    cout << "Case " << id++ << ": ";
    while (k >= 1 && sigma[k] != S)
      k--;
    if (k < 1) {
      cout << -1;
    } else {
      cout << k;
    }
    cout << endl;
  }
  return 0;
}
