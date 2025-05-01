#include <bits/stdc++.h>

using namespace std;

void solve_case()
{
  int ID;
  const int N = 20;
  int A[N];

  cin >> ID;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }


  int ans = 0;
  for (int i = 1; i < N; i++) {
    sort(A, A+i);
    int pos = lower_bound(A, A+i, A[i]) - A;
    ans += i - pos;
  }

  /*
  int ans = 0;
  for (int i = 1; i < N; i++) {
    for (int j = i; j > 0 && A[j] < A[j-1]; j--) {
      swap(A[j], A[j-1]);
      ans++;
    }
  }
  */
  
  cout << ID << ' ' << ans << endl;
}

int main()
{
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    solve_case();
  }
  
  return 0;
}
