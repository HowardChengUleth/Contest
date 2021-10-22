#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void solve()
{
  int N;
  cin >> N;

  ll w[100000];
  for (int i = 0; i < N; i++) {
    int W;
    cin >> W;
    w[i] = 0;
    while (W--) {
      int x;
      cin >> x;
      w[i] += x;
    }
  }
  sort(w, w+N);

  ll total = 0, curr = 0;
  for (int i = 0; i < N; i++) {
    curr += w[i];
    total += curr;
  }

  cout << fixed << setprecision(10) << (double)total/N << endl;
}

int main()
{
  int T;
  cin >> T;
  
  while (T--)
    solve();

  return 0;
}
