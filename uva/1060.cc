#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <utility>

using namespace std;
using namespace std::rel_ops;

const double EPS = 1e-6;
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

Orientation ccw(Point a, Point b, Point c) { // ccw: a-b-c  cw: c-a-b  neither: a-c-b
  Point d1 = b - a, d2 = c - b;
  if (dEqual(cross(d1,d2),0))
    if (d1.x * d2.x < 0 || d1.y * d2.y < 0) 
      return (d1 * d1 >= d2*d2 - EPS) ? CNEITHER : CW;
    else return CCW;
  else return (cross(d1,d2) > 0) ? CCW : CW;
}

//----------------------------------------------------------
// Point in polygon
const bool BOUNDARY = false;  // is boundary in polygon?
bool point_in_poly(Point poly[], int n, Point p) {
  int i, j, c = 0;
  for (i = 0; i < n; i++) 
    if (poly[i] == p || ccw(poly[i], poly[(i+1)%n], p) == CNEITHER) return BOUNDARY;
  
  for (i = 0, j = n-1; i < n; j = i++) 
    if (((poly[i].y <= p.y && p.y < poly[j].y) || (poly[j].y <= p.y && p.y < poly[i].y)) &&
        (p.x < (poly[j].x - poly[i].x) * (p.y - poly[i].y) /
         (poly[j].y - poly[i].y) + poly[i].x))
      c = !c;
  return c;
}

//----------------------------------------------------------
// Intersection of lines (line segment or infinite line)
//      (1 == 1 intersection pt, 0 == no intersection pts, -1 == infinitely many
int intersect_line(Point a, Point b, Point c, Point d, Point &p,bool segment) {
  double num1 = cross(d-c,a-c), num2 = cross(b-a,a-c),denom = cross(b-a,d-c);
  if (!dEqual(denom, 0)) {
    double r = num1 / denom, s = num2 / denom;
    if (!segment || (0-EPS <= r && r <= 1+EPS && 0-EPS <= s && s <= 1+EPS)) {
      p = a + r*(b-a); return 1;
    } else return 0;
  }
  if(!segment) return dEqual(num1,0) ? -1 : 0; // For infinite lines, this is the end
  if (!dEqual(num1, 0)) return 0;
  if(b < a) swap(a,b); if(d < c) swap(c,d);
  if (a.x == b.x) {
    if (b.y == c.y) { p = b; return 1; }
    if (a.y == d.y) { p = a; return 1; }
    return (b.y < c.y || d.y < a.y) ? 0 : -1;
  } else if (b.x == c.x) { p = b; return 1; }
  else if (a.x == d.x) { p = a; return 1; }
  else if (b.x < c.x || d.x < a.x) return 0;
  return -1;
}

int N;
Point poly[100], pass;
int vl, vp;

Point find_luggage(double mins)
{
  int v = 0;
  
  while (1) {
    int v2 = (v+1) % N;
    Point line = poly[v2] - poly[v];
    double seg = len(line);
    double can_go = mins * vl;
    if (can_go <= seg) {
      return poly[v] + (can_go/seg) * line;
    }
    mins -= seg / vl;
    v = v2;
  }
}

bool visible(Point a, Point b)
{
  for (int i = 0; i < N; i++) {
    Point c = poly[i], d = poly[(i+1)%N];
    Point p;
    int t = intersect_line(a, b, c, d, p, true);
    if (t == 1 && (p != a && p != b)) {
      return false;
    }
  }
  Point p = 0.5 * (a + b);
  return !point_in_poly(poly, N, p);
}

// 0 - N-1 = vertices, N = passenger, N+1 = luggage
double Gconst[102][102];

bool possible(double mins)
{
  Point luggage = find_luggage(mins);

  double G[102][102];    // 0 - N-1 = vertices, N = passenger, N+1 = luggage
  
  for (int i = 0; i < N+2; i++) {
    for (int j = 0; j < N+2; j++) {
      G[i][j] = (i <= N && j <= N) ? Gconst[i][j] : 1e16;
    }
  }

  if (visible(pass, luggage)) {
    G[N][N+1] = G[N+1][N] = len(luggage - pass);
  }
  G[N+1][N+1] = 0.0;
  
  for (int i = 0; i < N; i++) {
    if (visible(poly[i], luggage)) {
      G[i][N+1] = G[N+1][i] = len(poly[i] - luggage);
    }
  }

  for (int k = 0; k < N+2; k++) {
    for (int i = 0; i < N+2; i++) {
      for (int j = 0; j < N+2; j++) {
	G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
      }
    }
  }

  return (vp * mins >= G[N][N+1]);
}

void buildG()
{
  for (int i = 0; i < N+2; i++) {
    for (int j = 0; j < N+2; j++) {
      Gconst[i][j] = 1e16;
    }
  }

  for (int i = 0; i < N; i++) {
    Gconst[i][i] = 0.0;
    for (int j = i+1; j < N; j++) {
      if (visible(poly[i], poly[j])) {
	Gconst[i][j] = Gconst[j][i] = len(poly[i] - poly[j]);
      }
    }
    if (visible(poly[i], pass)) {
      Gconst[i][N] = Gconst[N][i] = len(poly[i] - pass);
    }
  }
}

bool solve(int id)
{
  cin >> N;
  if (!N) return false;

  cout << "Case " << id << ": Time = ";

  for (int i = 0; i < N; i++) {
    cin >> poly[i].x >> poly[i].y;
  }
  cin >> pass.x >> pass.y;
  cin >> vl >> vp;

  buildG();
  double lo = 0, hi = 1000;       // seconds, lo = impossible, hi = possible

  while (!possible(hi)) {
    lo = hi;
    hi *= 2;
  }

  while (hi - lo > 1e-8) {
    double mid = lo + (hi - lo)/2;
    if (possible(mid)) {
      hi = mid;
    } else {
      lo = mid;
    }
  }

  int secs = floor(hi*60.0 + 0.5);
  cout << secs/60 << ":" << setw(2) << setfill('0') << secs%60 << endl;
  return true;
}

int main()
{
  int id = 1;
  while (solve(id++))
    ;
  return 0;
}
