#include <bits/stdc++.h>

using namespace std;

map<string,int> loc;

int main()
{
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n; i++) {
    string name;
    cin >> name;
    loc[name] = i;
  }

  for (int i = 0; i < q; i++) {
    string name1, name2;
    cin >> name1 >> name2;
    int loc1 = loc[name1], loc2 = loc[name2];
    cout << abs(loc2 - loc1) - 1 << endl;
  }

  return 0;
}
