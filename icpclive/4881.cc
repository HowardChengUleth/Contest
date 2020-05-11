//
// Idea:
//
// Assume that we have triangle ABC with side lengths a, b, c (a opposite
// to A, etc.).  If the line cuts through AB and AC, then the point(s) of
// intersection is s*AC (length s*b) and t*AB (length t*c).
//
// The area of the triangle can be computed by cross product of the vectors,
// and comparing the original triangle with the new triangle formed gives
//
//   s * t = 1/2
//
// The condition on the perimeter gives:
//
//   (a+b+c) = 2*b*s + 2*c*t
//
// substituting t = 1/(2*s) gives:
//
//   (2*b)*s^2 - (a+b+c)*s + c = 0
//
// We need to solve for s, t such that 0 <= s, t <= 1
//

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct Point
{
  double x, y;
};

istream &operator>>(istream &is, Point &p)
{
  return is >> p.x >> p.y;
}

double dist(Point a, Point b)
{
  return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

bool check(Point A, Point B, Point C, double &lA, double &lB, double &lC)
{
  double a = dist(B, C), b = dist(A, C), c = dist(A, B);

  double disc = (a+b+c)*(a+b+c) - 4 * (2*b) * c;
  if (disc < 0) return false;

  double s = ((a+b+c) + sqrt(disc)) / (2 * (2*b));
  double t = 1/(2*s);
  if (0 <= s && s <= 1 && 0 <= t && t <= 1)
    goto success;

  s = ((a+b+c) - sqrt(disc)) / (2 * (2*b));
  t = 1/(2*s);
  if (0 <= s && s <= 1 && 0 <= t && t <= 1)
    goto success;

  return false;

 success:

  // cut points
  Point p1, p2;
  p1.x = A.x + s * (C.x - A.x);
  p1.y = A.y + s * (C.y - A.y);
  p2.x = A.x + t * (B.x - A.x);
  p2.y = A.y + t * (B.y - A.y);

  lA = p2.y - p1.y;
  lB = p1.x - p2.x;

  if (lA < 0) {
    lA *= -1;
    lB *= -1;
  }

  double len = sqrt(lA*lA + lB*lB);
  lA /= len;
  lB /= len;
  lC = lA*p1.x + lB*p1.y;
  
  return true;
}

int main(void)
{
  int P;
  cin >> P;
  while (P--) {
    int id;
    Point A, B, C;
    cin >> id >> A >> B >> C;
    double lA, lB, lC;

    check(A, B, C, lA, lB, lC) || check(B, A, C, lA, lB, lC) ||
      check(C, A, B, lA, lB, lC);

    cout << id << ' ' << fixed << setprecision(5) << lA << ' ' << lB << ' '
	 << lC << endl;
  }
  return 0;
}
