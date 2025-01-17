#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;

  bool even = false, odd = false;
  for (int s = 1; s <= 100-N+1; s++) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
      sum += s+i;
    }
    if (sum % 2 == 0) {
      even = true;
    } else {
      odd = true;
    }
  }

  if (even && odd) {
    cout << "Either" << endl;
  } else if (even) {
    cout << "Even" << endl;
  } else {
    cout << "Odd" << endl;
  }

  return 0;
}

/*
  can also do it analytically

  if (N % 4 == 0) {
    cout << "Even" << endl;
  } else if (N % 2 == 0) {
    cout << "Odd" << endl;
  } else {
    cout << "Either" << endl;
  }

  sum(i, i = s..s+N-1) = N * (N + 2*s - 1) / 2

  If N is a multiple of 4, it is always even
  If N is a multiple of 2 but not 4, it is always odd
  Otherwise, N = 2*k+1 for some k, and this simplifies to
    (2k+1)*(k+s).  Whether this is even or odd depends on s.
    
*/
