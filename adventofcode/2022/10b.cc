#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

char A[6][40];

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

  int X = 0;
  int ans = 0;

  int cycle = 1;
  while (!add.empty()) {
    int val = add.front();
    add.pop();
    if (val == INT_MAX) {
      int row = (cycle - 1) / 40;
      int col = (cycle - 1) % 40;
      A[row][col] = (X <= col && col <= X+2) ? '#' : '.';
      cycle++;
      continue;
    }

    for (int i = 0; i < 2; i++) {
      int row = (cycle - 1) / 40;
      int col = (cycle - 1) % 40;
      A[row][col] = (X <= col && col <= X+2) ? '#' : '.';
      cycle++;
    }

    X += val;
  }

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 40; j++) {
      cout << A[i][j];
    }
    cout << endl;
  }

  return 0;
}
