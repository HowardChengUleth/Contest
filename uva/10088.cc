#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>

using namespace std;

struct Point {
  long long x, y;
};

long long area_polygon2(Point polygon[], int n)
{
  long long sum = 0;

  for (int i = 0; i < n-1; i++) {
    sum += polygon[i].x * polygon[i+1].y - polygon[i].y * polygon[i+1].x;
  }
  sum += polygon[n-1].x * polygon[0].y - polygon[n-1].y * polygon[0].x;

  if (sum < 0) sum *= -1;
  return sum;
}

int gcd(int a, int b)
{
  if (a < 0) return gcd(-a, b);
  if (b < 0) return gcd(a, -b);
  while (b) {
    int r = a % b;
    a = b;
    b = r;
  }
  return a;
}

int main(void)
{
  Point poly[1000];
  int n;

  while (cin >> n && n > 0) {
    for (int i = 0; i < n; i++) {
      cin >> poly[i].x >> poly[i].y;
    }

    long long A2 = area_polygon2(poly, n);
    int B = 0;
    for (int i = 0; i < n; i++) {
      int dx = poly[i].x - poly[(i+1)%n].x;
      int dy = poly[i].y - poly[(i+1)%n].y;
      B += gcd(dx, dy);
    }
    cout << (A2 + 2 - B)/2 << endl;
  }
  return 0;
}

