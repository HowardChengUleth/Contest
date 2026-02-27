#include <bits/stdc++.h>

using namespace std;

void solve()
{
  double v0, theta, x1, h1, h2;
  cin >> v0 >> theta >> x1 >> h1 >> h2;

  const double PI = acos(-1.0);
  const double g = 9.81;
  
  theta *= PI/180.0;

  double t = x1 / (v0 * cos(theta));
  double y = v0 * t * sin(theta) - 0.5 * g * t * t;

  if (h1+1 <= y && y <= h2-1) {
    cout << "Safe" << endl;
  } else {
    cout << "Not Safe" << endl;
  }

}

int main()
{
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    solve();
  }

  return 0;
}
