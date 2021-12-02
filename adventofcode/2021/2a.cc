#include <bits/stdc++.h>

using namespace std;

int main()
{
  typedef long long ll;
  ll horiz = 0, depth = 0;

  string cmd;
  while (cin >> cmd) {
    int x;
    cin >> x;

    if (cmd == "forward") {
      horiz += x;
    } else if (cmd == "down") {
      depth += x;
    } else {
      depth -= x;
    }
  }

  cout << horiz * depth << endl;
  
  return 0;
}
