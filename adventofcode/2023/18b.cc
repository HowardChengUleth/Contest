#include <bits/stdc++.h>

using namespace std;

const string dir = "URDL";
const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

vector<int> cmd_dir, cmd_step;

bool read_cmd()
{
  char D;
  int s;
  string str;

  if (!(cin >> D >> s >> str))
    return false;

  string dir_input = "RDLU";
  D = dir_input[str[7]-'0'];
  s = stoi(str.substr(2,5), nullptr, 16);

  cmd_dir.push_back(dir.find(D));
  cmd_step.push_back(s);

  return true;
}

typedef long long ll;

struct Point {
  ll x, y;
  Point(ll xx = 0, ll yy = 0)
    : x{xx}, y{yy} { }
};

ll area_polygon2(const vector<Point> &polygon)
{
  int n = polygon.size();
  ll sum2 = 0;

  for (int i = 0; i < n-1; i++) {
    sum2 += polygon[i].x * polygon[i+1].y - polygon[i].y * polygon[i+1].x;
  }
  sum2 += polygon[n-1].x * polygon[0].y - polygon[n-1].y * polygon[0].x;
  return abs(sum2);
}


void compute()
{
  vector<Point> polygon;
  polygon.emplace_back(0, 0);

  int curr_r = 0, curr_c = 0;
  ll B = 0;
  for (int i = 0; i < (int)cmd_dir.size(); i++) {
    curr_r += dr[cmd_dir[i]] * cmd_step[i];
    curr_c += dc[cmd_dir[i]] * cmd_step[i];
    polygon.emplace_back(curr_r, curr_c);
    B += cmd_step[i];
  }

  ll A2 = area_polygon2(polygon);
  ll I2 = A2 - B + 2;

  cout << "A2 = " << A2 << endl;
  cout << "B = " << B << endl;
  cout << B + I2/2 << endl;
}


int main()
{
  while (read_cmd())
    ;

  compute();
  return 0;
}
