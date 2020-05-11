#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>

using namespace std;

struct Point {
  double x, y;
};

istream &operator>>(istream &is, Point &p)
{
  return is >> p.x >> p.y;
}

#define SQR(x) ((x)*(x))

double dist(const Point &p1, const Point &p2)
{
  return sqrt(SQR(p1.x-p2.x) + SQR(p1.y-p2.y));
}

double dot(const Point &a, const Point &b)
{
  return a.x * b.x + a.y * b.y;
}

double proj(const Point &M, const Point &p1, const Point &p2)
{
  Point u, v;

  v.x = M.x - p1.x;   v.y = M.y - p1.y;
  u.x = p2.x - p1.x;  u.y = p2.y - p1.y;

  return dot(u, v) / dot(u, u);
}

bool do_case()
{
  Point M;
  if (!(cin >> M)) {
    return false;
  }

  int N;
  cin >> N;
  Point p1, p2;
  double best_dist;
  Point best_p;
  
  cin >> p1;
  best_p = p1;
  best_dist = dist(M, p1);
  
  for (int i = 0; i < N; i++) {
    cin >> p2;
    double temp = dist(M, p2);
    if (best_dist > temp) {
      best_dist = temp;
      best_p = p2;
    }

    double t = proj(M, p1, p2);
    if (0 < t && t < 1) {
      Point p3;
      p3.x = p1.x + (p2.x - p1.x)*t;
      p3.y = p1.y + (p2.y - p1.y)*t;
      temp = dist(M, p3);
      if (best_dist > temp) {
	best_dist = temp;
	best_p = p3;
      }
    }
    
    p1 = p2;
  }

  cout << fixed << setprecision(4);
  cout << best_p.x << endl;
  cout << best_p.y << endl;
  
  return true;
}


int main(void)
{
  while (do_case())
    ;
  return 0;
}
