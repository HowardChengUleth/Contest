#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll EPS = 0;
bool dEqual(ll x,ll y) { return x == y; }

struct Point {
  ll x, y;
  bool operator==(const Point &p) const { return dEqual(x, p.x) && dEqual(y, p.y); }
  bool operator<(const Point &p) const { return y < p.y || (y == p.y && x < p.x); }
};

Point operator-(Point p,Point q){ p.x -= q.x; p.y -= q.y; return p; }
Point operator+(Point p,Point q){ p.x += q.x; p.y += q.y; return p; }
Point operator*(double r,Point p){ p.x *= r; p.y *= r; return p; }
ll operator*(Point p,Point q){ return p.x*q.x + p.y*q.y; }
ll cross(Point p,Point q){ return p.x*q.y - q.x*p.y; }
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
// Signed Area of Polygon
double area_polygon(Point p[], int n) {
  ll sum = 0.0;
  for (int i = 0; i < n; i++)  sum += cross(p[i],p[(i+1)%n]);
  return sum/2.0;
}

double area_tri(Point p1, Point p2, Point p3)
{
  double area = fabs((cross(p1,p2) + cross(p2,p3) + cross(p3,p1))/2.0);
  return area;
}

//------------------------------------------------------------------------------
// Convex hull: Contains co-linear points. To remove colinear points:
//   Change ("< -EPS" and "> EPS") to ("< EPS" and "> -EPS")
int convex_hull(Point P[], int n, Point hull[]){
  sort(P,P+n); n = unique(P,P+n) - P;  vector<Point> L,U;
  if(n <= 2) { copy(P,P+n,hull); return n; }
  for(int i=0;i<n;i++){
    while(L.size()>1 && cross(P[i]-L.back(),L[L.size()-2]-P[i]) <= 0) L.pop_back();
    while(U.size()>1 && cross(P[i]-U.back(),U[U.size()-2]-P[i]) >= 0) U.pop_back();
    L.push_back(P[i]); U.push_back(P[i]);
  }
  copy(L.begin(),L.end(),hull); copy(U.rbegin()+1,U.rend()-1,hull+L.size());
  return L.size()+U.size()-2;
}

int main()
{
  ios::sync_with_stdio(0); cin.tie(0);
  int N, hs;
  Point p[6000], hull[10000];
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> p[i].x >> p[i].y;
  }
  hs = convex_hull(p, N, hull);
  for (int i = 0; i < hs; i++) {
    hull[hs+i] = hull[i];
  }
  
  double ans = 0.0;

  for (int i = 0; i < hs; i++) {
    int hi = 1;
    for (int lo = 1; lo < hs; lo++) {
      while (hi+1 < hs) {
	int lo1 = (i+lo) % hs;
	int hi1 = (i+hi) % hs;
	int hi2 = (i+hi+1) % hs;
	double A1 = area_tri(hull[i], hull[lo1], hull[hi1]);
	double A2 = area_tri(hull[i], hull[lo1], hull[hi2]);
	ans = max(ans, max(A1, A2));
	if (A2 > A1)
	  hi++;
	else
	  break;
      }
    }
  }
  
  cout << fixed << setprecision(10) << ans << endl;
  
  return 0;
}
