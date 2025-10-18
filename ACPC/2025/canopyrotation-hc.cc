#include <bits/stdc++.h>

using namespace std;

int main()
{
  double A, B, C, D;

  cin >> A >> B >> C >> D;

  A /= 2;
  B /= 2;
  C /= 2;
  D /= 2;

  double x[4] = { D, D, -D, -D };
  double y[4] = { C, -C, C, -C };

  const int STEPS = 1'000'000;
  const double PI = acos(-1.0);

  int covered = 0;
  for (int i = 0; i < STEPS; i++) {
    double theta = (double) i / STEPS * 2 * PI;

    bool good = true;
    for (int j = 0; j < 4; j++) {
      double xx = x[j] * cos(theta) - y[j] * sin(theta);
      double yy = x[j] * sin(theta) + y[j] * cos(theta);

      good &= (fabs(xx) <= B && fabs(yy) <= A);
    }
    if (good) {
      covered++;
    }
  }

  cout << fixed << setprecision(10) << (double)covered*100 / STEPS << endl;
  return 0;
}
