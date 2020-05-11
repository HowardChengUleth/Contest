#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Point {
  int x, y;
  Point(int xx, int yy) : x(xx), y(yy) {}
};

bool cmp_x(const Point &p1, const Point &p2)
{
  if (p1.x != p2.x) return p1.x < p2.x;
  return p1.y < p2.y;
}

bool r_cmp_y(const Point &p1, const Point &p2)
{
  if (p1.y != p2.y) return p1.y > p2.y;
  return p1.x < p2.x;
}
  
bool read_points(vector<Point> &v)
{
  int k, x, y;
  int dx, dy;

  cin >> k;
  if (k == 0) return false;
  cin >> x >> y;
  if (k > 1) {
    cin >> dx >> dy;
  }
  while (k-- > 0) {
    v.push_back(Point(x, y));
    x += dx;
    y += dy;
  }
  return true;
}

int max(int x, int y)
{
  return (x > y) ? x : y;
}

int min(int x, int y)
{
  return (x < y) ? x : y;
}

void solve_case(void)
{
  int L, W;

  cin >> L >> W;

  vector<Point> v;
  while (read_points(v)) 
    ;

  int n = v.size();

  sort(v.begin(), v.end(), cmp_x);

  // MGAP = maximum gap in the x-coordinates (counting the boundaries)
  int MGAP;
  if (n > 0) {
    MGAP = v[0].x; 
    for (int i = 1; i < n; i++) {
      MGAP = max(v[i].x - v[i-1].x, MGAP);
    }
    MGAP = max(L - v[n-1].x, MGAP);
  } else {
    MGAP = L;
  }

  // max rectangle touching top and bottom boundaries
  int MAXR = MGAP * W;       

  // sort according to the y coordinates in descending order
  sort(v.begin(), v.end(), r_cmp_y);

  for (int i = 0; i < n; i++) {
    // left and right edge of the box currently considered
    int Tl = 0, Tr = L;

    // look at all boxes with bottom = v[i] and top = v[j]
    for (int j = i+1; j < n; j++) {
      // only look at it if it's still in contention
      if (Tl < v[j].x && v[j].x < Tr) {
	// update maximum area
	MAXR = max((Tr - Tl) * (v[i].y - v[j].y), MAXR);

	// adjust current left/right edge
	if (v[j].x > v[i].x) {
	  Tr = v[j].x;
	} else {
	  Tl = v[j].x;
	}
      }
    }
    // check the rectangle touching the bottom boundary
    MAXR = max((Tr - Tl) * v[i].y, MAXR);
  }

  // check rectangles touching the top boundary
  for (int i = 0; i < n; i++) {
    int Tr = L, Tl = 0;
    for (int j = 0; j < n; j++) {
      if (v[j].y > v[i].y) {
	if (v[j].x > v[i].x) {
	  Tr = min(v[j].x, Tr);
	} else {
	  //	if (v[j].x < v[i].x) {
	  Tl = max(v[j].x, Tl);
	}
      }
    }
    MAXR = max((Tr - Tl) * (W - v[i].y), MAXR);
  }

  cout << MAXR << endl;
}

int main(void)
{
  int C;
  cin >> C;
  while (C-- > 0) {
    solve_case();
  }
  return 0;
}
