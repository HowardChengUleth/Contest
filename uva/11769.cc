#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct Point
{
  double x, y, z;

  double norm() const {
    return sqrt(x*x + y*y + z*z);
  }
};

Point operator-(Point a, Point b)
{
  Point c;
  c.x = a.x - b.x;
  c.y = a.y - b.y;
  c.z = a.z - b.z;
  return c;
}

istream &operator>>(istream &is, Point &p)
{
  return is >> p.x >> p.y >> p.z;
}

Point cross(Point v1, Point v2)
{
  Point normal;
  normal.x = v1.y * v2.z - v1.z * v2.y;
  normal.y = v1.z * v2.x - v1.x * v2.z;
  normal.z = v1.x * v2.y - v1.y * v2.x;
  return normal;
}

double dot(Point v1, Point v2)
{
  return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

double surface_test(Point p[], int N, int i, int j, int k)
{
  Point v1 = p[j] - p[i];
  Point v2 = p[k] - p[i];
  Point normal = cross(v1, v2);
  
  bool pos = false, neg = false;
  for (int t = 0; t < N; t++) {
    double proj = dot(normal, p[t] - p[i]);
    pos |= proj > 0;
    neg |= proj < 0;
  }

  if (pos ^ neg) {
    return normal.norm()/2;
  } else {
    return 0.0;
  }
}

bool do_case(int case_num)
{
  int N;
  cin >> N;
  if (N == 0) {
    return false;
  }

  cout << "Case " << case_num << ": ";
  Point p[25];
  for (int i = 0; i < N; i++) {
    cin >> p[i];
  }

  double area = 0.0;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      for (int k = j+1; k < N; k++) {
	area += surface_test(p, N, i, j, k);
      }
    }
  }

  cout << fixed << setprecision(2) << area << endl;
  return true;
}

int main(void)
{
  int case_num = 1;
  while (do_case(case_num++))
    ;
  return 0;
}
