//
// Just simulate the bounce...that is sufficient.
//
// But my solution actually skips ahead and only check the bounces that matters.
// Remember that the centre of the ball does not reach the bumper.
//
#include <iostream>
#include <cmath>

using namespace std;

const double ball_r = 10.0;
const double lane_width = 105.0;
const double pin_r = 6.0;
const double EPS = 1e-8;
const double PI = acos(-1.0);

double dist(double angle, double x, double y)
{
  double x2 = cos(angle);
  double y2 = sin(angle);

  double proj = x*x2 + y*y2;
  return sqrt(x*x+y*y - proj*proj);
}

void solve()
{
  double T, X;
  cin >> T >> X;
  
  T *= 100;          // convert to cm
  X *= PI/180.0;     // convert to radians
  
  
  double pin_x = T, pin_y = 0;
  double len = (lane_width - 2*ball_r)/tan(X);
  double ball_x = -len/2;       // hack for the first bounce

  // figure out the first bounce that we need to consider
  int bounced = floor(floor((T - ball_r - pin_r - ball_x) / len) + 0.5);
  pin_y = bounced * (lane_width - 2*ball_r);
  ball_x += bounced * len;
  
  // try putting the pins in successive "reflections" of the lane
  do {
    if (dist(X, pin_x, pin_y) <= ball_r + pin_r + EPS) {
      cout << "yes" << endl;
      return;
    }
    ball_x += len;
    pin_y += lane_width - 2*ball_r;
  } while (ball_x <= T + ball_r + pin_r + EPS);
  cout << "no" << endl;
}

int main()
{
  int N;
  cin >> N;
  while (N--) {
    solve();
  }
  return 0;
}
