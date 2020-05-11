#include <iostream>
#include <algorithm>

using namespace std;

pair<int, int> A[100000];
int start[1000001];
int main(void)
{
  int n, m;
  while (cin >> n >> m) {
    for (int i = 0; i < n; i++) {
      cin >> A[i].first;
      A[i].second = i+1;
    }

    sort(A, A+n);
    fill(start, start+1000001, -1);
    for (int i = 0; i < n; i++) {
      if (i == 0 || A[i].first != A[i-1].first) {
	start[A[i].first] = i;
      }
    }

    while (m--) {
      int k, v;
      cin >> k >> v;
      if (start[v] < 0) {
	cout << 0 << endl;
	continue;
      }

      int t = start[v] + k - 1;
      if (t >= n || A[t].first != v) {
	cout << 0 << endl;
      } else {
	cout << A[t].second << endl;
      }
    }
  }

  return 0;
}
