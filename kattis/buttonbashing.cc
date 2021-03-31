#include <bits/stdc++.h>

using namespace std;

void solve()
{
  int n, t;
  cin >> n >> t;

  int b[16];
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }

  int D[3601];
  queue<int> q;
  
  fill(D, D+3601, -1);

  D[0] = 0;
  q.push(0);

  while (!q.empty()) {
    int curr = q.front();
    q.pop();

    for (int i = 0; i < n; i++) {
      int next = curr + b[i];
      next = max(0, min(3600, next));
      if (D[next] < 0) {
	D[next] = D[curr]+1;
	q.push(next);
      }
    }
  }

  int time = t;
  for (time = t; D[time] < 0; time++)
    ;
    
  cout << D[time] << ' ' << time - t << endl;


}
	  

int main()
{
  int T;
  cin >> T;
  while (T--) {
    solve();
  }

  return 0;
}
