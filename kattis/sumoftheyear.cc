#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  int64_t sum = 0, sum3 = 0;
  int ans = 0;

  for (int64_t k = 1; k <= n; k++) {
    sum += k;
    sum3 += k*k*k;
    if (sum*sum == sum3) {
      ans++;
    }
  }

  cout << ans << endl;
  
  return 0;
}
