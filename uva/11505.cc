#include <iostream>
#include <cmath>
#include <string>
#include <cassert>
#include <cstdlib>

using namespace std;

struct State
{
  double x, y;
  double angle;   // angle counterclockwise from north, in degrees

  State(double xx = 0, double yy = 0, double ang = 0)
    : x(xx), y(yy), angle(ang) {}

  void advance(double units)
  {
    const double pi = acos(-1.0);
    double rad = pi*angle/180.0;
    x -= units * sin(rad);
    y += units * cos(rad);
  }

  // rotate counterclockwise by angle degrees
  void rotate(double angle)
  {
    this->angle += angle;
  }
};

struct Command
{
  enum Type { RT,  LT,  FD,  BK};
  Type type;
  int arg;

  void apply(State &s) const
  {
    switch (type) {
    case RT:
      s.rotate(-arg);
      break;
    case LT:
      s.rotate(arg);
      break;
    case FD:
      s.advance(arg);
      break;
    case BK:
      s.advance(-arg);
      break;
    }
      
  }
};

istream &operator>>(istream &is, Command &c)
{
  string cmd, arg;
  is >> cmd >> arg;

  if (cmd == "rt") {
    c.type = Command::RT;
  } else if (cmd == "lt") {
    c.type = Command::LT;
  } else if (cmd == "fd") {
    c.type = Command::FD;
  } else if (cmd == "bk") {
    c.type = Command::BK;
  } else {
    assert(0);
  }
  
  c.arg = atoi(arg.c_str());

  return is;
}

void apply(State &s, Command cmd[], int n)
{
  for (int i = 0; i < n; i++) {
    cmd[i].apply(s);
  }
}

void compute_dist(Command cmd[], int n)
{
  State s;
  apply(s, cmd, n);
  cout << static_cast<int>(floor(sqrt(s.x*s.x + s.y*s.y)+0.5)) << endl;
}
 
void solve_case(void)
{
  int n;
  cin >> n;
  
  Command cmd[1000];
  for (int i = 0; i < n; i++) {
    cin >> cmd[i];
  }

  compute_dist(cmd, n);
}
 
int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    solve_case();
  }
  return 0;
}
