#include <bits/stdc++.h>

using namespace std;

struct Point
{
  int x, y;

  Point() : x{0}, y{0} { }
};

istream &operator>>(istream &is, Point &p)
{
  return is >> p.x >> p.y;
}

int dist(Point p1, Point p2)
{
  return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

int main()
{
  vector<Point> S, B;
  string line;
  while (getline(cin, line)) {
    replace_if(begin(line), end(line),
	       [](auto c) { return !isdigit(c) && c != '-'; },
	       ' ');
    istringstream iss(line);
    Point s, b;
    iss >> s >> b;
    S.push_back(s);
    B.push_back(b);
  }

  int n = S.size();
  int row_y = (n == 14) ? 10 : 2000000;

  set<int> loc;
  for (int i = 0; i < n; i++) {
    int beacD = dist(S[i], B[i]);
    int vertD = abs(S[i].y - row_y);
    if (vertD > beacD) continue;
    int diff = beacD - vertD;
    int x1 = S[i].x - diff, x2 = S[i].x + diff;
    for (int x = x1; x <= x2; x++) {
      loc.insert(x);
    }
  }
  for (auto p : B) {
    if (p.y == row_y) {
      loc.erase(p.x);
    }
  }

  cout << loc.size() << endl;

  
			       

  return 0;
}
