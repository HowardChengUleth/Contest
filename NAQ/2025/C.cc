#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n, k;
  cin >> n >> k;

  set<int> D;
  for (int i = 0; i < n; i++) {
    int d;
    cin >> d;
    D.insert(d);
  }

  cout << min(k, D.size()) << endl;


  return 0;
}
