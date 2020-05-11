#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
  int n;

  while (cin >> n && n > 0) {
    pair<int,int> A[500000], B[500000];

    for (int i = 0; i < n; i++) {
      cin >> A[i].first >> A[i].second;
      B[i] = make_pair(A[i].second, A[i].first);
    }
    sort(A, A+n);
    sort(B, B+n);
    cout <<  (equal(A, A+n, B) ? "YES" : "NO") << endl;
  }
  return 0;
}
