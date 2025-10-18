#include <bits/stdc++.h>

using namespace std;

void print(double x, double y)
{
  cout << fixed << setprecision(10) << x << ' ' << y << endl;
}

int main()
{
  int n, d;
  cin >> n >> d;

  vector<double> x(n), y(n);
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }


  for (int i = 0; i < n-1; i++) {
    print(x[i], y[i]);
    double dist = hypot(x[i+1]-x[i], y[i+1]-y[i]);
    int segments = ceil(dist / d);

    for (int k = 0; k < segments-1; k++) {
      double xx = x[i] + (k+1) * (x[i+1]-x[i]) / segments;
      double yy = y[i] + (k+1) * (y[i+1]-y[i]) / segments;
      print(xx, yy);
    }

  }

  print(x[n-1], y[n-1]);

  return 0;
}
