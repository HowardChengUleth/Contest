#include <iostream>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <cassert>

using namespace std;

const double C = 0.097;

double balance(double leftP, double rightV, double rightP)
{
  double a = C, b = -(leftP + C * rightV), c = (leftP*rightV - rightP*rightV);
  double x1 = (-b - sqrt(b*b - 4*a*c))/(2*a);
  double x2 = (-b + sqrt(b*b - 4*a*c))/(2*a);

  // one of them should be between 0 and rightV  (actually the smaller one is
  // the right one, but just in case...)
  if (0 <= x1 && x1 <= rightV) return x1;
  if (0 <= x2 && x2 <= rightV) return x2;
  return x1;
}

void decreaseVol(double &V, double &P, double dec)
{
  P = P*V/(V-dec);
  V -= dec;
}

bool solve(int id)
{
  int N;
  cin >> N;
  if (!N) return false;

  double h[10], pipe[10];
  for (int i = 0; i < N; i++) {
    cin >> h[i];
  }
  for (int i = 0; i < N-1; i++) {
    cin >> pipe[i];
  }
  pipe[N-1] = h[N-1] + 1;

  // volume of water is always at least the first tank and the second
  // tank to the pipe
  double water = h[0] + pipe[0];

  // volume of air in chambers, all connected
  double chamberV = accumulate(h, h+N, 0.0) - water;

  // pressure of air in chambers
  double chamberP = 1;

  // pressure we have to balance on the previous tank (tank 0 initially)
  double leftP = 1 + C*(h[0] - pipe[0]);
    
  for (int i = 1; i < N; i++) {
    // figure out how high the water is in the i-th tank
    double extra = balance(leftP, chamberV, chamberP);

    if (extra + pipe[i-1] <= pipe[i]) {
      // the extra does not reach the next pipe, we are done
      water += extra;
      goto done;
    }

    // now we know the water must go to at least pipe[i]
    double dpipe = pipe[i] - pipe[i-1];
    water += dpipe;
    decreaseVol(chamberV, chamberP, dpipe);

    // this is the pressure needed on top of the column in tank i to balance
    // tank i-1.
    double Pneeded = leftP - C * dpipe;

    // this is how much we need to decrease the volume of the chamber (and
    // fill with water)
    double Vneeded = chamberV * (1 - chamberP / Pneeded);

    if (Vneeded <= pipe[i]) {
      // we can move this amount into tank i+1, so just do it and
      // we are done
      water += Vneeded;
      goto done;
    }

    // the water has to go to at least pipe[i] in tank i+1, and this isolates
    // the chamber in tank i
    double top = h[i] - pipe[i];
    water += pipe[i];
    decreaseVol(chamberV, chamberP, pipe[i]);
    chamberV -= top;

    // now deal with tank i separately (chamber is cut off)
    extra = balance(Pneeded, top, chamberP);
    water += extra;

    //    leftP = C * extra + chamberP * top / (top - extra);
    leftP -= C * dpipe;
  }

 done:
  cout << "Case " << id << ": " << fixed << setprecision(3) << water << endl;
  cout << endl;
  return true;
}

int main()
{
  int id = 1;
  while (solve(id++))
    ;
  return 0;
}
