#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

int main()
{
  queue<int> add;
  string cmd;
  while (cin >> cmd) {
    if (cmd == "noop") {
      add.push(INT_MAX);
    } else {
      int val;
      cin >> val;
      add.push(val);
    }
  }

  int X = 1;
  int ans = 0;

  int cycle = 1;
  while (!add.empty()) {
    int val = add.front();
    add.pop();
    if (val == INT_MAX) {
      if (cycle % 40 == 20) {
	cout << cycle << ": " << X << endl;
	ans += X * cycle;
      }
      //      cout << cycle << ' ' << X << endl;
      cycle++;
      continue;
    }

    for (int i = 0; i < 2; i++) {
      //      cout << cycle << ' ' << X << endl;
      if (cycle % 40 == 20) {
	cout << cycle << ": " << X << endl;
	ans += X * cycle;
      }
      cycle++;
    }

    X += val;
    //    cout << cycle << ": " << X << endl;
  }

  cout << ans << endl;

  return 0;
}
