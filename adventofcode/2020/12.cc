#include <bits/stdc++.h>

using namespace std;

void rot90(int &x, int &y)
{
  swap(x,y);
  x *= -1;
}

int main()
{
  vector<char> cmd;
  vector<int> arg;

  string s;
  while (cin >> s) {
    cmd.push_back(s[0]);
    arg.push_back(stoi(s.substr(1)));
  }

  for (int i = 0; i < cmd.size(); i++) {
    if (cmd[i] == 'L' || cmd[i] == 'R') {
      assert(arg[i] == 90 || arg[i] == 180 || arg[i] == 270);
    }
  }

  const string dir_str = "WSEN";
  const int dx[4] = { -1, 0, 1, 0 };
  const int dy[4] = { 0, -1, 0, 1 };
  int curr_dir = 2;
  int curr_x = 0, curr_y = 0;

  for (int i = 0; i < cmd.size(); i++) {
    switch (cmd[i]) {
    case 'N':
    case 'S':
    case 'E':
    case 'W':
      {
	int dir = dir_str.find(cmd[i]);
	curr_x += arg[i] * dx[dir];
	curr_y += arg[i] * dy[dir];
      }
      break;
    case 'L':
      curr_dir = (curr_dir + arg[i] / 90) % 4;
      break;
    case 'R':
      curr_dir = (curr_dir + 4 - arg[i] / 90) % 4;
      break;
    case 'F':
      curr_x += arg[i] * dx[curr_dir];
      curr_y += arg[i] * dy[curr_dir];
      break;
    }
  }

  cout << "A = " << abs(curr_x) + abs(curr_y) << endl;

  int way_x = 10, way_y = 1;
  curr_x = curr_y = 0;

  for (int i = 0; i < cmd.size(); i++) {
    switch (cmd[i]) {
    case 'N':
    case 'S':
    case 'E':
    case 'W':
      {
	int dir = dir_str.find(cmd[i]);
	way_x += arg[i] * dx[dir];
	way_y += arg[i] * dy[dir];
      }
      break;
    case 'L':
      for (int k = 0; k < arg[i]/90; k++) {
	rot90(way_x, way_y);
      }
      break;
    case 'R':
      for (int k = 0; k < (360-arg[i])/90; k++) {
	rot90(way_x, way_y);
      }
      break;
    case 'F':
      curr_x += arg[i] * way_x;
      curr_y += arg[i] * way_y;
      break;
    }
  }

  cout << "B = " << abs(curr_x) + abs(curr_y) << endl;
  
  return 0;
}
