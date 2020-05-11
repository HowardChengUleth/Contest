// idea: always drink stronger potion as soon as possible
//       may want to save double potion until later, but we only need at most
//         7 double potions because p2 <= 100.

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <climits>
#include <cfloat>

using namespace std;

struct Battle
{
  int p1, p2, t1, t2, w1, w2;
  void read()
  {
    cin >> p1 >> p2 >> t1 >> t2 >> w1 >> w2;
    w2 = min(w2, 7);
  }

  double time(int p)
  {
    p = min(p, p2);
    return (double)(t2-t1)*(p-p1)/(p2-p1) + t1;
  }
};

Battle bat[1000];

// best[n][p][w] = best time to finish battle n with power level p, and
//                 w double potions left (before we drink the reward potions
//                 for battle n)
double best[1000][101][8];

int n, p;

bool solve()
{
  cin >> n >> p;
  if (!cin || (!n && !p)) return false;

  for (int i = 0; i < n; i++) {
    bat[i].read();
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= 100; j++) {
      for (int k = 0; k < 8; k++) {
	best[i][j][k] = -1;
      }
    }
  }

  // first battle
  if (p >= bat[0].p1) {
    p = min(p, 100);
    best[0][p][bat[0].w2] = bat[0].time(p);
  }

  // subsequent battles
  for (int i = 0; i < n-1; i++) {
    for (int p = 1; p <= 100; p++) {
      for (int w = 0; w < 8; w++) {
	if (best[i][p][w] < 0) continue;

	// drink as many +1 potions as we can
	int np = min(100, p+bat[i].w1);

	// try different number of x2 potions
	for (int d = 0; d <= w; d++) {
	  if (np >= bat[i+1].p1) {
	    double t = bat[i+1].time(np) + best[i][p][w];
	    int nw = min(w - d + bat[i+1].w2, 7);
	    if (best[i+1][np][nw] < 0 || t < best[i+1][np][nw]) {
	      best[i+1][np][nw] = t;
	    }
	  }
	  np = min(100, np*2);
	}
      }
    }
  }
  
  double t = DBL_MAX;
  bool good = false;
  for (int i = bat[n-1].p1; i <= 100; i++) {
    for (int w = 0; w < 8; w++) {
      if (best[n-1][i][w] > 0) {
	t = min(t, best[n-1][i][w]);
	good = true;
      }
    }
  }
  
  if (good) {
    cout << fixed << setprecision(2) << t << endl;
  } else {
    cout << "Impossible" << endl;
  }
  return true;
}

int main()
{
  while (solve())
    ;
  return 0;
}
