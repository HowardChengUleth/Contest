#include <bits/stdc++.h>

using namespace std;

// use cube coordinates
// see https://www.redblobgames.com/grids/hexagons/

const string dir[] = { "e", "se", "sw", "w", "nw", "ne" };
const int dx[] = { 1, 0, -1, -1, 0, 1 };
const int dy[] = { -1, -1, 0, 1, 1, 0 };
const int dz[] = { 0, 1, 1, 0, -1, -1 };

struct Coord
{
  int x, y, z;

  Coord(int xx = 0, int yy = 0, int zz = 0)
    : x{xx}, y{yy}, z{zz} { }

  void move(string dname)
  {
    int d = find(dir, dir+6, dname) - dir;
    x += dx[d];
    y += dy[d];
    z += dz[d];
  }

  bool operator<(const Coord &c) const
  {
    if (x != c.x) return x < c.x;
    if (y != c.y) return y < c.y;
    return z < c.z;
  }
};

vector<string> tile;

Coord parse(string s)
{
  Coord c;

  int i = 0;
  while (i < (int)s.length()) {
    if (s[i] == 'e' || s[i] == 'w') {
      c.move(s.substr(i,1));
      i++;
    } else {
      c.move(s.substr(i,2));
      i += 2;
    }
  }

  return c;
}

set<Coord> black;

void solveA()
{
  for (auto s : tile) {
    Coord t = parse(s);
    if (black.count(t)) {
      black.erase(t);
    } else {
      black.insert(t);
    }
  }

  cout << "A = " << black.size() << endl;

}

set<Coord> stepB(const set<Coord> &black)
{
  set<Coord> S;
  map<Coord,int> white;
  
  for (auto c : black) {
    int nbr = 0;
    for (int i = 0; i < 6; i++) {
      Coord c2 = c;
      c2.move(dir[i]);
      if (black.count(c2)) {
	nbr++;
      } else {
	white[c2]++;
      }
    }

    if (!(nbr == 0 || nbr > 2)) {
      S.insert(c);
    }
  }
  for (auto [c,count] : white) {
    if (count == 2) {
      S.insert(c);
    }
  }

  return S;
}

void solveB()
{
  set<Coord> S = black;
  for (int i = 0; i < 100; i++) {
    S = stepB(S);
  }

  cout << "B = " << S.size() << endl;
}

int main()
{
  string line;
  while (getline(cin, line)) {
    tile.push_back(line);
  }

  solveA();
  solveB();
  
  return 0;
}
