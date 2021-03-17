#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
  int n;
  ll A[100002], leftmax[100002], rightmin[100002];

  cin >> n;
  A[0] = LONG_LONG_MIN;
  A[n+1] = LONG_LONG_MAX;
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
  }
  leftmax[0] = A[0];
  for (int i = 1; i <= n+1; i++) {
    leftmax[i] = max(leftmax[i-1], A[i]);
  }
  rightmin[n+1] = A[n+1];
  for (int i = n; i >= 0; i--) {
    rightmin[i] = min(rightmin[i+1], A[i]);
  }

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += (A[i] >= leftmax[i-1] && A[i] < rightmin[i+1]);
  }

  cout << ans << endl;
  


  return 0;
}
