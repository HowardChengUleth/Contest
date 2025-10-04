#include <bits/stdc++.h>

using namespace std;

int main()
{
  vector<int> A(5);
  for (auto &x : A) {
    cin >> x;
  }

  while (!is_sorted(begin(A), end(A))) {
    for (int i = 0; i < 4; i++) {
      if (A[i] > A[i+1]) {
	swap(A[i], A[i+1]);
	for (auto x : A) {
	  cout << x << ' ';
	}
	cout << endl;
      }
    }
  }

  return 0;
}
