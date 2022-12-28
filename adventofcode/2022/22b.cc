#include <bits/stdc++.h>

using namespace std;

//   3
// 2   0
//   1

const int dr[] = { 0, 1, 0, -1 };
const int dc[] = { 1, 0, -1, 0 };

int dirturn[256];

const int side_len[2] = { 4, 50 };
const string side_map[2][4] = {
  {"  0 ",
   "123 ",
   "  45",
   "    "},
  
  {" 01",
   " 2 ",
   "45 ",
   "3  "}
};

const int side_next[2][6][4] = {
  {// R, D, L, U
    { 5, 3, 2, 1 },
    { 2, 4, 5, 0 },
    { 3, 4, 1, 0 },
    { 5, 4, 2, 0 },
    { 5, 1, 2, 3 },
    { 0, 1, 4, 3 },
  },
  {
    { 1, 2, 4, 3 },
    { 5, 2, 0, 3 },
    { 1, 5, 4, 0 },
    { 5, 1, 0, 4 },
    { 5, 3, 0, 2 },
    { 1, 3, 4, 2 }
  }
};

const int side_rot[2][6][4] = {
  {// R, D, L, U
    { 2, 0, 1, 2 },
    { 0, 2, 3, 2 },
    { 0, 1, 0, 3 },
    { 3, 0, 0, 0 },
    { 0, 2, 3, 0 },
    { 2, 1, 0, 1 },
  },
  {
    { 0, 0, 2, 3 },
    { 2, 3, 0, 0 },
    { 1, 0, 1, 0 },
    { 1, 0, 1, 0 },
    { 0, 0, 2, 3 },
    { 2, 3, 0, 0 }
  }
};

vector<vector<char>> face[6];
int cube = -1;            // cube 0 = sample, cube 1 = real input
string cmd;

void read_input()
{
  string line;
  int r = 0;
  while (getline(cin, line) && line != "") {
    if (cube < 0) {
      cube = line.length() >= 50;
      for (int i = 0; i < 6; i++) {
	face[i].resize(side_len[cube]);
	for (int r = 0; r < side_len[cube]; r++) {
	  face[i][r].resize(side_len[cube], ' ');
	}
      }
    }
    for (int c = 0; c < (int)line.length(); c++) {
      int map_r = r / side_len[cube];
      int map_c = c / side_len[cube];
      char f = side_map[cube][map_r][map_c];
      if (f != ' ') {
	face[f - '0'][r % side_len[cube]][c % side_len[cube]] = line[c];
      }
    }
    
    r++;
  }

  getline(cin, cmd);
}
  
int curr_f, curr_r, curr_c, curr_dir;

bool inside(int r, int c)
{
  return 0 <= r && r < side_len[cube] && 0 <= c && c < side_len[cube];
}

void rotate(int &r, int &c, int &dir)
{
  // rotate coordinates 90 deg ccw
  int next_r = side_len[cube]-1-c;
  int next_c = r;

  // rotate direction 90 deg ccw
  int next_dir = (dir + 3) % 4;

  r = next_r;
  c = next_c;
  dir = next_dir;
}

void move_steps(int steps)
{
  while (steps--) {
    int next_f = curr_f;
    int next_r = curr_r + dr[curr_dir];
    int next_c = curr_c + dc[curr_dir];
    int next_dir = curr_dir;
    if (!inside(next_r, next_c)) {
      next_f = side_next[cube][curr_f][curr_dir];
      next_r = (next_r + side_len[cube]) % side_len[cube];
      next_c = (next_c + side_len[cube]) % side_len[cube];
      for (int i = 0; i < side_rot[cube][curr_f][curr_dir]; i++) {
	rotate(next_r, next_c, next_dir);
      }
    }

    string dirchar = ">v<^";
    if (face[next_f][next_r][next_c] != '#') {
      face[curr_f][curr_r][curr_c] = dirchar[curr_dir];
      curr_f = next_f;
      curr_r = next_r;
      curr_c = next_c;
      curr_dir = next_dir;
    }
  }
}

void turn(char dir)
{
  curr_dir = (curr_dir + dirturn[dir]) % 4;
}

void process_cmd()
{
  curr_f = curr_r = curr_c = curr_dir = 0;
  
  istringstream iss(cmd);
  int steps;
  char dir;
	    
  while (true) {
    if (!(iss >> steps)) break;

    move_steps(steps);
    
    if (!(iss >> dir)) break;

    turn(dir);
  }
}

int main()
{
  read_input();

  dirturn['R'] = 1;
  dirturn['L'] = 3;
  
  process_cmd();

  for (int f = 0; f < 6; f++) {
    cout << "Face = " << f << endl << endl;
    for (const auto &v : face[f]) {
      for (const auto &c : v) {
	cout << c;
      }
      cout << endl;
    }
    cout << "======================" << endl;
  }

  cout << curr_f << ' ' << curr_r << ' ' << curr_c << ' ' << curr_dir << endl;

  for (int r = 0; r < 4; r++) {
    string::size_type c = side_map[cube][r].find(curr_f + '0');
    if (c == string::npos) continue;
    curr_r += r * side_len[cube];
    curr_c += c * side_len[cube];
  }
  curr_r++;
  curr_c++;
  
  cout << curr_f << ' ' << curr_r << ' ' << curr_c << ' ' << curr_dir << endl;
  
  int password = 1000 * curr_r + 4 * curr_c + curr_dir;
  cout << password << endl;
  
  return 0;
}
