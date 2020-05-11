#include <iostream>
#include <algorithm>

using namespace std;

void solve()
{
  pair<int,int> A[2000];
  int N;
  int k = 0;

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> A[k].first;
    A[k++].second = 1;
  }
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> A[k].first;
    A[k++].second = 2;
  }
  sort(A, A+k);

  int best = -1;
  for (int i = 0; i < k-1; i++) {
    if (A[i].second == A[i+1].second) continue;
    if (best == -1 || A[i+1].first - A[i].first < best) {
      best = A[i+1].first - A[i].first;
    }
  }
  cout << best << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
