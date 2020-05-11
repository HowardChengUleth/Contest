#include <bits/stdc++.h>

using namespace std;

int n;
int a[300000];

int main()
{
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a, a+n);

  long long ans = 0;
  for (int i = 0; i < n/2; i++) {
    int s = a[i] + a[n-1-i];
    ans += s*s;
  }
  cout << ans << endl;
}
