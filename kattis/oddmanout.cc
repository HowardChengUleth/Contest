#include <bits/stdc++.h>

using namespace std;

void solve()
{
  int G;
  cin >> G;

  map<int,int> C;
  for (int i = 0; i < G; i++) {
    int x;
    cin >> x;
    C[x]++;
  }
  for (auto p : C) {
    if (p.second == 1) {
      cout << p.first << endl;
      return;
    }
  }

}

int main()
{
  int N;
  cin >> N;

  for (int i = 1; i <= N; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
  return 0;
}
