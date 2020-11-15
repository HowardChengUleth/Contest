#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-8;
bool dEqual(double x,double y) { return fabs(x-y) < EPS; }

struct Point {
  double x, y;
  bool operator==(const Point &p) const { return dEqual(x, p.x) && dEqual(y, p.y); }
  bool operator<(const Point &p) const { return y < p.y || (y == p.y && x < p.x); }
};

Point operator-(Point p,Point q){ p.x -= q.x; p.y -= q.y; return p; }
Point operator+(Point p,Point q){ p.x += q.x; p.y += q.y; return p; }
Point operator*(double r,Point p){ p.x *= r; p.y *= r; return p; }
double operator*(Point p,Point q){ return p.x*q.x + p.y*q.y; }
double len(Point p){ return sqrt(p*p); }
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
      return (d1 * d1 >= d2*d2 - EPS) ? CNEITHER : CW;
    else return CCW;
  else return (cross(d1,d2) > 0) ? CCW : CW;
}

//------------------------------------------------------------------------------
// Convex hull: Contains co-linear points. To remove colinear points:
//   Change ("< -EPS" and "> EPS") to ("< EPS" and "> -EPS")
int convex_hull(Point P[], int n, Point hull[]){
  sort(P,P+n); n = unique(P,P+n) - P;  vector<Point> L,U;
  if(n <= 2) { copy(P,P+n,hull); return n; }
  for(int i=0;i<n;i++){
    while(L.size()>1 && cross(P[i]-L.back(),L[L.size()-2]-P[i]) < -EPS) L.pop_back();
    while(U.size()>1 && cross(P[i]-U.back(),U[U.size()-2]-P[i]) >  EPS) U.pop_back();
    L.push_back(P[i]); U.push_back(P[i]);
  }
  copy(L.begin(),L.end(),hull); copy(U.rbegin()+1,U.rend()-1,hull+L.size());
  return L.size()+U.size()-2;
}

Point P[1000*1000], H[1000*1000];

int main()
{
  // a block with (left hand) x-coordinate 0 <= x < N will move to
  // x + x/N = x*(1 + 1/N) in one step.
  //
  // doing it again will move it to x + x/N + x/N^2, etc.  So the final
  // destination is x*(1 + 1/N + 1/N^2 + ...) = N/(N-1).
  //
  // only have to deal with left hand corner since it shrinks to a point.
  //
  // Once you figured out where all the blocks move to, then it is
  // just a matter of computing the convex hull of all the points.
  //
  // doesn't work though if it is 1x1 though
 
  int N;
  cin >> N;

  if (N == 1) {
    char c;
    cin >> c;
    if (c == '1') {
      cout << 4 << endl;
    } else {
      cout << 0 << endl;
    }
    return 0;
  }
  
  int n = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      char c;
      cin >> c;
      if (c == '1') {
	P[n++] = {j * N/(N-1.0), i * N/(N-1.0)};
      }
    }
  }

  int h = convex_hull(P, n, H);
  double ans = 0.0;
  for (int i = 0; i < h; i++) {
    ans += len(H[i]-H[(i+1)%h]);
  }

  cout << fixed << setprecision(10) << ans << endl;
  
  return 0;
}
