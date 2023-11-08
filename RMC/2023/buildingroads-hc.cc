#include <bits/stdc++.h>

using namespace std;

struct Point {
  int x, y;
};

istream &operator>>(istream &is, Point &p)
{
  return is >> p.x >> p.y;
}

ostream &operator<<(ostream &os, Point p)
{
  return os << "(" << p.x << ", " <<  p.y << ")";
}

const int MAX_N = 200;
int N;
Point p[MAX_N];

int sqdist(int i, int j)
{
  int dx = p[i].x - p[j].x, dy = p[i].y - p[j].y;
  return dx*dx + dy*dy;
}

double solve1()
{
  double best = DBL_MAX;

  if (N < 3) {
    return DBL_MAX;
  }

  for (int i = 0; i < N; i++) {
    int max1 = -1, max2 = -1;

    // try p[i] as center
    for (int j = 0; j < N; j++) {
      if (i == j) continue;

      auto d = sqdist(i, j);
      if (d > max1) {
	max2 = max1;
	max1 = d;
      } else if (d > max2) {
	max2 = d;
      }
    }
    best = min(best, sqrt(max1) + sqrt(max2));
  }
  return best;
}

typedef pair<int,int> pii;

double solve2()
{
  if (N < 4) {
    return DBL_MAX;
  }

  pii L[MAX_N][MAX_N];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      L[i][j] = pii(sqdist(i, j), j);
    }
    sort(L[i], L[i]+N);
  }

  double best_dist = DBL_MAX;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      // try p[i], p[j] as the pair
      bool coveredi[MAX_N] = { false };
      bool coveredj[MAX_N];
      fill(coveredj, coveredj+N, true);
      
      int jindex = N-1;
      for (int k = 0; k < N; k++) {
	coveredi[L[i][k].second] = true;
	while (jindex > 0 && coveredi[L[j][jindex].second]) {
	  coveredj[L[j][jindex--].second] = false;
	}
	if (L[i][k].first == 0) continue;
	if (coveredj[L[i][k].second]) continue;  // already covered by j
	if (L[j][jindex].first == 0) break;   // just a star from p[i]
	double dist = sqrt(L[i][k].first) + sqrt(L[j][jindex].first) +
	  sqrt(sqdist(i, j));
	best_dist = min(best_dist, dist);
      }
    }
  }

  return best_dist;
}

double solve()
{
  if (N == 2) {
    return sqrt(sqdist(0, 1));
  }

  double ans1 = solve1();
  double ans2 = solve2();
  
  return min(ans1, ans2);
}

int main()
{
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> p[i];
  }

  double ans = solve();
  cout << fixed << setprecision(10) << ans << endl;

  return 0;
}
