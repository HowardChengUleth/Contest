#include <iostream>
#include <algorithm>

using namespace std;

bool inrect(int xll, int yll, int xur, int yur, int x, int y)
{
  return xll <= x && x <= xur && yll <= y && y <= yur;
}

void solve()
{
  int xll1, yll1, xur1, yur1;
  int xll2, yll2, xur2, yur2;
  cin >> xll1 >> yll1 >> xur1 >> yur1;
  cin >> xll2 >> yll2 >> xur2 >> yur2;

  int x[100], y[100];
  int n = 0;

  // see if vertex of one rectangle is in the other
  if (inrect(xll1, yll1, xur1, yur1, xll2, yll2)) {
    x[n] = xll2;
    y[n++] = yll2;
  }
  if (inrect(xll1, yll1, xur1, yur1, xur2, yll2)) {
    x[n] = xur2;
    y[n++] = yll2;
  }
  if (inrect(xll1, yll1, xur1, yur1, xll2, yur2)) {
    x[n] = xll2;
    y[n++] = yur2;
  }
  if (inrect(xll1, yll1, xur1, yur1, xur2, yur2)) {
    x[n] = xur2;
    y[n++] = yur2;
  }
  if (inrect(xll2, yll2, xur2, yur2, xll1, yll1)) {
    x[n] = xll1;
    y[n++] = yll1;
  }
  if (inrect(xll2, yll2, xur2, yur2, xur1, yll1)) {
    x[n] = xur1;
    y[n++] = yll1;
  }
  if (inrect(xll2, yll2, xur2, yur2, xll1, yur1)) {
    x[n] = xll1;
    y[n++] = yur1;
  }
  if (inrect(xll2, yll2, xur2, yur2, xur1, yur1)) {
    x[n] = xur1;
    y[n++] = yur1;
  }

  // now look at intersections of boundaries
  if (yll1 <= yll2 && yll2 <= yur1 && xll2 <= xll1 && xll1 <= xur2) {
    x[n] = xll1;
    y[n++] = yll2;
  }
  if (yll1 <= yur2 && yur2 <= yur1 && xll2 <= xll1 && xll1 <= xur2) {
    x[n] = xll1;
    y[n++] = yur2;
  }
  if (yll1 <= yll2 && yll2 <= yur1 && xll2 <= xur1 && xur1 <= xur2) {
    x[n] = xur1;
    y[n++] = yll2;
  }
  if (yll1 <= yur2 && yur2 <= yur1 && xll2 <= xur1 && xur1 <= xur2) {
    x[n] = xur1;
    y[n++] = yur2;
  }
  if (yll2 <= yll1 && yll1 <= yur2 && xll1 <= xll2 && xll2 <= xur1) {
    x[n] = xll2;
    y[n++] = yll1;
  }
  if (yll2 <= yur1 && yur1 <= yur2 && xll1 <= xll2 && xll2 <= xur1) {
    x[n] = xll2;
    y[n++] = yur1;
  }
  if (yll2 <= yll1 && yll1 <= yur2 && xll1 <= xur2 && xur2 <= xur1) {
    x[n] = xur2;
    y[n++] = yll1;
  }
  if (yll2 <= yur1 && yur1 <= yur2 && xll1 <= xur2 && xur2 <= xur1) {
    x[n] = xur2;
    y[n++] = yur1;
  }

  int xll = *min_element(x, x+n);
  int yll = *min_element(y, y+n);
  int xur = *max_element(x, x+n);
  int yur = *max_element(y, y+n);

  if (n < 4 || xll == xur || yll == yur) {
    cout << "No Overlap" << endl;
  } else {
    cout << xll << ' ' << yll << ' ' << xur << ' ' << yur << endl;
  }
}

int main()
{
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    if (i) cout << endl;
    solve();
  }
  return 0;
}
