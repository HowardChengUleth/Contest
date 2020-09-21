#include <bits/stdc++.h>

using namespace std;

int main()
{
  int A[3];
  for (int i = 0; i < 3; i++) {
    cin >> A[i];
  }
  sort(A, A+3);

  for (int i = 0; i < 3; i++) {
    char c;
    cin >> c;
    cout << A[c - 'A'] << ' ';
  }
  cout << endl;

  return 0;
}
