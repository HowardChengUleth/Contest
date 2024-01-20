#include <bits/stdc++.h>

using namespace std;


int main()
{
  int N;
  cin >> N;

  int A[100000];
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  sort(A, A+N);
  
  int Q;
  cin >> Q;
  for (int i = 0; i < Q; i++) {
    int l, r;
    cin >> l >> r;
    auto lb = lower_bound(A, A+N, l);
    auto ub = upper_bound(A, A+N, r);
    cout << ub - lb << endl;
  }

  return 0;
}
