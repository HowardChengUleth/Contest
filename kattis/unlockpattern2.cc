#include <bits/stdc++.h>

using namespace std;

bool dEqual(int x, int y) {
  return x == y;
}

struct Point {
  int x, y;
  bool operator==(const Point &p) const { return dEqual(x, p.x) && dEqual(y, p.y); }
  bool operator<(const Point &p) const { return y < p.y || (y == p.y && x < p.x); }
};

Point operator-(Point p,Point q){ p.x -= q.x; p.y -= q.y; return p; }
Point operator+(Point p,Point q){ p.x += q.x; p.y += q.y; return p; }
Point operator*(double r,Point p){ p.x *= r; p.y *= r; return p; }
int operator*(Point p,Point q){ return p.x*q.x + p.y*q.y; }
int len2(Point p){ return p*p; }
double cross(Point p,Point q){ return p.x*q.y - q.x*p.y; }
Point inv(Point p){ Point q = {-p.y,p.x}; return q; }

enum Orientation {CCW, CW, CNEITHER};

//------------------------------------------------------------------------------
// Colinearity test
bool colinear(Point a, Point b, Point c) { return dEqual(cross(b-a,c-b),0); }

//------------------------------------------------------------------------------
// Orientation test  (When pts are colinear: ccw: a-b-c  cw: c-a-b  neither: a-c-b)
Orientation ccw(Point a, Point b, Point c) { // 
  Point d1 = b - a, d2 = c - b;
  if (dEqual(cross(d1,d2),0))
    if (d1.x * d2.x < 0 || d1.y * d2.y < 0) 
      return (d1 * d1 >= d2*d2) ? CNEITHER : CW;
    else return CCW;
  else return (cross(d1,d2) > 0) ? CCW : CW;
}

int row[9] = {0, 0, 0, 1, 1, 1, 2, 2, 2};
int col[9] = {0, 1, 2, 0, 1, 2, 0, 1, 2};

string gen_string(int perm[])
{
  bool visited[9] = {false};
  visited[perm[0]] = true;
  string ans;
  
  for (int i = 1; i < 8; i++) {
    char next;
    Point a{row[perm[i-1]], col[perm[i-1]]};
    Point b{row[perm[i]], col[perm[i]]};
    Point c{row[perm[i+1]], col[perm[i+1]]};
    if (colinear(a,b,c)) {
      next = (ccw(a,b,c) == CCW) ? 'S' : 'A';
    } else {
      next = (ccw(a,b,c) == CCW) ? 'L' : 'R';
    }
    ans += next;
  }

  for (int i = 0; i < 8; i++) {
    Point a{row[perm[i]], col[perm[i]]};
    Point c{row[perm[i+1]], col[perm[i+1]]};
    for (int j = i+2; j < 9; j++) {
      Point b{row[perm[j]], col[perm[j]]};
      if (colinear(a,b,c) && ccw(a,b,c) == CCW) {
	return "*******";
      }
    }
  }
  return ans;
}

int main()
{
  string seq;
  cin >> seq;

  int ans = 0;
  int perm[9] = {0,1,2,3,4,5,6,7,8};
  do {
    string s = gen_string(perm);
    bool good = true;
    for (int i = 0; i < 7 && good; i++) {
      good = (seq[i] == '?' && s[i] != '*') || (seq[i] == s[i]);
    }
    if (good) {
      ans++;
    }
  } while (next_permutation(perm, perm+9));
  cout << ans << endl;
  return 0;
}
