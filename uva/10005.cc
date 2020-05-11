#include <iostream>
#include <cmath>

using namespace std;

const double EPS = 1e-8;

double dist(double x1, double y1, double x2, double y2)
{
  double dx = x1-x2, dy = y1-y2;
  return sqrt(dx*dx + dy*dy);
}

bool solve()
{
  int n;
  cin >> n;
  if (n == 0) return false;

  int x[100], y[100];
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }
  double r;
  cin >> r;

  bool found = (n == 1);

  // try all pairs
  for (int i = 0; i < n && !found; i++) {
    for (int j = i+1; j < n && !found; j++) {
      double d = dist(x[i], y[i], x[j], y[j]);
      if (d > 2*r) continue;

      double midx = (x[i]+x[j])/2.0, midy = (y[i]+y[j])/2.0;
      double dx = y[j] - y[i], dy = x[i] - x[j];
      double len = sqrt(dx*dx + dy*dy);
      double len2 = sqrt(r*r - d*d/4);

      // try circle 1
      double cx = midx + dx*len2/len, cy = midy + dy*len2/len;
      bool good = true;
      for (int i = 0; i < n && good; i++) {
	good &= (dist(cx, cy, x[i], y[i]) <= r + EPS);
      }
      found |= good;

      // try circle 2
      cx = midx - dx*len2/len, cy = midy - dy*len2/len;
      good = true;
      for (int i = 0; i < n && good; i++) {
	good &= (dist(cx, cy, x[i], y[i]) <= r + EPS);
      }
      found |= good;
    }
  }

  if (found) {
    cout << "The polygon can be packed in the circle." << endl;
  } else {
    cout << "There is no way of packing that polygon." << endl;
  }
  return true;
}

int main(void)
{
  while (solve())
    ;

  return 0;
}
