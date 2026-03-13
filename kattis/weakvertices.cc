#include <bits/stdc++.h>

using namespace std;

bool solve()
{
  int n;
  cin >> n;
  if (n == -1) {
    return false;
  }

  int A[20][20] = {0};
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> A[i][j];
    }
  }

  bool good[20] = { false };

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
	if (A[i][j] && A[j][k] && A[i][k]) {
	  good[i] = good[j] = good[k] = true;
	}
      }
    }
  }

  for (int i = 0; i < n; i++) {
    if (!good[i]) {
      cout << i << ' ';
    }
  }
  cout << endl;

  return true;
}


int main()
{
  while (solve())
    ;

  return 0;
}
