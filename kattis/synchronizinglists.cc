#include <bits/stdc++.h>

using namespace std;

bool solve(bool first)
{
  int n;
  cin >> n;
  if (n == 0) {
    return false;
  }

  if (first) {
    cout << endl;
  }

  vector<int> A(n), B(n);
  for (auto &x : A) {
    cin >> x;
  }
  for (auto &x : B) {
    cin >> x;
  }

  vector<int> A2 = A, B2 = B;
  sort(begin(A2), end(A2));
  sort(begin(B2), end(B2));

  map<int,int> M;
  for (int i = 0; i < n; i++) {
    M[A2[i]] = B2[i];
  }

  for (int i = 0; i < n; i++) {
    cout << M[A[i]] << endl;
  }

  return true;
}

int main()
{
  bool first = true;
  while (solve(first)) {
    first = false;
  }
  return 0;
}
