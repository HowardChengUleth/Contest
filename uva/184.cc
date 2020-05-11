#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace std;

struct Point {
  int x, y;
  
  bool operator<(const Point &p) const {
    if (x != p.x) return x < p.x;
    return y < p.y;
  }

  bool operator!=(const Point &p) const {
    return x != p.x || y != p.y;
  }
};

struct Disc : Point {
  int index;

  Disc() { }

  Disc(const Point &p1, const Point &p2, int i) {
    x = p1.x - p2.x;
    y = p1.y - p2.y;
    index = i;
  }

  bool operator<(const Disc &p) const {
    if (*this == p) return false;
    if (x && p.x) {
      bool res = y * p.x < p.y * x;
      if (x < 0) {
	res = !res;
      }
      if (p.x < 0) {
	res = !res;
      }
      return res;
    } else if (!x) {
      return false;
    } else {
      return true;
    }
  }

  bool operator==(const Disc &p) const {
    if (x && p.x) {
      return y * p.x == p.y * x;
    } else {
      return (x == p.x);
    }
  }
};

istream &operator>>(istream &is, Point &p)
{
  return is >> p.x >> p.y;
}

ostream &operator<<(ostream &os, const Point &p)
{
  return os << '(' << setw(4) << p.x << ',' << setw(4) << p.y << ')';
}

bool line_cmp(const vector<Point> &L1, const vector<Point> &L2) {
  if (L1[0] != L2[0]) {
    return L1[0] < L2[0];
  } else {
    return L1[1] < L2[1];
  }
}
  
int main(void)
{
  while (1) {
    int n = 0;
    Point p[301];
  
    while (cin >> p[n] && (p[n].x || p[n].y)) {
      n++;
    }
    if (!n) {
      break;
    }
    vector< vector<Point> > lines;

    for (int i = 0; i < n; i++) {
      Disc disc[301];
      for (int j = 0; j < n; j++) {
	disc[j] = Disc(p[i], p[j], j);
      }
      swap(disc[i], disc[n-1]);

      sort(disc, disc+n-1);
      int s1, s2;

      for (s1 = 0; s1 < n-1; s1 = s2) {
	for (s2 = s1; s2 < n-1 && disc[s1] == disc[s2]; s2++)
	  ;
	if (s2 - s1 > 1) {
	  vector<Point> line(s2-s1+1);
	  bool seen = false;
	  line[0] = p[i];
	  for (int k = 0; k < s2-s1; k++) {
	    line[k+1] = p[disc[s1+k].index];
	    if (disc[s1+k].index < i) {
	      seen = true;
	    }
	  }
	  if (!seen) {
	    sort(line.begin(), line.end());
	    lines.push_back(line);
	  }
	}
      }
    }

    sort(lines.begin(), lines.end(), line_cmp);
    if (lines.size() == 0) {
      cout << "No lines were found" << endl;
    } else {
      cout << "The following lines were found:" << endl;
      for (unsigned int i = 0; i < lines.size(); i++) {
	for (unsigned int j = 0; j < lines[i].size(); j++) {
	  cout << lines[i][j];
	}
	cout << endl;
      }
    }
    
  }
  
  return 0;
}
