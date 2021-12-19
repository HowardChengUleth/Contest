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

  void print(ostream &os) const
  {
    for (int i = 0; i < 3; i++) {
      os << p[i] << ' ';
    }
    os << endl;
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

int dist(Point a, Point b)
{
  int d = 0;
  for (int i = 0; i < 3; i++) {
    d += abs(a.p[i] - b.p[i]);
  }
  return d;
}

typedef set<Point> PS;
vector<PS> sensor;
vector<Point> origin[100];

void read_sensors()
{
  string s;
  int k = 0;
  while (getline(cin, s)) {
    assert(s[0] == '-');
    PS S;
    while (getline(cin, s) && s != "") {
      Point p(s);
      S.insert(p);
    }
    sensor.push_back(S);
    origin[k++].push_back(Point("0,0,0"));
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

ostream &operator<<(ostream &os, const Point p)
{
  p.print(os);
  return os;
}

bool lineup(PS &S1, const PS &S2, Point &offset)
{
  map<Point,int> freq;
  for (auto p1 : S1) {
    for (auto p2 : S2) {
      // line up p1 and p2
      Point offset = p2 - p1;
      freq[offset]++;
    }
  }

  for (auto [off, f] : freq) {
    if (f < 12) continue;

    for (auto p3 : S2) {
      S1.insert(p3 - off);
    }
    offset = off;
    return true;
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

      Point offset;
      if (lineup(sensor[to], N, offset)) {
	//	cout << "from, to = " << from << ' ' << to << endl;
	sensor[from].clear();
	//	cout << "offset = " << offset;
	for (auto p : origin[from]) {
	  origin[to].push_back(normalize(p,i,j,k) - offset);
	  //	  cout << p;
	}
	//	cout << "----" << endl;
	return true;
      }
    }
  }
  return false;
}

int main()
{
  int ans = 0;

  read_sensors();

  /*
  merge(4, 1);
  merge(3, 1);
  merge(2, 1);
  merge(1, 0);

  for (int i = 0; i < origin[0].size(); i++) {
    cout << origin[0][i] << endl;
    for (int j = 0; j < origin[0].size(); j++) {
      ans = max(ans, dist(origin[0][i], origin[0][j]));
    }
  }

  cout << ans << endl;

  return 0;
  */

  
  for (int i = sensor.size()-1; i > 0; i--) {

    int best = 0;
    for (int k = 0; k <= i; k++) {
      if (sensor[k].size() < sensor[best].size()) {
	best = k;
      }
    }
    sensor[i].swap(sensor[best]);
    origin[i].swap(origin[best]);
    
    bool found = false;
    for (int j = i-1; j >= 0 && !found; j--) {
      if (merge(i, j)) {
	found = true;
      }
    }
    cout << "i = " << i << endl;

    assert(found);
  }

  for (int i = 0; i < origin[0].size(); i++) {
    //    cout << origin[0][i] << endl;
    for (int j = 0; j < origin[0].size(); j++) {
      ans = max(ans, dist(origin[0][i], origin[0][j]));
    }
  }
  
  cout << ans << endl;

  return 0;
}
