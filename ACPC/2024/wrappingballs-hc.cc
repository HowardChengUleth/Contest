#include <bits/stdc++.h>

using namespace std;

long double ball;

long double PI = acosl(-1.0);

long double eval_int(long double x)
{
  return 2 * PI * ball * x;
}

void solve(long double ball, long double paper)
{
  long double ans;

  // half the "arc length"
  long double full = PI * ball;

  // can cover everything
  if (paper >= full)
  {
    ans = 4 * PI * ball * ball;
  }
  else
  {
    // lay sphere on its side and wrap above x axis,  Figure out how far we
    // can get in x value
    long double ang = PI * (paper / full);

    // surface area = int(2*pi*f(x) * sqrt(1 + f'(x)^2), x=xlo..xhi)
    //
    // xlo = ball * cos(ang)
    // xhi = ball
    //
    // f(x) = sqrt(ball^2 - x^2)
    //
    // compute indefinite integral at x:
    //
    // 2 * pi * ball * x
    ans = 2 * PI * ball * ball * (1 - cos(ang));
  }

  cout << setprecision(16) << ans << endl;
}

int main()
{
  cin >> ball;

  int N;
  cin >> N;

  for (int i = 0; i < N; i++)
  {
    long double paper;
    cin >> paper;
    solve(ball, paper);
  }

  return 0;
}
