#include <bits/stdc++.h>

using namespace std;

struct Count
{
  int left, right, any;

  Count()
    : left{0}, right{0}, any{0}
  {}
};

map<string,Count> sock;

int main()
{
  int n;
  cin >> n;

  for (int t = 0; t < n; t++) {
    string i, j;
    int k;
    cin >> i >> j >> k;
    if (j == "any") {
      sock[i].any = k;
    } else if (j == "left") {
      sock[i].left = k;
    } else if (j == "right") {
      sock[i].right = k;
    }
  }

  // for each type of socks, we can pick all left socks, all right socks
  // or just 1 "any" sock and still not have any matching socks
  int ans = 0;
  bool possible = false;
  for (auto [ type, c ] : sock) {
    ans += max(max(c.left, c.right), min(1, c.any));
    possible |= c.any >= 2;     // if there are at least 2 any
    possible |= c.left && (c.right || c.any);
    possible |= c.right && (c.left || c.any);
  }

  if (possible) {
    // ans is now the max number of socks we can get to not have a matching
    // pair, so final answer is +1.
    
    cout << ans+1 << endl;
  } else {
    cout << "impossible" << endl;
  }


  return 0;
}
