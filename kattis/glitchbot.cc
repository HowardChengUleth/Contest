#include <bits/stdc++.h>

using namespace std;

const string cmds[] = {"Left", "Forward", "Right"};

int x, y;
int n;
string cmd_list[50];

bool works()
{
  int cx = 0, cy = 0;
  const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
  int dir = 0;

  for (int i = 0; i < n; i++) {
    if (cmd_list[i] == "Left") {
      dir = (dir+3)%4;
    } else if (cmd_list[i] == "Right") {
      dir = (dir+1)%4;
    } else {
      cx += dx[dir];
      cy += dy[dir];
    }
  }
  return cx == x && cy == y;
}

int main()
{
  cin >> x >> y;
  cin >> n;
  
  for (int i = 0; i < 50; i++) {
    cin >> cmd_list[i];
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 3; j++) {
      if (cmds[j] == cmd_list[i]) continue;
      string old = cmd_list[i];
      cmd_list[i] = cmds[j];
      if (works()) {
	cout << i+1 << ' ' << cmds[j] << endl;
	return 0;
      }
      cmd_list[i] = old;
    }
  }
  
  return 0;
}
