#include <bits/stdc++.h>

using namespace std;

int ans[2000001] = {0};
bool prime[2000001];

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  fill(prime+2, prime+2000001, true);
  fill(ans, ans+2000001, 1);
  
  for (int k = 2; k <= 2000000; k++) {
    if (prime[k]) {
      for (int kk = k+k; kk <= 2000000; kk += k) {
	prime[kk] = false;
      }
    } else {
      for (int kk = k; kk <= 2000000; kk += k) {
	ans[kk]++;
      }
    }
  }

  int Q;
  cin >> Q;

  int i;
  while (Q--) {
    cin >> i;
    cout << ans[i] << '\n';
  }
  
  return 0;
}
