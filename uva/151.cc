/* @JUDGE_ID: 1102NT 151 C++ "" */

#include <iostream>

using namespace std;

const int AUCKLAND = 12;

int good(int n, int m)
{
  int off[100];
  
  for (int i = 0; i < n; i++) {
    off[i] = 0;
  }

  int i = 0;
  off[i] = 1;
  for (int k = 0; k < n-2; k++) {
    for (int j = 0; j < m; ) {
      if (++i >= n) {
	i = 0;
      }
      if (!off[i]) {
	j++;
      }
    }
    off[i] = 1;
    if (i == AUCKLAND) {
      return 0;
    }
  }
  return 1;
}

int main(void)
{
  int n;

  while (cin >> n && n > 0) {
    int m = 1;
    while (1) {
      if (good(n, m)) {
	cout << m << endl;
	break;
      }
      m++;
    }
  }
  return 0;
}
