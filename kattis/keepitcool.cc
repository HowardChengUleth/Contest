#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n, m, s, d;
  pair<int,int> c[100];
  
  cin >> n >> m >> s >> d;
  for (int i = 0; i < s; i++) {
    cin >> c[i].first;
    c[i].second = i;
  }

  sort(c, c+s);
   
  int ans[100] = {0};

  for (int i = 0; i < s && n > 0; i++) {
    ans[c[i].second] = min(n, d-c[i].first);
    n -= ans[c[i].second];
    assert(n >= 0);
  }

  int cold = 0;
  for (int i = 0; i < s; i++) {
    if (ans[c[i].second] == 0) {
      cold += c[i].first;
    }
  }
  if (cold < m) {
    cout << "impossible" << endl;
  } else {
    for (int i = 0; i < s; i++) {
      cout << ans[i] << ' ';
    }
    cout << endl;
  }
  
  return 0;
}
