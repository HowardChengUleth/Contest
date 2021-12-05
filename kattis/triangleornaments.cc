#include <bits/stdc++.h>

using namespace std;

// Heron's formula
//
// Computes the area of a triangle given the lengths of the three sides.
//
// Author: Howard Cheng
//

#include <iostream>
#include <iomanip>
#include <utility>
#include <cmath>

using namespace std;

// the lengths of the three sides are a, b, and c.  The routine returns
// the area of the triangle, or -1 if the three lengths do not make a
// triangle.
double area_heron(double a, double b, double c)
{
  if (a < b) swap(a, b);
  if (a < c) swap(a, c);
  if (b < c) swap(b, c);
  if (c < a - b) return -1;
  return sqrt((a+b+c)*(c-a+b)*(c+a-b)*(a+b-c))/4.0;
}

double solve()
{
  double A, B, C;
  cin >> A >> B >> C;

  // when you hang the triangle, the triangle will orient itself so that the
  // line straight down will split the area into 2 equal halves.  i.e.
  // it will cut C into exactly 2 halves

  // angle opposite to side B
  double theta = acos((A*A + C*C - B*B) / (2*A*C));

  // length of bisector
  double D = sqrt(A*A + C*C/4.0 - 2*A*C/2.0 * cos(theta));

  // area of each half = base * height/2.  Base = D, height = what we want
  double ans1 = area_heron(A, D, C/2) * 2 / D;
  double ans2 = area_heron(B, D, C/2) * 2 / D;

  return ans1 + ans2;
}

int main()
{
  int N;
  cin >> N;
  
  double ans = 0.0;
  for (int i = 0; i < N; i++) {
    ans += solve();
  }

  cout << fixed << setprecision(16) << ans << endl;

  return 0;
}
