#include <bits/stdc++.h>

using namespace std;

int main()
{
  int H;
  string s;

  cin >> H >> s;
  int node = 0;
  for (auto c : s) {
    node = node * 2 + 1;
    if (c == 'R') {
      node++;
    }
  }

  cout << (1 << (H+1))-1 - node << endl;

  return 0;
}
