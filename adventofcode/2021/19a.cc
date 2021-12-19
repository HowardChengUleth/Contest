#include <bits/stdc++.h>

using namespace std;

struct Point
{
  int p[3];

  Point(string s = string("0,0,0"))
  {
    replace(begin(s), end(s), ',', ' ');
    istringstream iss(s);
    for (int i = 0; i < 3; i++) {
      iss >> p[i];
    }
  }

  
  bool operator==(const Point &p2) const
  {
    return equal(p, p+3, p2.p);
  }
  
  bool operator<(const Point &p2) const
  {
    return lexicographical_compare(p, p+3, p2.p, p2.p+3);
  }
};

Point operator-(Point a, Point b)
{
  Point c;
  for (int i = 0; i < 3; i++) {
    c.p[i] = a.p[i] - b.p[i];
  }
  return c;
}

Point cross(Point a, Point b)
{
  Point c;

  c.p[0] = a.p[1]*b.p[2] - a.p[2]*b.p[1];
  c.p[1] = a.p[2]*b.p[0] - a.p[0]*b.p[2];
  c.p[2] = a.p[0]*b.p[1] - a.p[1]*b.p[0];
  return c;
}

typedef set<Point> PS;
vector<PS> sensor;

void read_sensors()
{
  string s;
  while (getline(cin, s)) {
    assert(s[0] == '-');
    PS S;
    while (getline(cin, s) && s != "") {
      Point p(s);
      S.insert(p);
    }
    sensor.push_back(S);
  }
}

Point axes[6] = {
  string("1,0,0"), string("-1,0,0"),
  string("0,1,0"), string("0,-1,0"),
  string("0,0,1"), string("0,0,-1")
};

Point normalize(Point p, int a1, int a2, int a3)
{
  int a[3] = {a1, a2, a3};
  Point q;

  for (int i = 0; i < 3; i++) {
    q.p[i] = p.p[a[i]/2];
    if (a[i] % 2) {
      q.p[i] *= -1;
    }
  }
  return q;
}

bool lineup(PS &S1, const PS &S2)
{
  for (auto p1 : S1) {
    for (auto p2 : S2) {
      // line up p1 and p2
      Point offset = p2 - p1;
      PS trans;
      int count = 0;
      for (auto p3 : S2) {
	count += S1.count(p3 - offset);
      }

      if (count < 12) continue;
      
      for (auto p3 : S2) {
	S1.insert(p3 - offset);
      }
      
      return true;
    }
  }

  return false;
}

bool merge(int from, int to)
{
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      if (i == j) continue;
      if (i/2 == j/2) continue;
      Point a3 = cross(axes[i], axes[j]);
      int k = find(axes, axes+6, a3) - axes;
      assert(k < 6);

      PS N;
      for (auto p : sensor[from]) {
	N.insert(normalize(p, i, j, k));
      }

      if (lineup(sensor[to], N)) {
	sensor[from].clear();
	return true;
      }
    }
  }
  return false;
}

int main()
{
  read_sensors();

  for (int i = sensor.size()-1; i > 0; i--) {
    int best = 0;
    for (int k = 0; k <= i; k++) {
      if (sensor[k].size() < sensor[best].size()) {
	best = k;
      }
    }
    sensor[i].swap(sensor[best]);
    bool found = false;
    for (int j = i-1; j >= 0 && !found; j--) {
      if (merge(i, j)) {
	found = true;
      }
    }
    cout << "i = " << i << endl;
    assert(found);
  }

  cout << sensor[0].size() << endl;

  return 0;
}
