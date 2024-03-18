#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
  ll ans = 1;        // person 0 has both
  ll P = 0, G = 0;   // current position

  int N;
  cin >> N;
  while (N--) {
    char type;
    ll K;
    cin >> type >> K;

    if (type == 'P') {
      if (P < G && P+K >= G) {
	// catch up to the gravy, he gets to pour gravy now
	ans++;
      }
      P += K;
    } else {
      if (G < P+1) {
	ans += min(K, P-G);
      }
      G += K;
    }
  }
  cout << ans << endl;
  
  
  return 0;
}
