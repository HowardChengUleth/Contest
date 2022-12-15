#include <bits/stdc++.h>

using namespace std;

struct Point
{
  int x, y;

  Point(int X = 0, int Y = 0) : x{X}, y{Y} { }
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
  int max_coord = (n == 14) ? 20 : 4000000;

  vector<pair<int,int>> loc;
  loc.reserve(n+1);
  for (int y = 0; y <= max_coord; y++) {
    loc.clear();
    for (int i = 0; i < n; i++) {
      int beacD = dist(S[i], B[i]);
      int vertD = abs(S[i].y - y);

      if (vertD > beacD) continue;
      int diff = beacD - vertD;
      int x1 = S[i].x - diff, x2 = S[i].x + diff;
      x1 = max(0, x1);
      x2 = min(max_coord, x2);
      loc.emplace_back(x1, x2);
    }

    int maxX = -1;
    sort(begin(loc), end(loc));
    for (auto [s, e] : loc) {
      if (maxX >= max_coord) break;
      if (s > maxX+1) {
	cout << "x = " << maxX+1 << ' ' << "y = " << y << endl;
	long long tuning = (maxX+1) * 4000000LL + y;
	cout << tuning << endl;
	break;
      }
      maxX = max(maxX, e);
    }
  }
  
  return 0;
}
