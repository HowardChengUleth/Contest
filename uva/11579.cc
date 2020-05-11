//
// The idea is to first sort the sides in increasing order.
//
// If the longest side is fixed, then it is sufficient to maximize
// the two remaining sides.
//
// To see that it's not good enough to simply choose the triangle with
// the largest longest side, try this sequence: 50, 50, 51, 100
//

#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

double area(double a, double b, double c)
{
  double s = (a+b+c)/2;

  return sqrt(s*(s-a)*(s-b)*(s-c));
}

void do_case(void)
{
  int N;
  cin >> N;
  
  double sides[10000];
  for (int i = 0; i < N; i++) {
    cin >> sides[i];
  }
  sort(sides, sides+N);
  
  // try each side as the longest side
  double best = 0.0;
  for (int i = 2; i < N; i++) {
    // two longest remaining sides can't form triangle, neither can
    // the shorter sides.
    if (sides[i-1]+sides[i-2] <= sides[i]) continue;
    double A = area(sides[i-1], sides[i-2], sides[i]);
    if (A > best) {
      best = A;
    }
  }

  cout << fixed << setprecision(2) << best << endl;
}

int main(void)
{
  int C;
  cin >> C;
  while (C-- > 0) {
    do_case();
  }
  return 0;
}
