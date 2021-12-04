#include <bits/stdc++.h>

using namespace std;

int main()
{
  typedef long long ll;
  ll horiz = 0, depth = 0, aim = 0;

  string cmd;
  while (cin >> cmd) {
    int x;
    cin >> x;

    if (cmd == "forward") {
      horiz += x;
      depth += x * aim;
    } else if (cmd == "down") {
      aim += x;
    } else if (cmd == "up") {
      aim -= x;
    }
  }

  cout << horiz * depth << endl;
  
  return 0;
}
