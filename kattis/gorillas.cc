#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-5;

struct Point
{
  double x, y;
};

istream &operator>>(istream &is, Point &p)
{
  return is >> p.x >> p.y;
}

Point s, t;
int N;
Point obs[1000];


bool check_straight()
{
  double rise = t.y - s.y;
  double run = t.x - s.x;

  for (int i = 0; i < N; i++) {
    if ((obs[i].x - s.x) * rise / run + s.y < obs[i].y-EPS)
      return false;
  }
  
  return true;
}

double det(double A[3][3])
{
  return A[0][0]*A[1][1]*A[2][2] - A[0][0]*A[1][2]*A[2][1]
    + A[0][2]*A[1][0]*A[2][1] - A[0][1]*A[1][0]*A[2][2]
    + A[0][1]*A[1][2]*A[2][0] - A[0][2]*A[1][1]*A[2][0];
}

void find_parab(Point p1, Point p2, Point p3, double &A, double &B, double &C)
{
  double coeff[3][3] = {{ p1.x*p1.x, p1.x, 1 },
			{ p2.x*p2.x, p2.x, 1 },
			{ p3.x*p3.x, p3.x, 1 }};

  
  
  double rhs[3] = {p1.y, p2.y, p3.y};


  double bot = det(coeff);

  double coeff2[3][3];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      coeff2[i][j] = (j == 0) ? rhs[i] : coeff[i][j];
    }
  }
  A = det(coeff2)/bot;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      coeff2[i][j] = (j == 1) ? rhs[i] : coeff[i][j];
    }
  }
  B = det(coeff2)/bot;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      coeff2[i][j] = (j == 2) ? rhs[i] : coeff[i][j];
    }
  }
  C = det(coeff2)/bot;
}

bool check_parab(int i, double &peak)
{
  double A, B, C;

  find_parab(s, obs[i], t, A, B, C);
  //  cout << "A,B,C = " << A << ' ' << B << ' ' << C << endl;
  if (A >= 0) return false;
  
  for (int i = 0; i < N; i++) {
    double x = obs[i].x, y = obs[i].y;
    double h = A*x*x + B*x + C;
    //    cout << "x, h = " << x << ' ' << h << endl;
    if (h < y-EPS) {
      //      cout << "h-y = " << h-y << endl;
      return false;
    }
  }

  double peak_x = -B/(2*A);
  if (s.x <= peak_x && peak_x <= t.x) {
    peak = C - B*B/(4*A);
  } else {
    peak = max(s.y, t.y);
  }
  
  return true;
}

void solve()
{

  cin >> s >> t >> N;
  for (int i = 0; i < N; i++) {
    cin >> obs[i];
  }

  double ans = 1e100;
  bool found = false;
  
  // check if straight line works
  if (check_straight()) {
    ans = max(s.y, t.y);
    goto print;
  }

  for (int i = 0; i < N; i++) {
    double peak;
    if (check_parab(i, peak)) {
      ans = min(ans, peak);
      found = true;
    }
  }

  assert(found);

 print:
  cout << fixed << setprecision(10) << ans << endl;

}


int main()
{
  int T;
  cin >> T;
  while (T--)
    solve();

  return 0;
}
