#include <bits/stdc++.h>

using namespace std;

int mypow(int b, int n)
{
  int ans = 1;
  for (int i = 0; i < n; i++) {
    ans *= b;
  }
  return ans;
}

int main()
{
  int N;
  int ans = 0;

  cin >> N;
  for (int i = 0; i < N; i++) {
    int P;
    cin >> P;
    ans += mypow(P/10, P%10);
  }
  cout << ans << endl;

  return 0;
}
