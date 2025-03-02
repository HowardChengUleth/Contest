#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  set<int> S;
  for (int i = 0; i < n; i++) {
    int r, f;
    cin >> r >> f;
    S.insert(r+f);
  }

  cout << S.size() << endl;

  return 0;
}
