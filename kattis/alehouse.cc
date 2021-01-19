#include <bits/stdc++.h>

using namespace std;

int n, k;

// event = (t, id)  id = + if leaving, - entering
typedef pair<int,int> pii;
pii event[2*100000];

int main()
{
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    int a, b;
    cin >> a >> b;
    event[2*i-2] = pii(a, -i);
    event[2*i-1] = pii(b, i);
  }
  sort(event, event+2*n);
  
  int ans = 0;
  set<int> inbar;
  int end = 0;
  for (int i = 0; i < 2*n; i++) {
    int start_t = event[i].first;
    while (end < 2*n && event[end].first <= start_t + k) {
      if (event[end].second < 0) {
	inbar.insert(-event[end].second);
      }
      end++;
    }
    ans = max(ans, (int)inbar.size());
    
    if (event[i].second > 0) {
      inbar.erase(event[i].second);
    }
  }

  cout << ans << endl;

  return 0;
}
