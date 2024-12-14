#include <bits/stdc++.h>

using namespace std;

const int WIDTH = 101, HEIGHT = 103;
//const int WIDTH = 11, HEIGHT = 7;
const int QWIDTH = (WIDTH-1)/2, QHEIGHT = (HEIGHT-1)/2;

typedef vector<int> vi;
typedef vector<vi> vii;

vii grid(HEIGHT, vi(WIDTH, 0));

struct Robot
{
  int x, y, vx, vy;

  Robot(string s)
  {
    istringstream iss(s);
    char ch;
    iss >> ch >> ch;
    iss >> x >> ch >> y;
    iss >> ch >> ch;
    iss >> vx >> ch >> vy;
  }

  void move()
  {
    x = (x + vx) % WIDTH;
    y = (y + vy) % HEIGHT;
    if (x < 0) x += WIDTH;
    if (y < 0) y += HEIGHT;
  }
};

ostream &operator<<(ostream &os, const Robot &r)
{
  return os << "(" << r.x << ", " << r.y << "), v = ("
	    << r.vx << ", " << r.vy << ")";
}

vector<Robot> robot;
void read_input()
{
  string line;
  while (getline(cin, line) && line != "") {
    robot.emplace_back(line);
  }
}

int count_quad(int qr, int qc)
{
  qr *= QHEIGHT+1;
  qc *= QWIDTH+1;

  int ans = 0;
  for (int r = 0; r < QHEIGHT; r++) {
    for (int c = 0; c < QWIDTH; c++) {
      ans += grid[qr+r][qc+c];
    }
  }
  return ans;
}

int main()
{
  read_input();

  for (int i = 0; i < 20000; i++) {
    for (auto &r : robot) {
      r.move();
    }

    if (i <= 99) continue;
    for (int r = 0; r < HEIGHT; r++) {
      for (int c = 0; c < WIDTH; c++) {
	grid[r][c] = 0;
      }
    }

    for (auto r : robot) {
      grid[r.y][r.x]++;
    }

    cout << "after " << i+1 << " seconds:" << endl;
    for (int r = 0; r < HEIGHT; r++) {
      for (int c = 0; c < WIDTH; c++) {
	if (grid[r][c] > 0) {
	  cout << '*';
	} else {
	  cout << '.';
	}
      }
      cout << endl;
    }
    cout << "============" << endl;
  }

  return 0;
}
